#include "../includes/mini_rt.h"

static void	init_camera(t_mrt *mrt)
{
	if (!mrt->cam)
	{
		mrt->cam = cam_lstnew();
		mrt->cur_cam = mrt->cam;
	}
	else
	{
		cam_lstadd_back(&mrt->cam, cam_lstnew());
		mrt->cur_cam = mrt->cur_cam->next;
	}
	vector_init_inf(&mrt->cur_cam->pos);
	vector_init_inf(&mrt->cur_cam->dir);
	mrt->cur_cam->fov = -1;
}

static void	check_error(t_mrt *mrt)
{
	check_vector_error_inf(mrt, mrt->cur_cam->pos,
		mrt->cur_cam->dir, mrt->cur_cam->pos);
	if (mrt->cur_cam->dir.x > 1.0f || mrt->cur_cam->dir.x < -1.0f
		|| mrt->cur_cam->dir.y > 1.0f || mrt->cur_cam->dir.y < -1.0f
		|| mrt->cur_cam->dir.z > 1.0f || mrt->cur_cam->dir.z < -1.0f
		|| mrt->cur_cam->fov < 0 || mrt->cur_cam->fov > 180
		|| mrt->error == 1
		|| (mrt->cur_cam->dir.x == 0 && mrt->cur_cam->dir.y == 0
			&& mrt->cur_cam->dir.z == 0))
	{
		ft_putstr_fd("Error parsing camera\n", 1);
		mrt->error = 1;
	}
}

static void	parsing_camera2(t_mrt *mrt, char *str, int i)
{
	if (mrt->cur_cam->dir.x == 1.0 / 0.0)
		mrt->cur_cam->dir.x = ft_atof(str + i);
	else if (mrt->cur_cam->dir.y == 1.0 / 0.0)
		mrt->cur_cam->dir.y = ft_atof(str + i);
	else if (mrt->cur_cam->dir.z == 1.0 / 0.0)
		mrt->cur_cam->dir.z = ft_atof(str + i);
	else if (mrt->cur_cam->fov == -1)
		mrt->cur_cam->fov = ft_atof(str + i);
}

void	parsing_camera(t_mrt *mrt, char *str)
{
	int	i;

	i = 0;
	init_camera(mrt);
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-')
		{
			if (mrt->cur_cam->pos.x == 1.0 / 0.0)
				mrt->cur_cam->pos.x = ft_atof(str + i);
			else if (mrt->cur_cam->pos.y == 1.0 / 0.0)
				mrt->cur_cam->pos.y = ft_atof(str + i);
			else if (mrt->cur_cam->pos.z == 1.0 / 0.0)
				mrt->cur_cam->pos.z = ft_atof(str + i);
			else
				parsing_camera2(mrt, str, i);
			while (str[i] && str[i] != ' ' && str[i] != '	' && str[i] != ',')
				i++;
		}
		if (str[i])
			i++;
	}
	check_error(mrt);
	mrt->cur_cam->dir = vector_normalize(mrt->cur_cam->dir);
}
