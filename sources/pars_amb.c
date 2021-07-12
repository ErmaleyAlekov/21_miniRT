#include "../includes/mini_rt.h"

static void	end_parsing_amb(t_mrt *mrt)
{
	mrt->argb.r = (mrt->argb.r / 255.0f) * mrt->ali;
	mrt->argb.g = (mrt->argb.g / 255.0f) * mrt->ali;
	mrt->argb.b = (mrt->argb.b / 255.0f) * mrt->ali;
}

static void	check_error_amb(t_mrt *mrt)
{
	check_color_error(mrt, mrt->argb);
	if (mrt->ali == -1 || mrt->ali > 1.0f || mrt->ali < 0.0f
		|| mrt->error == 1)
	{
		ft_putstr_fd("Error parsing ambient light\n", 1);
		mrt->error = 1;
	}
}

void	parsing_amb(t_mrt *mrt, char *str)
{
	int	i;

	i = 0;
	if (mrt->ali != -1)
		mrt->error = 1;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-')
		{
			if (mrt->ali == -1)
				mrt->ali = ft_atof(str + i);
			else if (mrt->argb.r == -1)
				mrt->argb.r = ft_atof(str + i);
			else if (mrt->argb.g == -1)
				mrt->argb.g = ft_atof(str + i);
			else if (mrt->argb.b == -1)
				mrt->argb.b = ft_atof(str + i);
			while (str[i] && str[i] != ' ' && str[i] != '	' && str[i] != ',')
				i++;
		}
		if (str[i])
			i++;
	}
	check_error_amb(mrt);
	end_parsing_amb(mrt);
}
