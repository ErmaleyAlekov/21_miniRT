#include "../includes/mini_rt.h"

t_vector	vector_add(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vector	vector_normalize(t_vector v1)
{
	float		norm;
	t_vector	result;

	norm = fabs(sqrt(vector_dot(v1, v1)));
	result.x = v1.x / norm;
	result.y = v1.y / norm;
	result.z = v1.z / norm;
	return (result);
}

static unsigned int	rgb_hex(int rgb[4])
{
	unsigned int	argb;

	argb = ((rgb[0] << 24) + (rgb[1] << 16) + (rgb[2] << 8) + rgb[3]);
	return (argb);
}

int	rgb_manage(double r, double g, double b)
{
	int	rgb[4];

	rgb[0] = 0;
	rgb[1] = (unsigned int)min(r * 255.0f, 255);
	rgb[2] = (unsigned int)min(g * 255.0f, 255);
	rgb[3] = (unsigned int)min(b * 255.0f, 255);
	return (rgb_hex(rgb));
}