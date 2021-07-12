#include "../includes/mini_rt.h"

void	check_vec_error(t_mstr *mstr, t_vec v1, t_vec v2, t_vec v3)
{
	if (v1.x == -1 || v1.y == -1 || v1.z == -1)
		mstr->error = 1;
	if (v2.x == -1 || v2.y == -1 || v2.z == -1)
		mstr->error = 1;
	if (v3.x == -1 || v3.y == -1 || v3.z == -1)
		mstr->error = 1;
}

void	check_color_error(t_mstr *mstr, t_color col)
{
	if (col.r < 0 || col.r > 255)
		mstr->error = 1;
	if (col.g < 0 || col.g > 255)
		mstr->error = 1;
	if (col.b < 0 || col.b > 255)
		mstr->error = 1;
}

void	check_vec_error_inf(t_mstr *mstr, t_vec v1, t_vec v2,
	t_vec v3)
{
	if (v1.x == 1.0 / 0.0 || v1.y == 1.0 / 0.0 || v1.z == 1.0 / 0.0)
		mstr->error = 1;
	if (v2.x == 1.0 / 0.0 || v2.y == 1.0 / 0.0 || v2.z == 1.0 / 0.0)
		mstr->error = 1;
	if (v3.x == 1.0 / 0.0 || v3.y == 1.0 / 0.0 || v3.z == 1.0 / 0.0)
		mstr->error = 1;
}

int	check_args(int argc, char *argv)
{
	if (argc < 2)
	{
		printf("Error, Please choose a .rt file\n");
		return (-1);
	}
	if (ft_strcmp(argv, "uterese") == 0)
	{
		printf("I`m glade to see you daddy!\n");
		return (-1);
	}
	if (argc > 2)
	{
		printf("Error, Too many arguments\n");
		return (-1);
	}
	return (0);
}
