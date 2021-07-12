#include "../includes/mini_rt.h"

t_vector	new_vec3(double x, double y, double z)
{
	t_vector	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

unsigned int	min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double	ft_atof(char *str)
{
	double	ret;
	double	tmp;
	int		neg;

	ret = 0;
	neg = 1;
	tmp = 0;
	while (*str && *str != '-' && (*str < '0' || *str > '9'))
		str++;
	ret = (float)ft_atoi(str);
	if (ret < 0)
		str++;
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	if (*str == '.' && *str++)
		tmp = (float)ft_atoi(str);
	while (tmp >= 1.0f)
		tmp *= 0.1;
	ret += tmp;
	return (ret * neg);
}

int	ft_atoi(const char *str)
{
	int	n;
	int	i;
	int	p;

	n = 0;
	i = 0;
	p = 1;
	while (str[i] == '\n' || str[i] == '\v' || str[i] == '\t'
		|| str[i] == ' ' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-')
	{
		n = -n;
		p = -1;
	}
	else if (str[i] != '+')
		i--;
	while (str[++i] >= '0' && str[i] <= '9')
		n = n * 10 + (str[i] - '0');
	return (n * p);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
}
