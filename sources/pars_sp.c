#include "../includes/mini_rt.h"

static void	init_sphere(t_mrt *mrt)
{
	if (!mrt->sp)
	{
		mrt->sp = sp_lstnew();
		mrt->cur_sp = mrt->sp;
	}
	else
	{
		sp_lstadd_back(&mrt->sp, sp_lstnew());
		mrt->cur_sp = mrt->cur_sp->next;
	}
	vector_init_inf(&mrt->cur_sp->pos);
	color_init(&mrt->cur_sp->mat.rgb);
	mrt->cur_sp->radius = -1;
	mrt->cur_sp->mat.reflect = -1;
}

static void	check_error_sphere(t_mrt *mrt)
{
	check_vector_error_inf(mrt, mrt->cur_sp->pos,
		mrt->cur_sp->pos, mrt->cur_sp->pos);
	check_color_error(mrt, mrt->cur_sp->mat.rgb);
	if (mrt->error == 1 || mrt->cur_sp->radius < 0)
	{
		mrt->error = 1;
		ft_putstr_fd("Error parsing sphere\n", 1);
	}
}

static void	end_parsing_sphere(t_mrt *mrt)
{
	mrt->cur_sp->radius /= 2;
	mrt->cur_sp->save.radius = mrt->cur_sp->radius;
	if (mrt->cur_sp->mat.reflect == -1)
		mrt->cur_sp->mat.reflect = 0.0f;
	mrt->cur_sp->mat.rgb.r /= 255.0f;
	mrt->cur_sp->mat.rgb.g /= 255.0f;
	mrt->cur_sp->mat.rgb.b /= 255.0f;
	mrt->cur_sp->save.pos1 = mrt->cur_sp->pos;
}

static void	parsing_sphere2(t_mrt *mrt, char *str, int i)
{
	if (mrt->cur_sp->pos.x == 1.0 / 0.0)
		mrt->cur_sp->pos.x = ft_atof(str + i);
	else if (mrt->cur_sp->pos.y == 1.0 / 0.0)
		mrt->cur_sp->pos.y = ft_atof(str + i);
	else if (mrt->cur_sp->pos.z == 1.0 / 0.0)
		mrt->cur_sp->pos.z = ft_atof(str + i);
	else if (mrt->cur_sp->radius == -1)
		mrt->cur_sp->radius = ft_atof(str + i);
	else if (mrt->cur_sp->mat.rgb.r == -1)
		mrt->cur_sp->mat.rgb.r = ft_atof(str + i);
	else if (mrt->cur_sp->mat.rgb.g == -1)
		mrt->cur_sp->mat.rgb.g = ft_atof(str + i);
	else if (mrt->cur_sp->mat.rgb.b == -1)
		mrt->cur_sp->mat.rgb.b = ft_atof(str + i);
}

void	parsing_sphere(t_mrt *mrt, char *str)
{
	int	i;

	i = 0;
	init_sphere(mrt);
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == 'r' || str[i] == '-')
		{
			if (str[i] == 'r' && mrt->cur_sp->mat.reflect == -1)
				mrt->cur_sp->mat.reflect = ft_atof(str + i);
			else
				parsing_sphere2(mrt, str, i);
			while (str[i] && (str[i] != ' ' && str[i] != ',' && str[i] != '	'))
				i++;
		}
		if (str[i])
			i++;
	}
	check_error_sphere(mrt);
	end_parsing_sphere(mrt);
}
