#include "../includes/mini_rt.h"

static void	end_parsing_amb(t_mstr *mstr)
{
	mstr->argb.r = (mstr->argb.r / 255.0f) * mstr->ali;
	mstr->argb.g = (mstr->argb.g / 255.0f) * mstr->ali;
	mstr->argb.b = (mstr->argb.b / 255.0f) * mstr->ali;
}

static void	check_error_amb(t_mstr *mstr)
{
	check_color_error(mstr, mstr->argb);
	if (mstr->ali == -1 || mstr->ali > 1.0f || mstr->ali < 0.0f
		|| mstr->error == 1)
	{
		ft_putstr_fd("Error parsing ambient light\n", 1);
		mstr->error = 1;
	}
}

void	parsing_amb(t_mstr *mstr, char *str)
{
	int	i;

	i = 0;
	if (mstr->ali != -1)
		mstr->error = 1;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-')
		{
			if (mstr->ali == -1)
				mstr->ali = ft_atof(str + i);
			else if (mstr->argb.r == -1)
				mstr->argb.r = ft_atof(str + i);
			else if (mstr->argb.g == -1)
				mstr->argb.g = ft_atof(str + i);
			else if (mstr->argb.b == -1)
				mstr->argb.b = ft_atof(str + i);
			while (str[i] && str[i] != ' ' && str[i] != '	' && str[i] != ',')
				i++;
		}
		if (str[i])
			i++;
	}
	check_error_amb(mstr);
	end_parsing_amb(mstr);
}
