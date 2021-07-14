#include "../includes/mini_rt.h"

static void	intersect_circles(double *t, t_cyl *ret, t_ray *r)
{
	double	dot;

	dot = vec_dot(r->dir, ret->n);
	if (dot == 0)
		dot = 0.00001;
	t[0] = vec_dot(vec_sub(ret->pos, r->start), ret->n) / dot;
	t[1] = vec_dot(vec_sub(ret->top, r->start), ret->n) / dot;
	if (calc_dist(ret->pos, vec_add(r->start,
				vec_scale(t[0], r->dir))) > ret->radius)
		t[0] = 200000000;
	if (calc_dist(ret->top, vec_add(r->start,
				vec_scale(t[1], r->dir))) > ret->radius)
		t[1] = 200000000;
}

static int	calc_t(t_cyl *ret, t_ray *r, double *abc, double *t2)
{
	ret->t0 = (-abc[1] + sqrt(ret->dist)) / (2 * abc[0]);
	ret->t1 = (-abc[1] - sqrt(ret->dist)) / (2 * abc[0]);
	if (ret->t0 < EPSILON && ret->t1 < EPSILON)
		return (ret->t0);
	ret->i = vec_sub(vec_add(r->start,
				vec_scale(ret->t0, r->dir)), ret->pos);
	ret->o = vec_sub(vec_add(r->start,
				vec_scale(ret->t1, r->dir)), ret->pos);
	if (vec_dot(ret->i, ret->n1) > vec_dot(ret->n1, ret->n1)
		|| vec_dot(ret->o, ret->n1) < 0)
		ret->t0 = 200000000;
	if (vec_dot(ret->o, ret->n1) > vec_dot(ret->n1, ret->n1)
		|| vec_dot(ret->o, ret->n1) < 0)
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

static int	check_cylinder(t_mstr *mstr, t_cyl *ret, double *t)
{
	double	z;

	*t = ret->t;
	mstr->new_start = vec_add(ret->r.start, vec_scale(*t, ret->r.dir));
	mstr->ret = &ret->mat;
	z = sqrt(fabs((calc_dist(mstr->new_start, ret->pos)
					* calc_dist(mstr->new_start, ret->pos)
					- ret->radius * ret->radius)));
	ret->n1 = vec_add(ret->pos, vec_scale(z, ret->n));
	if (!ret->cap)
		mstr->n = vec_sub(mstr->new_start, ret->n1);
	else
		mstr->n = ret->n;
	vec_normalize(mstr->n);
	return (1);
}

static int	intersect_cyl(t_mstr *mstr, t_cyl *ret, t_ray *r,
	double *t)
{
	double	abc[3];
	double	t2[2];

	ret->n = vec_normalize(ret->n);
	ret->top = vec_add(ret->pos, vec_scale(ret->h, ret->n));
	ret->hit1 = vec_sub(r->start, ret->pos);
	ret->hit2 = vec_sub(ret->hit1, vec_scale(
				vec_dot(ret->hit1, ret->n), ret->n));
	ret->hit3 = vec_sub(r->dir, vec_scale(
				vec_dot(r->dir, ret->n), ret->n));
	ret->n1 = vec_sub(ret->top, ret->pos);
	abc[0] = vec_dot(ret->hit3, ret->hit3);
	abc[1] = 2 * vec_dot(ret->hit3, ret->hit2);
	abc[2] = vec_dot(ret->hit2, ret->hit2) - (ret->radius * ret->radius);
	ret->dist = abc[1] * abc[1] - (4 * abc[0] * abc[2]);
	if ((abc[0] == 0 || ret->dist < EPSILON))
		return (0);
	ret->t = calc_t(ret, r, abc, t2);
	if (ret->t < EPSILON || ret->t == 200000000 || ret->t > *t)
		return (0);
	return (check_cylinder(mstr, ret, t));
}

int	rtc_cy(t_mstr *mstr, t_ray *r, double *t)
{
	t_cyl	*ret;

	mstr->cur_cy = mstr->cy;
	ret = NULL;
	while (mstr->cur_cy)
	{
		mstr->cur_cy->r.start = r->start;
		mstr->cur_cy->r.dir = r->dir;
		mstr->cur_cy->cap = 0;
		if ((intersect_cyl(mstr, mstr->cur_cy, &mstr->cur_cy->r, t)) == 1)
			ret = mstr->cur_cy;
		mstr->cur_cy = mstr->cur_cy->next;
	}
	if (ret != NULL)
		return (1);
	return (0);
}
