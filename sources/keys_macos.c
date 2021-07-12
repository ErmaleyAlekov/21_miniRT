#include "../includes/mini_rt.h"

static	int	handle_key2(int key_code, t_mrt *mrt)
{
	if (key_code == 18)
	{
		if (mrt->cur_cam->next)
			mrt->cur_cam = mrt->cur_cam->next;
		raytracing(mrt);
	}
	else if (key_code == 19)
	{
		mrt->cur_cam = mrt->cam;
		raytracing(mrt);
	}
	return (1);
}

int	handle_key(int key_code, t_mrt *mrt)
{
	if (key_code == 53)
		exit_prog(mrt);
	else if (key_code == 124)
	{
		mrt->cur_cam->pos.x += mrt->cur_cam->fov / 5;
		raytracing(mrt);
	}
	else if (key_code == 123)
	{
		mrt->cur_cam->pos.x -= mrt->cur_cam->fov / 5;
		raytracing(mrt);
	}
	else if (key_code == 126)
	{
		mrt->cur_cam->pos.y += mrt->cur_cam->fov / 5;
		raytracing(mrt);
	}
	else if (key_code == 125)
	{
		mrt->cur_cam->pos.y -= mrt->cur_cam->fov / 5;
		raytracing(mrt);
	}
	return (handle_key2(key_code, mrt));
}

int	handle_mouse(int key_code, int x, int y, t_mrt *mrt)
{
	x = y;
	y = x;
	if (key_code == 4)
	{
		mrt->cur_cam->pos.z -= 3;
		raytracing(mrt);
	}
	else if (key_code == 5)
	{
		mrt->cur_cam->pos.z += 3;
		raytracing(mrt);
	}
	return (1);
}

int	exit_prog(t_mrt *mrt)
{
	no_leaks(mrt);
	exit(1);
	return (1);
}
