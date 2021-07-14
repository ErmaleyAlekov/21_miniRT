#include "../includes/mini_rt.h"

static int	find_closest_sp(float discr, double c, double b, double *t)
{
	discr = sqrt(discr);
	c = (-b + discr) / 2;
	b = (-b - discr) / 2;
	if (c > b)
		c = b;
	if ((c > 0.001f) && (c < *t))
		*t = c;
	else
		return (0);
	return (1);
}

static int	intersect_sp(t_ray *r, t_sp *s, double *t, int level)
{
	double		b;
	double		c;
	t_vec		dist;
	float		discr;

	if (level)
		s->save.a = vec_dot(s->r.dir, s->r.dir);
	dist = vec_sub(r->start, s->pos);
	b = 2 * vec_dot(r->dir, dist);
	c = vec_dot(dist, dist) - (s->radius * s->radius);
	discr = b * b - 4 * s->save.a * c;
	if (discr < 0)
		return (0);
	else
		return (find_closest_sp(discr, c, b, t));
}

static int	check_sphere(t_mstr *mstr, double *t, t_sp *ret)
{
	double		tmp;

	tmp = *t;
	mstr->scaled = vec_scale(*t, ret->r.dir);
	mstr->new_start = vec_add(ret->r.start, mstr->scaled);
	mstr->n = vec_sub(mstr->new_start, ret->pos);
	*t = vec_dot(mstr->n, mstr->n);
	if (*t == 0)
	{
		*t = tmp;
		return (0);
	}
	*t = 1.0f / sqrt(*t);
	mstr->n = vec_scale(*t, mstr->n);
	mstr->ret = &ret->mat;
	mstr->n = vec_normalize(mstr->n);
	return (1);
}

int	rtc_sp(t_mstr *mstr, t_ray *r, double *t, int level)
{
	t_sp	*ret;

	mstr->cur_sp = mstr->sp;
	ret = NULL;
	while (mstr->cur_sp)
	{
		mstr->cur_sp->r.start = r->start;
		mstr->cur_sp->r.dir = r->dir;
		mstr->cur_sp->save.a = vec_dot(mstr->cur_sp->r.dir,
				mstr->cur_sp->r.dir);
		if (intersect_sp(&mstr->cur_sp->r, mstr->cur_sp, t, level) == 1)
			ret = mstr->cur_sp;
		mstr->cur_sp = mstr->cur_sp->next;
	}
	if (ret != NULL)
		return ((check_sphere(mstr, t, ret)));
	return (0);
}
