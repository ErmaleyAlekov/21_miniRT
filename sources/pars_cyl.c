#include "../includes/mini_rt.h"

static void	init_cylinder(t_mrt *mrt)
{
	if (mrt->cy == NULL)
	{
		mrt->cy = cy_lstnew();
		mrt->cur_cy = mrt->cy;
	}
	else
	{
		cy_lstadd_back(&mrt->cy, cy_lstnew());
		mrt->cur_cy = mrt->cur_cy->next;
	}
	vector_init_inf(&mrt->cur_cy->pos);
	vector_init_inf(&mrt->cur_cy->ori);
	color_init(&mrt->cur_cy->mat.rgb);
	mrt->cur_cy->mat.reflect = -1;
	mrt->cur_cy->h = 1.0 / 0.0;
	mrt->cur_cy->radius = 1.0 / 0.0;
}

static void	check_error_cylinder(t_mrt *mrt)
{
	check_vector_error_inf(mrt, mrt->cur_cy->pos,
		mrt->cur_cy->ori, mrt->cur_cy->pos);
	check_color_error(mrt, mrt->cur_cy->mat.rgb);
	if (mrt->cur_cy->ori.x > 1.0f || mrt->cur_cy->ori.x < -1.0f
		|| mrt->cur_cy->ori.y > 1.0f || mrt->cur_cy->ori.y < -1.0f
		|| mrt->cur_cy->ori.z > 1.0f || mrt->cur_cy->ori.z < -1.0f
		|| mrt->cur_cy->h == 1.0 / 0.0 || mrt->cur_cy->h < 0
		|| mrt->cur_cy->radius == 1.0 / 0.0 || mrt->cur_cy->radius < 0
		|| mrt->error == 1)
	{
		mrt->error = 1;
		ft_putstr_fd("Error parsing cylinder\n", 1);
	}
}

static void	end_parsing_cylinder(t_mrt *mrt)
{
	if (mrt->cur_cy->mat.reflect == -1)
		mrt->cur_cy->mat.reflect = 0;
	mrt->cur_cy->mat.rgb.r /= 255.0f;
	mrt->cur_cy->mat.rgb.g /= 255.0f;
	mrt->cur_cy->mat.rgb.b /= 255.0f;
	mrt->cur_cy->n = vector_normalize(mrt->cur_cy->ori);
	mrt->cur_cy->radius /= 2;
}

static void	parsing_cylinder2(t_mrt *mrt, char *str, int i)
{
	if (mrt->cur_cy->pos.z == 1.0 / 0.0)
		mrt->cur_cy->pos.z = ft_atof(str + i);
	else if (mrt->cur_cy->ori.x == 1.0 / 0.0)
		mrt->cur_cy->ori.x = ft_atof(str + i);
	else if (mrt->cur_cy->ori.y == 1.0 / 0.0)
		mrt->cur_cy->ori.y = ft_atof(str + i);
	else if (mrt->cur_cy->ori.z == 1.0 / 0.0)
		mrt->cur_cy->ori.z = ft_atof(str + i);
	else if (mrt->cur_cy->radius == 1.0 / 0.0)
		mrt->cur_cy->radius = ft_atof(str + i);
	else if (mrt->cur_cy->h == 1.0 / 0.0)
		mrt->cur_cy->h = ft_atof(str + i);
	else if (mrt->cur_cy->mat.rgb.r == -1)
		mrt->cur_cy->mat.rgb.r = ft_atof(str + i);
	else if (mrt->cur_cy->mat.rgb.g == -1)
		mrt->cur_cy->mat.rgb.g = ft_atof(str + i);
	else if (mrt->cur_cy->mat.rgb.b == -1)
		mrt->cur_cy->mat.rgb.b = ft_atof(str + i);
}

void	parsing_cylinder(t_mrt *mrt, char *str)
{
	int	i;

	i = 0;
	init_cylinder(mrt);
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == 'r' || str[i] == '-')
		{
			if (str[i] == 'r' && mrt->cur_cy->mat.reflect == -1)
				mrt->cur_cy->mat.reflect = ft_atof(str + i);
			else if (mrt->cur_cy->pos.x == 1.0 / 0.0)
				mrt->cur_cy->pos.x = ft_atof(str + i);
			else if (mrt->cur_cy->pos.y == 1.0 / 0.0)
				mrt->cur_cy->pos.y = ft_atof(str + i);
			else
				parsing_cylinder2(mrt, str, i);
			while (str[i] && (str[i] != ' ' && str[i] != ',' && str[i] != '	'))
				i++;
		}
		if (str[i])
			i++;
	}
	check_error_cylinder(mrt);
	end_parsing_cylinder(mrt);
}
