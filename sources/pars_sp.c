#include "../includes/mini_rt.h"

static void	init_sphere(t_mstr *mstr)
{
	if (!mstr->sp)
	{
		mstr->sp = sp_lstnew();
		mstr->cur_sp = mstr->sp;
	}
	else
	{
		sp_lstadd_back(&mstr->sp, sp_lstnew());
		mstr->cur_sp = mstr->cur_sp->next;
	}
	vec_init_inf(&mstr->cur_sp->pos);
	color_init(&mstr->cur_sp->mat.rgb);
	mstr->cur_sp->radius = -1;
	mstr->cur_sp->mat.reflect = -1;
}

static void	check_error_sphere(t_mstr *mstr)
{
	check_vec_error_inf(mstr, mstr->cur_sp->pos,
		mstr->cur_sp->pos, mstr->cur_sp->pos);
	check_color_error(mstr, mstr->cur_sp->mat.rgb);
	if (mstr->error == 1 || mstr->cur_sp->radius < 0)
	{
		mstr->error = 1;
		ft_putstr_fd("Error parsing sphere\n", 1);
	}
}

static void	end_parsing_sphere(t_mstr *mstr)
{
	mstr->cur_sp->radius /= 2;
	mstr->cur_sp->save.radius = mstr->cur_sp->radius;
	if (mstr->cur_sp->mat.reflect == -1)
		mstr->cur_sp->mat.reflect = 0.0f;
	mstr->cur_sp->mat.rgb.r /= 255.0f;
	mstr->cur_sp->mat.rgb.g /= 255.0f;
	mstr->cur_sp->mat.rgb.b /= 255.0f;
	mstr->cur_sp->save.pos1 = mstr->cur_sp->pos;
}

static void	parsing_sphere2(t_mstr *mstr, char *str, int i)
{
	if (mstr->cur_sp->pos.x == 1.0 / 0.0)
		mstr->cur_sp->pos.x = ft_atof(str + i);
	else if (mstr->cur_sp->pos.y == 1.0 / 0.0)
		mstr->cur_sp->pos.y = ft_atof(str + i);
	else if (mstr->cur_sp->pos.z == 1.0 / 0.0)
		mstr->cur_sp->pos.z = ft_atof(str + i);
	else if (mstr->cur_sp->radius == -1)
		mstr->cur_sp->radius = ft_atof(str + i);
	else if (mstr->cur_sp->mat.rgb.r == -1)
		mstr->cur_sp->mat.rgb.r = ft_atof(str + i);
	else if (mstr->cur_sp->mat.rgb.g == -1)
		mstr->cur_sp->mat.rgb.g = ft_atof(str + i);
	else if (mstr->cur_sp->mat.rgb.b == -1)
		mstr->cur_sp->mat.rgb.b = ft_atof(str + i);
}

void	parsing_sphere(t_mstr *mstr, char *str)
{
	int	i;

	i = 0;
	init_sphere(mstr);
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == 'r' || str[i] == '-')
		{
			if (str[i] == 'r' && mstr->cur_sp->mat.reflect == -1)
				mstr->cur_sp->mat.reflect = ft_atof(str + i);
			else
				parsing_sphere2(mstr, str, i);
			while (str[i] && (str[i] != ' ' && str[i] != ',' && str[i] != '	'))
				i++;
		}
		if (str[i])
			i++;
	}
	check_error_sphere(mstr);
	end_parsing_sphere(mstr);
}
