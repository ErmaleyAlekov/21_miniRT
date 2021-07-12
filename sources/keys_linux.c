#include "../includes/mini_rt.h"

static	int	handle_key2(int key_code, t_mstr *mstr)
{
	if (key_code == 41)
	{
		if (mstr->cur_cam->next)
			mstr->cur_cam = mstr->cur_cam->next;
		raytracing(mstr);
	}
	else if (key_code == 24)
	{
		mstr->cur_cam = mstr->cam;
		raytracing(mstr);
	}
	return (1);
}

int	handle_key(int key_code, t_mstr *mstr)
{
	if (key_code == 9)
		exit_prog(mstr);
	else if (key_code == 62)
	{
		mstr->cur_cam->pos.x += mstr->cur_cam->fov / 5;
		raytracing(mstr);
	}
	else if (key_code == 68)
	{
		mstr->cur_cam->pos.x -= mstr->cur_cam->fov / 5;
		raytracing(mstr);
	}
	else if (key_code == 66)
	{
		mstr->cur_cam->pos.y += mstr->cur_cam->fov / 5;
		raytracing(mstr);
	}
	else if (key_code == 64)
	{
		mstr->cur_cam->pos.y -= mstr->cur_cam->fov / 5;
		raytracing(mstr);
	}
	return (handle_key2(key_code, mstr));
}

int	handle_mouse(int key_code, int x, int y, t_mstr *mstr)
{
	x = y;
	y = x;
	if (key_code == 4)
	{
		mstr->cur_cam->pos.z -= 5;
		raytracing(mstr);
	}
	else if (key_code == 5)
	{
		mstr->cur_cam->pos.z += 5;
		raytracing(mstr);
	}
	return (1);
}

int	exit_prog(t_mstr *mstr)
{
	no_leaks(mstr);
	exit(1);
	return (1);
}
