#include "../includes/mini_rt.h"

t_vec	vec_divide(t_vec v1, t_vec v2)
{
	t_vec	ret;

	ret.x = 0;
	ret.y = 0;
	ret.z = 0;
	if (v1.x != 0 && v2.x != 0)
		ret.x = v1.x / v2.x;
	if (v1.y != 0 && v2.y != 0)
		ret.y = v1.y / v2.y;
	if (v1.z != 0 && v2.z != 0)
		ret.z = v1.z / v2.z;
	return (ret);
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	t_vec	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vec	vec_cross(t_vec v1, t_vec v2)
{
	t_vec	ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return (ret);
}

double	vec_dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec	vec_scale(double c, t_vec v)
{
	t_vec	result;

	result.x = v.x * c;
	result.y = v.y * c;
	result.z = v.z * c;
	return (result);
}
