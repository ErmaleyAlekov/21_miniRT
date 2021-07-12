#include "../includes/mini_rt.h"

void	compute_camera(t_mrt *mrt, double x, double y)
{
	t_vector	vec1;
	t_vector	vec2;
	t_vector	camera_right;
	t_vector	camera_up;

	camera_up.x = 0;
	camera_up.y = 1;
	camera_up.z = 0;
	camera_right = vector_normalize(vector_cross(mrt->cur_cam->dir, camera_up));
	camera_up = vector_normalize(vector_cross(camera_right, mrt->cur_cam->dir));
	vec1 = vector_scale(x, camera_right);
	vec2 = vector_scale(y, camera_up);
	vec1 = vector_add(vector_add(vec1, vec2),
			vector_add(mrt->cur_cam->pos, mrt->cur_cam->dir));
	mrt->new_dir = vector_normalize(vector_sub(vec1, mrt->cur_cam->pos));
}

static int	check_intersect_all(t_mrt *mrt, double *t, t_ray *r)
{
	if (raytracer_sp(mrt, r, t, 0) == 1
		|| raytracer_cy(mrt, r, t) == 1)
		return (1);
	return (0);
}

static void	apply_light(t_mrt *mrt, t_ray light_ray, t_mat *ret, t_vector n)
{
	double	lamb;

	lamb = vector_dot(light_ray.dir, n) * mrt->rcoef
		* mrt->cur_li->intensity;
	mrt->tmpr += lamb * (mrt->cur_li->color.r + ret->rgb.r);
	mrt->tmpg += lamb * (mrt->cur_li->color.g + ret->rgb.g);
	mrt->tmpb += lamb * (mrt->cur_li->color.b + ret->rgb.b);
}

void	check_light(t_mat *ret, t_vector n, t_mrt *mrt, double *t)
{
	double		tmp;
	t_ray		light_ray;

	mrt->cur_li = mrt->li;
	while (mrt->cur_li)
	{
		mrt->dist = vector_sub(mrt->cur_li->pos, mrt->new_start);
		if (vector_dot(n, mrt->dist) > 0.0f)
		{
			tmp = sqrt(vector_dot(mrt->dist, mrt->dist));
			if (tmp > 0.0f)
			{
				light_ray.start = mrt->new_start;
				light_ray.dir = vector_normalize(
						vector_scale((1 / tmp), mrt->dist));
				if ((check_intersect_all(mrt, t, &light_ray)) == 0
					&& mrt->cur_li->intensity > 0.0f)
					apply_light(mrt, light_ray, ret, n);
			}
		}
		mrt->cur_li = mrt->cur_li->next;
	}
	mrt->rcoef *= ret->reflect;
	mrt->new_dir = vector_normalize(vector_sub(mrt->new_dir,
				vector_scale(2.0f * vector_dot(mrt->new_dir, n), n)));
}
