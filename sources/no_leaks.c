#include "../includes/mini_rt.h"

static void	free_objects(t_mstr *mstr)
{
	while (mstr->sp)
	{
		mstr->cur_sp = mstr->sp;
		mstr->sp = mstr->sp->next;
		free(mstr->cur_sp);
		mstr->cur_sp = NULL;
	}
	while (mstr->pl)
	{
		mstr->cur_pl = mstr->pl;
		mstr->pl = mstr->pl->next;
		free(mstr->cur_pl);
		mstr->cur_pl = NULL;
	}
	while (mstr->cy)
	{
		mstr->cur_cy = mstr->cy;
		mstr->cy = mstr->cy->next;
		free(mstr->cur_cy);
		mstr->cur_cy = NULL;
	}
}

void	no_leaks(t_mstr *mstr)
{
	if (mstr->mlx_ptr && mstr->win_ptr)
		mlx_destroy_window(mstr->mlx_ptr, mstr->win_ptr);
	free_objects(mstr);
}
