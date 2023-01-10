 

#include "../../incs/mylibc.h"

void	myargument_size(t_count *print)
{
	if (print->format_char == 'd' || print->format_char == 'i')
		print->arg_len = mysize(print->type_d_i);
	if (print->format_char == 'u')
		print->arg_len = mysize_unsigned(print->type_u);
	if (print->format_char == 'x' || print->format_char == 'X')
		mysize_hex(print, print->type_x_x);
	if (print->format_char == 'c' || print->format_char == '%')
		print->arg_len = 1;
	if (print->format_char == 's' && print->type_s)
		print->arg_len = mystrlen(print->type_s);
	if (print->format_char == 'p')
	{
		mysize_p(print, print->type_p);
		print->arg_len += 2;
	}
}

int	mysize(int n)
{
	int		i;
	long	nbr;

	nbr = n;
	i = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	while (nbr >= 10)
	{
		nbr /= 10;
		i++;
	}
	i++;
	return (i);
}

int	mysize_unsigned(unsigned int n)
{
	int	i;

	i = 0;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	i++;
	return (i);
}

void	mysize_hex(t_count *print, unsigned int n)
{
	if (n >= 16)
	{
		mysize_hex(print, n / 16);
		mysize_hex(print, n % 16);
	}
	else
		print->arg_len = print->arg_len + 1;
}

void	mysize_p(t_count *print, unsigned long n)
{
	if (n >= 16)
	{
		mysize_p(print, n / 16);
		mysize_p(print, n % 16);
	}
	else
		print->arg_len = print->arg_len + 1;
}
