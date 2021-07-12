#include "../includes/mini_rt.h"

double	calc_dist_fabs(t_vector v2, t_vector v1)
{
	return (fabs(sqrt(pow(v1.x - v2.x, 2)
				+ pow(v1.y - v2.y, 2) + pow(v1.z - v2.z, 2))));
}

double	calc_dist(t_vector v2, t_vector v1)
{
	return (sqrt(pow(v1.x - v2.x, 2)
			+ pow(v1.y - v2.y, 2) + pow(v1.z - v2.z, 2)));
}

double	deg2rad(double deg)
{
	return (deg * M_PI / 180);
}

t_vector	calc_v_dir(t_vector rdir)
{
	t_vector	up;
	t_vector	ndir;

	up.x = 0;
	up.y = 0;
	up.z = -1;
	if (rdir.x == 0 && rdir.z == 0)
		return (up);
	up.y = 1;
	up.z = 0;
	ndir = vector_sub(up, vector_scale(vector_dot(rdir, up), rdir));
	return (ndir);
}

t_vector	calc_w_dir(t_vector rdir, t_vector u)
{
	t_vector	ndir;

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
