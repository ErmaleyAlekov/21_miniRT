#include "../includes/mini_rt.h"

static void	init_plane(t_mrt *mrt)
{
	if (mrt->pl == NULL)
	{
		mrt->pl = pl_lstnew();
		mrt->cur_pl = mrt->pl;
	}
	else
	{
		pl_lstadd_back(&mrt->pl, pl_lstnew());
		mrt->cur_pl = mrt->cur_pl->next;
	}
	vector_init_inf(&mrt->cur_pl->pos);
	vector_init_inf(&mrt->cur_pl->ori);
	color_init(&mrt->cur_pl->mat.rgb);
	mrt->cur_pl->mat.reflect = -1;
}

static void	check_error_plane(t_mrt *mrt)
{
	check_vector_error_inf(mrt, mrt->cur_pl->pos,
		mrt->cur_pl->ori, mrt->cur_pl->pos);
	check_color_error(mrt, mrt->cur_pl->mat.rgb);
	if (mrt->cur_pl->ori.x > 1.0f || mrt->cur_pl->ori.x < -1.0f
		|| mrt->cur_pl->ori.y > 1.0f || mrt->cur_pl->ori.y < -1.0f
		|| mrt->cur_pl->ori.z > 1.0f || mrt->cur_pl->ori.z < -1.0f
		|| mrt->error == 1)
		ft_putstr_fd("Error parsing plane\n", 1);
}

static void	end_parsing_plane(t_mrt *mrt)
{
	if (mrt->cur_pl->mat.reflect == -1)
		mrt->cur_pl->mat.reflect = 0;
	mrt->cur_pl->mat.rgb.r /= 255.0f;
	mrt->cur_pl->mat.rgb.g /= 255.0f;
	mrt->cur_pl->mat.rgb.b /= 255.0f;
	mrt->cur_pl->n = mrt->cur_pl->ori;
	mrt->cur_pl->n = vector_normalize(mrt->cur_pl->n);
}

static void	parsing_plane2(t_mrt *mrt, char *str, int i)
{
	if (mrt->cur_pl->pos.z == 1.0 / 0.0)
		mrt->cur_pl->pos.z = ft_atof(str + i);
	else if (mrt->cur_pl->ori.x == 1.0 / 0.0)
		mrt->cur_pl->ori.x = ft_atof(str + i);
	else if (mrt->cur_pl->ori.y == 1.0 / 0.0)
		mrt->cur_pl->ori.y = ft_atof(str + i);
	else if (mrt->cur_pl->ori.z == 1.0 / 0.0)
		mrt->cur_pl->ori.z = ft_atof(str + i);
	else if (mrt->cur_pl->mat.rgb.r == -1)
		mrt->cur_pl->mat.rgb.r = ft_atof(str + i);
	else if (mrt->cur_pl->mat.rgb.g == -1)
		mrt->cur_pl->mat.rgb.g = ft_atof(str + i);
	else if (mrt->cur_pl->mat.rgb.b == -1)
		mrt->cur_pl->mat.rgb.b = ft_atof(str + i);
}

void	parsing_plane(t_mrt *mrt, char *str)
{
	int	i;

	i = 0;
	init_plane(mrt);
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == 'r' || str[i] == '-')
		{
			if (str[i] == 'r' && mrt->cur_pl->mat.reflect == -1)
				mrt->cur_pl->mat.reflect = ft_atof(str + i);
			else if (mrt->cur_pl->pos.x == 1.0 / 0.0)
				mrt->cur_pl->pos.x = ft_atof(str + i);
			else if (mrt->cur_pl->pos.y == 1.0 / 0.0)
				mrt->cur_pl->pos.y = ft_atof(str + i);
			else
				parsing_plane2(mrt, str, i);
			while (str[i] && (str[i] != ' ' && str[i] != ',' && str[i] != '	'))
				i++;
		}
		if (str[i])
			i++;
	}
	check_error_plane(mrt);
	end_parsing_plane(mrt);
}
