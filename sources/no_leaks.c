#include "../includes/mini_rt.h"

static void	free_objects(t_mrt *mrt)
{
	while (mrt->sp)
	{
		mrt->cur_sp = mrt->sp;
		mrt->sp = mrt->sp->next;
		free(mrt->cur_sp);
		mrt->cur_sp = NULL;
	}
	while (mrt->pl)
	{
		mrt->cur_pl = mrt->pl;
		mrt->pl = mrt->pl->next;
		free(mrt->cur_pl);
		mrt->cur_pl = NULL;
	}
	while (mrt->cy)
	{
		mrt->cur_cy = mrt->cy;
		mrt->cy = mrt->cy->next;
		free(mrt->cur_cy);
		mrt->cur_cy = NULL;
	}
}

void	no_leaks(t_mrt *mrt)
{
	if (mrt->mlx_ptr && mrt->win_ptr)
		mlx_destroy_window(mrt->mlx_ptr, mrt->win_ptr);
	free_objects(mrt);
}
