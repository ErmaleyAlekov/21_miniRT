#include "../includes/mini_rt.h"

static void	init_light(t_mrt *mrt)
{
	if (!mrt->li)
	{
		mrt->li = li_lstnew();
		mrt->cur_li = mrt->li;
	}
	else
	{
		li_lstadd_back(&mrt->li, li_lstnew());
		mrt->cur_li = mrt->cur_li->next;
	}
	vector_init_inf(&mrt->cur_li->pos);
	color_init(&mrt->cur_li->color);
	mrt->cur_li->intensity = -1;
}

static void	check_error_light(t_mrt *mrt)
{
	check_vector_error_inf(mrt, mrt->cur_li->pos,
		mrt->cur_li->pos, mrt->cur_li->pos);
	check_color_error(mrt, mrt->cur_li->color);
	if (mrt->cur_li->intensity == -1 || mrt->cur_li->intensity > 1.0f
		|| mrt->cur_li->intensity < 0.0f
		|| mrt->error == 1)
	{
		ft_putstr_fd("Error parsing light\n", 1);
		mrt->error = 1;
	}
}

static void	end_parsing_light(t_mrt *mrt)
{
	if (mrt->cur_li->color.r == 0 && mrt->cur_li->color.g == 0
		&& mrt->cur_li->color.b == 0)
		mrt->cur_li->intensity = 0;
	mrt->cur_li->color.r = mrt->cur_li->color.r
		/ 255.0f * mrt->cur_li->intensity;
	mrt->cur_li->color.g = mrt->cur_li->color.g
		/ 255.0f * mrt->cur_li->intensity;
	mrt->cur_li->color.b = mrt->cur_li->color.b
		/ 255.0f * mrt->cur_li->intensity;
	mrt->cur_li->save.pos1 = mrt->cur_li->pos;
}

static void	parsing_light2(t_mrt *mrt, char *str, int i)
{
	if (mrt->cur_li->intensity == -1)
		mrt->cur_li->intensity = ft_atof(str + i);
	else if (mrt->cur_li->color.r == -1)
		mrt->cur_li->color.r = ft_atof(str + i);
	else if (mrt->cur_li->color.g == -1)
		mrt->cur_li->color.g = ft_atof(str + i);
	else if (mrt->cur_li->color.b == -1)
		mrt->cur_li->color.b = ft_atof(str + i);
}

void	parsing_light(t_mrt *mrt, char *str)
{
	int	i;

	i = 0;
	init_light(mrt);
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-')
		{
			if (mrt->cur_li->pos.x == 1.0 / 0.0)
				mrt->cur_li->pos.x = ft_atof(str + i);
			else if (mrt->cur_li->pos.y == 1.0 / 0.0)
				mrt->cur_li->pos.y = ft_atof(str + i);
			else if (mrt->cur_li->pos.z == 1.0 / 0.0)
				mrt->cur_li->pos.z = ft_atof(str + i);
			else
				parsing_light2(mrt, str, i);
			while (str[i] && str[i] != ' ' && str[i] != '	' && str[i] != ',')
				i++;
		}
		if (str[i])
			i++;
	}
	check_error_light(mrt);
	end_parsing_light(mrt);
}
