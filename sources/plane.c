#include "../includes/mini_rt.h"

static int	intersect_plane(t_plane *ret, t_ray *r, double *t)
{
	double		denom;
	double		a;
	double		b;
	double		dist;

	denom = -vector_dot(ret->pos, ret->n);
	a = vector_dot(ret->n, r->start) + denom;
	b = vector_dot(r->dir, ret->n);
	dist = -(a / b);
	if (dist > EPSILON && dist < *t)
	{
		*t = dist;
		return (1);
	}
	return (0);
}

int	raytracer_pl(t_mrt *mrt, t_ray *r, double *t)
{
	t_plane	*ret;

	mrt->cur_pl = mrt->pl;
	ret = NULL;
	while (mrt->cur_pl)
	{
		mrt->cur_pl->r.start = r->start;
		mrt->cur_pl->r.dir = r->dir;
		if ((intersect_plane(mrt->cur_pl, &mrt->cur_pl->r, t)) == 1)
			ret = mrt->cur_pl;
		mrt->cur_pl = mrt->cur_pl->next;
	}
	if (ret != NULL)
	{
		mrt->new_start = vector_add(ret->r.start, vector_scale(*t, ret->r.dir));
		mrt->n = vector_normalize(ret->n);
		mrt->ret = &ret->mat;
		return (1);
	}
	return (0);
}
