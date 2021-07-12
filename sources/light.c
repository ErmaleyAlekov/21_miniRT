#include "../includes/mini_rt.h"

void	compute_camera(t_mstr *mstr, double x, double y)
{
	t_vec	vec1;
	t_vec	vec2;
	t_vec	camera_right;
	t_vec	camera_up;

	camera_up.x = 0;
	camera_up.y = 1;
	camera_up.z = 0;
	camera_right = vec_normalize(vec_cross(mstr->cur_cam->dir, camera_up));
	camera_up = vec_normalize(vec_cross(camera_right, mstr->cur_cam->dir));
	vec1 = vec_scale(x, camera_right);
	vec2 = vec_scale(y, camera_up);
	vec1 = vec_add(vec_add(vec1, vec2),
			vec_add(mstr->cur_cam->pos, mstr->cur_cam->dir));
	mstr->new_dir = vec_normalize(vec_sub(vec1, mstr->cur_cam->pos));
}

static int	check_intersect_all(t_mstr *mstr, double *t, t_ray *r)
{
	if (rtc_sp(mstr, r, t, 0) == 1
		|| rtc_cy(mstr, r, t) == 1)
		return (1);
	return (0);
}

static void	apply_light(t_mstr *mstr, t_ray light_ray, t_mat *ret, t_vec n)
{
	double	lamb;

	lamb = vec_dot(light_ray.dir, n) * mstr->rcoef
		* mstr->cur_li->intensity;
	mstr->tmpr += lamb * (mstr->cur_li->color.r + ret->rgb.r);
	mstr->tmpg += lamb * (mstr->cur_li->color.g + ret->rgb.g);
	mstr->tmpb += lamb * (mstr->cur_li->color.b + ret->rgb.b);
}

void	check_light(t_mat *ret, t_vec n, t_mstr *mstr, double *t)
{
	double		tmp;
	t_ray		light_ray;

	mstr->cur_li = mstr->li;
	while (mstr->cur_li)
	{
		mstr->dist = vec_sub(mstr->cur_li->pos, mstr->new_start);
		if (vec_dot(n, mstr->dist) > 0.0f)
		{
			tmp = sqrt(vec_dot(mstr->dist, mstr->dist));
			if (tmp > 0.0f)
			{
				light_ray.start = mstr->new_start;
				light_ray.dir = vec_normalize(
						vec_scale((1 / tmp), mstr->dist));
				if ((check_intersect_all(mstr, t, &light_ray)) == 0
					&& mstr->cur_li->intensity > 0.0f)
					apply_light(mstr, light_ray, ret, n);
			}
		}
		mstr->cur_li = mstr->cur_li->next;
	}
	mstr->rcoef *= ret->reflect;
	mstr->new_dir = vec_normalize(vec_sub(mstr->new_dir,
				vec_scale(2.0f * vec_dot(mstr->new_dir, n), n)));
}
