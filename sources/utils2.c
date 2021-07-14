#include "../includes/mini_rt.h"

double	calc_dist(t_vec v2, t_vec v1)
{
	return (sqrt(pow(v1.x - v2.x, 2)
			+ pow(v1.y - v2.y, 2) + pow(v1.z - v2.z, 2)));
}

double	deg2rad(double deg)
{
	return (deg * M_PI / 180);
}

unsigned int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
