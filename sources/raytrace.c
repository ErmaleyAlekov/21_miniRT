#include "../includes/mini_rt.h"

static void	init_inner_loop(t_mstr *mstr, int *level, int x, int y)
{
	*level = -1;
	mstr->new_start.z = -1;
	mstr->new_start.x = (2 * (x + 0.5) / mstr->rx - 1)
		* mstr->win_ratio * mstr->win_scale;
	mstr->new_start.y = (1 - 2 * (y + 0.5) / mstr->ry) * mstr->win_scale;
	compute_camera(mstr, mstr->new_start.x, mstr->new_start.y);
	mstr->new_start.x += mstr->cur_cam->pos.x;
	mstr->new_start.y += mstr->cur_cam->pos.y;
	mstr->new_start.z = mstr->cur_cam->pos.z;
	mstr->tmpr = mstr->argb.r;
	mstr->tmpg = mstr->argb.g;
	mstr->tmpb = mstr->argb.b;
	mstr->rcoef = 1.0f;
}

static int	img_to_window(t_mstr *mstr)
{
	mlx_put_image_to_window(mstr->mlx_ptr, mstr->win_ptr, mstr->img_ptr, 0, 0);
	return (1);
}

static int	rtc_end(t_mstr *mstr)
{
	img_to_window(mstr);
	mlx_hook(mstr->win_ptr, 17, 1L << 17, exit_prog, mstr);
	mlx_hook(mstr->win_ptr, 15, 1L << 16, img_to_window, mstr);
	mlx_key_hook(mstr->win_ptr, handle_key, mstr);
	mlx_mouse_hook(mstr->win_ptr, handle_mouse, mstr);
	mlx_loop(mstr->mlx_ptr);
	mstr->first_call = 0;
	return (1);
}

static void	call_obj(t_mstr *mstr, double *t, int level)
{
	*t = 1.0 / 0.0;
	mstr->ret = NULL;
	mstr->r.start = mstr->new_start;
	mstr->r.dir = mstr->new_dir;
	if (mstr->sp != NULL)
		rtc_sp(mstr, &mstr->r, t, level);
	if (mstr->cy != NULL)
		rtc_cy(mstr, &mstr->r, t);
	if (mstr->pl != NULL)
		rtc_pl(mstr, &mstr->r, t);
	if (mstr->ret == NULL)
		return ;
	check_light(mstr->ret, mstr->n, mstr, t);
}

int	raytracing(t_mstr *mstr)
{
	int			x;
	int			y;
	double		t;
	int			level;

	compute_all(mstr);
	y = -1;
	while (++y < mstr->ry)
	{
		x = -1;
		while (++x < mstr->rx)
		{
			init_inner_loop(mstr, &level, x, y);
			while (++level < 15 && mstr->rcoef > 0.0f)
			{
				call_obj(mstr, &t, level);
				if (mstr->ret == NULL)
					break ;
			}
			*(int *)(mstr->img_data + (x * 4 + (mstr->img_size * y)))
				= rgb_mng(mstr->tmpr, mstr->tmpg, mstr->tmpb);
		}
	}
	rtc_end(mstr);
	return (1);
}
