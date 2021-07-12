#include "../includes/mini_rt.h"

void	create_window(t_mstr *mstr)
{
	if (mstr->error == 0 && (mstr->ali == -1 || mstr->cam == NULL))
	{
		printf("Error, Ambient light or ");
		printf("Camera are missing\n");
		exit_prog(mstr);
		return ;
	}
	mstr->mlx_ptr = mlx_init();
	mstr->win_ptr = NULL;
	mstr->win_ptr = mlx_new_window(mstr->mlx_ptr, mstr->rx, mstr->ry,
			"MiniRT");
	if (mstr->win_ptr)
		mstr->error = -1;
	mstr->cur_cam = mstr->cam;
	mstr->cur_li = mstr->li;
}

void	parsing_id(t_mstr *mstr, char *str)
{
	if (str[0] == 'A' && str[1] == ' ')
		parsing_amb(mstr, str);
	else if (str[0] == 'c' && str[1] == 'y' && str[2] == ' ')
		parsing_cylinder(mstr, str);
	else if (str[0] == 'c' && str[1] == ' ')
		parsing_camera(mstr, str);
	else if (str[0] == 'l' && str[1] == ' ')
		parsing_light(mstr, str);
	else if (str[0] == 's' && str[1] == 'p' && str[2] == ' ')
		parsing_sphere(mstr, str);
	else if (str[0] == 'p' && str[1] == 'l' && str[2] == ' ')
		parsing_plane(mstr, str);
	if (mstr->rx > mstr->ry)
		mstr->win_ratio = mstr->rx / mstr->ry;
	else
		mstr->win_ratio = mstr->ry / mstr->rx;
}

int	read_file(t_mstr *mstr, int fd)
{
	char	*line;
	int		ret;

	mstr->error = 0;
	mstr->rx = 1920;
	mstr->ry = 1160;
	mstr->cam = 0;
	mstr->li = 0;
	mstr->sp = 0;
	mstr->pl = 0;
	mstr->cy = 0;
	mstr->ali = -1;
	ret = 0;
	color_init(&mstr->argb);
	while (ret != -1)
	{
		ret = get_next_line(fd, &line);
		if (mstr->error == 0)
			parsing_id(mstr, line);
		free(line);
		if (ret == 0)
			break ;
	}
	return (ret);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_mstr	mstr;
	int		len;

	mstr.img_ptr = NULL;
	if ((check_args(argc, argv[1])) == -1)
		return (-1);
	len = ft_strlen(argv[1]);
	if (len < 4 || argv[1][len - 1] != 't' || argv[1][len - 2] != 'r'
		|| argv[1][len - 3] != '.')
	{
		printf("Error, Please choose a valid .rt file\n");
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file\n");
		return (-1);
	}
	if (read_file(&mstr, fd) == -1 || mstr.error == 1)
		exit_prog(&mstr);
	create_window(&mstr);
	raytracing(&mstr);
	return (0);
}
