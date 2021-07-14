#include "../includes/mini_rt.h"

static void	init_pl(t_mstr *mstr)
{
	if (mstr->pl == NULL)
	{
		mstr->pl = pl_lstnew();
		mstr->cur_pl = mstr->pl;
	}
	else
	{
		pl_lstadd_back(&mstr->pl, pl_lstnew());
		mstr->cur_pl = mstr->cur_pl->next;
	}
	vec_init_inf(&mstr->cur_pl->pos);
	vec_init_inf(&mstr->cur_pl->ori);
	color_init(&mstr->cur_pl->mat.rgb);
	mstr->cur_pl->mat.reflect = 0.4;
}

static void	check_error_plane(t_mstr *mstr)
{
	check_vec_error_inf(mstr, mstr->cur_pl->pos,
		mstr->cur_pl->ori, mstr->cur_pl->pos);
	check_color_error(mstr, mstr->cur_pl->mat.rgb);
	if (mstr->cur_pl->ori.x > 1.0f || mstr->cur_pl->ori.x < -1.0f
		|| mstr->cur_pl->ori.y > 1.0f || mstr->cur_pl->ori.y < -1.0f
		|| mstr->cur_pl->ori.z > 1.0f || mstr->cur_pl->ori.z < -1.0f
		|| mstr->error == 1)
		printf("Error parsing plane\n");
}

static void	end_parsing_plane(t_mstr *mstr)
{
	mstr->cur_pl->mat.rgb.r /= 255.0f;
	mstr->cur_pl->mat.rgb.g /= 255.0f;
	mstr->cur_pl->mat.rgb.b /= 255.0f;
	mstr->cur_pl->n = mstr->cur_pl->ori;
	mstr->cur_pl->n = vec_normalize(mstr->cur_pl->n);
}

static void	parsing_plane2(t_mstr *mstr, char *str, int i)
{
	if (mstr->cur_pl->pos.z == 1.0 / 0.0)
		mstr->cur_pl->pos.z = ft_atof(str + i);
	else if (mstr->cur_pl->ori.x == 1.0 / 0.0)
		mstr->cur_pl->ori.x = ft_atof(str + i);
	else if (mstr->cur_pl->ori.y == 1.0 / 0.0)
		mstr->cur_pl->ori.y = ft_atof(str + i);
	else if (mstr->cur_pl->ori.z == 1.0 / 0.0)
		mstr->cur_pl->ori.z = ft_atof(str + i);
	else if (mstr->cur_pl->mat.rgb.r == -1)
		mstr->cur_pl->mat.rgb.r = ft_atof(str + i);
	else if (mstr->cur_pl->mat.rgb.g == -1)
		mstr->cur_pl->mat.rgb.g = ft_atof(str + i);
	else if (mstr->cur_pl->mat.rgb.b == -1)
		mstr->cur_pl->mat.rgb.b = ft_atof(str + i);
}

void	parsing_plane(t_mstr *mstr, char *str)
{
	int	i;

	i = 0;
	init_pl(mstr);
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-')
		{
			if (mstr->cur_pl->pos.x == 1.0 / 0.0)
				mstr->cur_pl->pos.x = ft_atof(str + i);
			else if (mstr->cur_pl->pos.y == 1.0 / 0.0)
				mstr->cur_pl->pos.y = ft_atof(str + i);
			else
				parsing_plane2(mstr, str, i);
			while (str[i] && (str[i] != ' ' && str[i] != ',' && str[i] != '	'))
				i++;
		}
		if (str[i])
			i++;
	}
	check_error_plane(mstr);
	end_parsing_plane(mstr);
}
