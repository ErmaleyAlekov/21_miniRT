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

t_vec	calc_v_dir(t_vec rdir)
{
	t_vec	up;
	t_vec	ndir;

	up.x = 0;
	up.y = 0;
	up.z = -1;
	if (rdir.x == 0 && rdir.z == 0)
		return (up);
	up.y = 1;
	up.z = 0;
	ndir = vec_sub(up, vec_scale(vec_dot(rdir, up), rdir));
	return (ndir);
}

t_vec	calc_w_dir(t_vec rdir, t_vec u)
{
	t_vec	ndir;

	ndir.x = -1;
	ndir.y = 0;
	ndir.z = 0;
	if (rdir.x == 0 && rdir.z == 0)
		return (ndir);
	ndir.x = rdir.x * u.x;
	ndir.y = rdir.y * u.y;
	ndir.z = rdir.z * u.z;
	return (ndir);
}

unsigned int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
