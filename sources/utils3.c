#include "../includes/mini_rt.h"

t_vector	vector_divide(t_vector v1, t_vector v2)
{
	t_vector	ret;

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

t_vector	vector_sub(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vector	vector_cross(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return (ret);
}

double	vector_dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	vector_scale(double c, t_vector v)
{
	t_vector	result;

	result.x = v.x * c;
	result.y = v.y * c;
	result.z = v.z * c;
	return (result);
}
