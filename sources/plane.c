#include "../includes/mini_rt.h"

static int	intersect_pl(t_pl *ret, t_ray *r, double *t)
{
	double		denom;
	double		a;
	double		b;
	double		dist;

	denom = -vec_dot(ret->pos, ret->n);
	a = vec_dot(ret->n, r->start) + denom;
	b = vec_dot(r->dir, ret->n);
	dist = -(a / b);
	if (dist > EPSILON && dist < *t)
	{
		*t = dist;
		return (1);
	}
	return (0);
}

int	rtc_pl(t_mstr *mstr, t_ray *r, double *t)
{
	t_pl	*ret;

	mstr->cur_pl = mstr->pl;
	ret = NULL;
	while (mstr->cur_pl)
	{
		mstr->cur_pl->r.start = r->start;
		mstr->cur_pl->r.dir = r->dir;
		if ((intersect_pl(mstr->cur_pl, &mstr->cur_pl->r, t)) == 1)
			ret = mstr->cur_pl;
		mstr->cur_pl = mstr->cur_pl->next;
	}
	if (ret != NULL)
	{
		mstr->new_start = vec_add(ret->r.start, vec_scale(*t, ret->r.dir));
		mstr->n = vec_normalize(ret->n);
		mstr->ret = &ret->mat;
		return (1);
	}
	return (0);
}
