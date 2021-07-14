#include "../includes/mini_rt.h"

static void	init_cylinder(t_mstr *mstr)
{
	if (mstr->cy == NULL)
	{
		mstr->cy = cy_lstnew();
		mstr->cur_cy = mstr->cy;
	}
	else
	{
		cy_lstadd_back(&mstr->cy, cy_lstnew());
		mstr->cur_cy = mstr->cur_cy->next;
	}
	vec_init_inf(&mstr->cur_cy->pos);
	vec_init_inf(&mstr->cur_cy->ori);
	color_init(&mstr->cur_cy->mat.rgb);
	mstr->cur_cy->mat.reflect = 0.4;
	mstr->cur_cy->h = 1.0 / 0.0;
	mstr->cur_cy->radius = 1.0 / 0.0;
}

static void	check_error_cylinder(t_mstr *mstr)
{
	check_vec_error_inf(mstr, mstr->cur_cy->pos,
		mstr->cur_cy->ori, mstr->cur_cy->pos);
	check_color_error(mstr, mstr->cur_cy->mat.rgb);
	if (mstr->cur_cy->ori.x > 1.0f || mstr->cur_cy->ori.x < -1.0f
		|| mstr->cur_cy->ori.y > 1.0f || mstr->cur_cy->ori.y < -1.0f
		|| mstr->cur_cy->ori.z > 1.0f || mstr->cur_cy->ori.z < -1.0f
		|| mstr->cur_cy->h == 1.0 / 0.0 || mstr->cur_cy->h < 0
		|| mstr->cur_cy->radius == 1.0 / 0.0 || mstr->cur_cy->radius < 0
		|| mstr->error == 1)
	{
		mstr->error = 1;
		printf("Error parsing cylinder\n");
	}
}

static void	end_parsing_cylinder(t_mstr *mstr)
{
	mstr->cur_cy->mat.rgb.r /= 255.0f;
	mstr->cur_cy->mat.rgb.g /= 255.0f;
	mstr->cur_cy->mat.rgb.b /= 255.0f;
	mstr->cur_cy->n = vec_normalize(mstr->cur_cy->ori);
	mstr->cur_cy->radius /= 2;
}

static void	parsing_cylinder2(t_mstr *mstr, char *str, int i)
{
	if (mstr->cur_cy->pos.z == 1.0 / 0.0)
		mstr->cur_cy->pos.z = ft_atof(str + i);
	else if (mstr->cur_cy->ori.x == 1.0 / 0.0)
		mstr->cur_cy->ori.x = ft_atof(str + i);
	else if (mstr->cur_cy->ori.y == 1.0 / 0.0)
		mstr->cur_cy->ori.y = ft_atof(str + i);
	else if (mstr->cur_cy->ori.z == 1.0 / 0.0)
		mstr->cur_cy->ori.z = ft_atof(str + i);
	else if (mstr->cur_cy->radius == 1.0 / 0.0)
		mstr->cur_cy->radius = ft_atof(str + i);
	else if (mstr->cur_cy->h == 1.0 / 0.0)
		mstr->cur_cy->h = ft_atof(str + i);
	else if (mstr->cur_cy->mat.rgb.r == -1)
		mstr->cur_cy->mat.rgb.r = ft_atof(str + i);
	else if (mstr->cur_cy->mat.rgb.g == -1)
		mstr->cur_cy->mat.rgb.g = ft_atof(str + i);
	else if (mstr->cur_cy->mat.rgb.b == -1)
		mstr->cur_cy->mat.rgb.b = ft_atof(str + i);
}

void	parsing_cylinder(t_mstr *mstr, char *str)
{
	int	i;

	i = 0;
	init_cylinder(mstr);
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-')
		{
			if (mstr->cur_cy->pos.x == 1.0 / 0.0)
				mstr->cur_cy->pos.x = ft_atof(str + i);
			else if (mstr->cur_cy->pos.y == 1.0 / 0.0)
				mstr->cur_cy->pos.y = ft_atof(str + i);
			else
				parsing_cylinder2(mstr, str, i);
			while (str[i] && (str[i] != ' ' && str[i] != ',' && str[i] != '	'))
				i++;
		}
		if (str[i])
			i++;
	}
	check_error_cylinder(mstr);
	end_parsing_cylinder(mstr);
}
