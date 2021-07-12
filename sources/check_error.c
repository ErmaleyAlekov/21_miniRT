#include "../includes/mini_rt.h"

void	check_vector_error(t_mrt *mrt, t_vector v1, t_vector v2, t_vector v3)
{
	if (v1.x == -1 || v1.y == -1 || v1.z == -1)
		mrt->error = 1;
	if (v2.x == -1 || v2.y == -1 || v2.z == -1)
		mrt->error = 1;
	if (v3.x == -1 || v3.y == -1 || v3.z == -1)
		mrt->error = 1;
}

void	check_color_error(t_mrt *mrt, t_color col)
{
	if (col.r < 0 || col.r > 255)
		mrt->error = 1;
	if (col.g < 0 || col.g > 255)
		mrt->error = 1;
	if (col.b < 0 || col.b > 255)
		mrt->error = 1;
}

void	check_vector_error_inf(t_mrt *mrt, t_vector v1, t_vector v2,
	t_vector v3)
{
	if (v1.x == 1.0 / 0.0 || v1.y == 1.0 / 0.0 || v1.z == 1.0 / 0.0)
		mrt->error = 1;
	if (v2.x == 1.0 / 0.0 || v2.y == 1.0 / 0.0 || v2.z == 1.0 / 0.0)
		mrt->error = 1;
	if (v3.x == 1.0 / 0.0 || v3.y == 1.0 / 0.0 || v3.z == 1.0 / 0.0)
		mrt->error = 1;
}
