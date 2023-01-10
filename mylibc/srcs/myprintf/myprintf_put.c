 

#include "../../incs/mylibc.h"

void	printf_putchar(t_count *print, char c, int fd)
{
	myputchar_fd(c, fd);
	print->chars_printed = print->chars_printed + 1;
}

void	printf_putstr(t_count *print, char *str, int fd)
{
	int	i;

	i = 0;
	if (print->precision && print->format_char == 's')
	{
		while (i < print->precision_len && str[i])
		{
			printf_putchar(print, str[i], fd);
			i++;
		}
		return ;
	}
	myputstr_fd(str, fd);
	print->chars_printed = print->chars_printed + mystrlen(str);
}

void	printf_putnbr(t_count *print, int n, int fd)
{
	char	*str;

	if (n == -2147483648 && print->flag_0)
	{
		printf_putstr(print, "2147483648", fd);
		return ;
	}
	if (n < 0 && print->flag_0)
		n *= -1;
	if (print->flag_plus && print->flag_0
		&& (print->type_d_i > 0 || print->type_u > 0)
		&& print->precision)
		printf_putchar(print, '+', 1);
	str = myitoa(n);
	if (!print->noprint)
		printf_putstr(print, str, fd);
	free(str);
}
