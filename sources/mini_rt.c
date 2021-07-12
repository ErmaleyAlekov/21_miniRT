#include "../includes/mini_rt.h"

void	create_window(t_mrt *mrt)
{
	if (mrt->error == 0 && (mrt->ali == -1 || mrt->cam == NULL))
	{
		ft_putstr_fd("Error, Ambient light or ", 1);
		ft_putstr_fd("Camera are missing\n", 1);
		exit_prog(mrt);
		return ;
	}
	mrt->mlx_ptr = mlx_init();
	mrt->win_ptr = NULL;
	mrt->win_ptr = mlx_new_window(mrt->mlx_ptr, mrt->rx, mrt->ry,
			"MiniRT");
	if (mrt->win_ptr)
		mrt->error = -1;
	mrt->cur_cam = mrt->cam;
	mrt->cur_li = mrt->li;
}

void	parsing_hub(t_mrt *mrt, char *str)
{
	if (str[0] == 'A' && str[1] == ' ')
		parsing_amb(mrt, str);
	else if (str[0] == 'c' && str[1] == 'y' && str[2] == ' ')
		parsing_cylinder(mrt, str);
	else if (str[0] == 'c' && str[1] == ' ')
		parsing_camera(mrt, str);
	else if (str[0] == 'l' && str[1] == ' ')
		parsing_light(mrt, str);
	else if (str[0] == 's' && str[1] == 'p' && str[2] == ' ')
		parsing_sphere(mrt, str);
	else if (str[0] == 'p' && str[1] == 'l' && str[2] == ' ')
		parsing_plane(mrt, str);
	if (mrt->rx > mrt->ry)
		mrt->win_ratio = mrt->rx / mrt->ry;
	else
		mrt->win_ratio = mrt->ry / mrt->rx;
}

int	reading_file(t_mrt *mrt, int fd)
{
	char	*line;
	int		ret;

	mrt->error = 0;
	mrt->rx = 1920;
	mrt->ry = 1160;
	mrt->cam = 0;
	mrt->li = 0;
	mrt->sp = 0;
	mrt->pl = 0;
	mrt->cy = 0;
	mrt->ali = -1;
	ret = 0;
	color_init(&mrt->argb);
	while (ret != -1)
	{
		ret = get_next_line(fd, &line);
		if (mrt->error == 0)
			parsing_hub(mrt, line);
		free(line);
		if (ret == 0)
			break ;
	}
	return (ret);
}

static int	check_args(int argc)
{
	if (argc < 2)
	{
		ft_putstr_fd("Please choose a .rt file\n", 1);
		return (-1);
	}
	if (argc > 2)
	{
		ft_putstr_fd("Too many arguments\n", 1);
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_mrt	mrt;
	int		len;

	mrt.img_ptr = NULL;
	if ((check_args(argc)) == -1)
		return (-1);
	len = ft_strlen(argv[1]);
	if (len < 4 || argv[1][len - 1] != 't' || argv[1][len - 2] != 'r'
		|| argv[1][len - 3] != '.')
	{
		ft_putstr_fd("Please choose a valid .rt file\n", 1);
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error opening file\n", 1);
		return (-1);
	}
	if (reading_file(&mrt, fd) == -1 || mrt.error == 1)
		exit_prog(&mrt);
	create_window(&mrt);
	raytracing(&mrt);
	return (0);
}
