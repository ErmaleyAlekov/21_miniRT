#include "../includes/mini_rt.h"

static void	intersect_circles(double *t, t_cylinder *ret, t_ray *r)
{
	double	dot;

	dot = vector_dot(r->dir, ret->n);
	if (dot == 0)
		dot = 0.00001;
	t[0] = vector_dot(vector_sub(ret->pos, r->start), ret->n) / dot;
	t[1] = vector_dot(vector_sub(ret->top, r->start), ret->n) / dot;
	if (calc_dist(ret->pos, vector_add(r->start,
				vector_scale(t[0], r->dir))) > ret->radius)
		t[0] = 200000000;
	if (calc_dist(ret->top, vector_add(r->start,
				vector_scale(t[1], r->dir))) > ret->radius)
		t[1] = 200000000;
}

static int	calc_t(t_cylinder *ret, t_ray *r, double *abc, double *t2)
{
	ret->t0 = (-abc[1] + sqrt(ret->dist)) / (2 * abc[0]);
	ret->t1 = (-abc[1] - sqrt(ret->dist)) / (2 * abc[0]);
	if (ret->t0 < EPSILON && ret->t1 < EPSILON)
		return (ret->t0);
	ret->i = vector_sub(vector_add(r->start,
				vector_scale(ret->t0, r->dir)), ret->pos);
	ret->o = vector_sub(vector_add(r->start,
				vector_scale(ret->t1, r->dir)), ret->pos);
	if (vector_dot(ret->i, ret->n1) > vector_dot(ret->n1, ret->n1)
		|| vector_dot(ret->o, ret->n1) < 0)
		ret->t0 = 200000000;
	if (vector_dot(ret->o, ret->n1) > vector_dot(ret->n1, ret->n1)
		|| vector_dot(ret->o, ret->n1) < 0)
		ret->t1 = 200000000;
	intersect_circles(t2, ret, r);
	if ((t2[0] < ret->t0 && t2[0] < ret->t1) && (ret->cap == 1) == 1)
		ret->t0 = t2[0];
	if ((t2[1] < ret->t0 && t2[1] < ret->t1) && (ret->cap == 1) == 1)
		ret->t1 = t2[1];
	if (ret->t0 < ret->t1)
		return (ret->t0);
	return (ret->t1);
}

static int	check_cylinder(t_mrt *mrt, t_cylinder *ret, double *t)
{
	double	z;

	*t = ret->t;
	mrt->new_start = vector_add(ret->r.start, vector_scale(*t, ret->r.dir));
	mrt->ret = &ret->mat;
	z = sqrt(fabs((calc_dist(mrt->new_start, ret->pos)
					* calc_dist(mrt->new_start, ret->pos)
					- ret->radius * ret->radius)));
	ret->n1 = vector_add(ret->pos, vector_scale(z, ret->n));
	if (!ret->cap)
		mrt->n = vector_sub(mrt->new_start, ret->n1);
	else
		mrt->n = ret->n;
	vector_normalize(mrt->n);
	return (1);
}

static int	intersect_cylinder(t_mrt *mrt, t_cylinder *ret, t_ray *r,
	double *t)
{
	double	abc[3];
	double	t2[2];

	ret->n = vector_normalize(ret->n);
	ret->top = vector_add(ret->pos, vector_scale(ret->h, ret->n));
	ret->hit1 = vector_sub(r->start, ret->pos);
	ret->hit2 = vector_sub(ret->hit1, vector_scale(
				vector_dot(ret->hit1, ret->n), ret->n));
	ret->hit3 = vector_sub(r->dir, vector_scale(
				vector_dot(r->dir, ret->n), ret->n));
	ret->n1 = vector_sub(ret->top, ret->pos);
	abc[0] = vector_dot(ret->hit3, ret->hit3);
	abc[1] = 2 * vector_dot(ret->hit3, ret->hit2);
	abc[2] = vector_dot(ret->hit2, ret->hit2) - (ret->radius * ret->radius);
	ret->dist = abc[1] * abc[1] - (4 * abc[0] * abc[2]);
	if ((abc[0] == 0 || ret->dist < EPSILON))
		return (0);
	ret->t = calc_t(ret, r, abc, t2);
	if (ret->t < EPSILON || ret->t == 200000000 || ret->t > *t)
		return (0);
	return (check_cylinder(mrt, ret, t));
}

int	raytracer_cy(t_mrt *mrt, t_ray *r, double *t)
{
	t_cylinder	*ret;

	mrt->cur_cy = mrt->cy;
	ret = NULL;
	while (mrt->cur_cy)
	{
		mrt->cur_cy->r.start = r->start;
		mrt->cur_cy->r.dir = r->dir;
		mrt->cur_cy->cap = 0;
		if ((intersect_cylinder(mrt, mrt->cur_cy, &mrt->cur_cy->r, t)) == 1)
			ret = mrt->cur_cy;
		mrt->cur_cy = mrt->cur_cy->next;
	}
	if (ret != NULL)
		return (1);
	return (0);
}
