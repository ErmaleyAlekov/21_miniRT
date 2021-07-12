#include "../includes/mini_rt.h"

static void	init_camera(t_mstr *mstr)
{
	if (!mstr->cam)
	{
		mstr->cam = cam_lstnew();
		mstr->cur_cam = mstr->cam;
	}
	else
	{
		cam_lstadd_back(&mstr->cam, cam_lstnew());
		mstr->cur_cam = mstr->cur_cam->next;
	}
	vec_init_inf(&mstr->cur_cam->pos);
	vec_init_inf(&mstr->cur_cam->dir);
	mstr->cur_cam->fov = -1;
}

static void	check_error(t_mstr *mstr)
{
	check_vec_error_inf(mstr, mstr->cur_cam->pos,
		mstr->cur_cam->dir, mstr->cur_cam->pos);
	if (mstr->cur_cam->dir.x > 1.0f || mstr->cur_cam->dir.x < -1.0f
		|| mstr->cur_cam->dir.y > 1.0f || mstr->cur_cam->dir.y < -1.0f
		|| mstr->cur_cam->dir.z > 1.0f || mstr->cur_cam->dir.z < -1.0f
		|| mstr->cur_cam->fov < 0 || mstr->cur_cam->fov > 180
		|| mstr->error == 1
		|| (mstr->cur_cam->dir.x == 0 && mstr->cur_cam->dir.y == 0
			&& mstr->cur_cam->dir.z == 0))
	{
		ft_putstr_fd("Error parsing camera\n", 1);
		mstr->error = 1;
	}
}

static void	parsing_camera2(t_mstr *mstr, char *str, int i)
{
	if (mstr->cur_cam->dir.x == 1.0 / 0.0)
		mstr->cur_cam->dir.x = ft_atof(str + i);
	else if (mstr->cur_cam->dir.y == 1.0 / 0.0)
		mstr->cur_cam->dir.y = ft_atof(str + i);
	else if (mstr->cur_cam->dir.z == 1.0 / 0.0)
		mstr->cur_cam->dir.z = ft_atof(str + i);
	else if (mstr->cur_cam->fov == -1)
		mstr->cur_cam->fov = ft_atof(str + i);
}

void	parsing_camera(t_mstr *mstr, char *str)
{
	int	i;

	i = 0;
	init_camera(mstr);
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-')
		{
			if (mstr->cur_cam->pos.x == 1.0 / 0.0)
				mstr->cur_cam->pos.x = ft_atof(str + i);
			else if (mstr->cur_cam->pos.y == 1.0 / 0.0)
				mstr->cur_cam->pos.y = ft_atof(str + i);
			else if (mstr->cur_cam->pos.z == 1.0 / 0.0)
				mstr->cur_cam->pos.z = ft_atof(str + i);
			else
				parsing_camera2(mstr, str, i);
			while (str[i] && str[i] != ' ' && str[i] != '	' && str[i] != ',')
				i++;
		}
		if (str[i])
			i++;
	}
	check_error(mstr);
	mstr->cur_cam->dir = vec_normalize(mstr->cur_cam->dir);
}
