#include "../includes/mini_rt.h"

static void	init_li(t_mstr *mstr)
{
	if (!mstr->li)
	{
		mstr->li = li_lstnew();
		mstr->cur_li = mstr->li;
	}
	else
	{
		li_lstadd_back(&mstr->li, li_lstnew());
		mstr->cur_li = mstr->cur_li->next;
	}
	vec_init_inf(&mstr->cur_li->pos);
	color_init(&mstr->cur_li->color);
	mstr->cur_li->intensity = -1;
}

static void	check_error_light(t_mstr *mstr)
{
	check_vec_error_inf(mstr, mstr->cur_li->pos,
		mstr->cur_li->pos, mstr->cur_li->pos);
	check_color_error(mstr, mstr->cur_li->color);
	if (mstr->cur_li->intensity == -1 || mstr->cur_li->intensity > 1.0f
		|| mstr->cur_li->intensity < 0.0f
		|| mstr->error == 1)
	{
		printf("Error parsing light\n");
		mstr->error = 1;
	}
}

static void	end_parsing_light(t_mstr *mstr)
{
	if (mstr->cur_li->color.r == 0 && mstr->cur_li->color.g == 0
		&& mstr->cur_li->color.b == 0)
		mstr->cur_li->intensity = 0;
	mstr->cur_li->color.r = mstr->cur_li->color.r
		/ 255.0f * mstr->cur_li->intensity;
	mstr->cur_li->color.g = mstr->cur_li->color.g
		/ 255.0f * mstr->cur_li->intensity;
	mstr->cur_li->color.b = mstr->cur_li->color.b
		/ 255.0f * mstr->cur_li->intensity;
	mstr->cur_li->save.pos1 = mstr->cur_li->pos;
}

static void	parsing_color(t_mstr *mstr, char *str, int i)
{
	if (mstr->cur_li->intensity == -1)
		mstr->cur_li->intensity = ft_atof(str + i);
	else if (mstr->cur_li->color.r == -1)
		mstr->cur_li->color.r = ft_atof(str + i);
	else if (mstr->cur_li->color.g == -1)
		mstr->cur_li->color.g = ft_atof(str + i);
	else if (mstr->cur_li->color.b == -1)
		mstr->cur_li->color.b = ft_atof(str + i);
}

void	parsing_light(t_mstr *mstr, char *str)
{
	int	i;

	i = 0;
	init_li(mstr);
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-')
		{
			if (mstr->cur_li->pos.x == 1.0 / 0.0)
				mstr->cur_li->pos.x = ft_atof(str + i);
			else if (mstr->cur_li->pos.y == 1.0 / 0.0)
				mstr->cur_li->pos.y = ft_atof(str + i);
			else if (mstr->cur_li->pos.z == 1.0 / 0.0)
				mstr->cur_li->pos.z = ft_atof(str + i);
			else
				parsing_color(mstr, str, i);
			while (str[i] && str[i] != ' ' && str[i] != '	' && str[i] != ',')
				i++;
		}
		if (str[i])
			i++;
	}
	check_error_light(mstr);
	end_parsing_light(mstr);
}
