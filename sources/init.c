#include "../includes/mini_rt.h"

void	vec_init(t_vec *v1)
{
	v1->x = -1;
	v1->y = -1;
	v1->z = -1;
}

void	color_init(t_color *rgb)
{
	rgb->r = -1;
	rgb->g = -1;
	rgb->b = -1;
}

void	vec_init_inf(t_vec *v1)
{
	v1->x = 1.0 / 0.0;
	v1->y = 1.0 / 0.0;
	v1->z = 1.0 / 0.0;
}

void	compute_all(t_mstr *mstr)
{
	if (mstr->img_ptr != NULL)
		mlx_destroy_image(mstr->mlx_ptr, mstr->img_ptr);
	mstr->img_ptr = mlx_new_image(mstr->mlx_ptr, mstr->rx, mstr->ry);
	mstr->img_data = mlx_get_data_addr(mstr->img_ptr, &mstr->bpp,
			&mstr->img_size, &mstr->endian);
	mstr->win_scale = tan(deg2rad(mstr->cur_cam->fov * 0.5));
}
