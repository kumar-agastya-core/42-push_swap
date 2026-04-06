#include "push_swap.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	write(fd, s, len);
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v');
}

static int	read_sign(const char **s)
{
	int	sign;

	sign = 1;
	if (**s == '-')
	{
		sign = -1;
		(*s)++;
	}
	else if (**s == '+')
		(*s)++;
	return (sign);
}

int	ft_atoi_safe(const char *s, long *result)
{
	long	n;
	int		sign;

	n = 0;
	sign = read_sign(&s);
	if (!ft_isdigit(*s))
		return (0);
	while (ft_isdigit(*s))
	{
		n = n * 10 + (*s - '0');
		if (n > 2147483648L)
			return (0);
		s++;
	}
	if (*s != '\0')
		return (0);
	*result = n * sign;
	if (*result > INT_MAX || *result < INT_MIN)
		return (0);
	return (1);
}
