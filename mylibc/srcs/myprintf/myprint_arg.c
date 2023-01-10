 

#include "../../incs/mylibc.h"

void	print_arg(t_count *print, va_list args)
{
	if (print->format_char == 'u')
	{
		print->type_u = va_arg(args, unsigned int);
		print_specifiers(print);
		print_u(print, print->type_u, 1);
	}
	else if (print->format_char == 'x' || print->format_char == 'X')
	{
		print->type_x_x = va_arg(args, unsigned int);
		print_specifiers(print);
		if (print->flag_hash && print->type_x_x && print->format_char == 'x')
			printf_putstr(print, "0x", 1);
		if (print->flag_hash && print->type_x_x && print->format_char == 'X')
			printf_putstr(print, "0X", 1);
		print_x(print, print->type_x_x, 1);
	}
	else if (print->format_char == 'd' || print->format_char == 'i')
	{
		print->type_d_i = va_arg(args, int);
		print_specifiers(print);
		printf_putnbr(print, print->type_d_i, 1);
	}
	else
		print_arg2(print, args);
	print_flag_minus(print);
}

void	print_arg2(t_count *print, va_list args)
{
	if (print->format_char == 'c')
	{
		print->type_c = va_arg(args, int);
		print_specifiers(print);
		printf_putchar(print, print->type_c, 1);
	}
	else if (print->format_char == 's')
	{
		print->type_s = va_arg(args, char *);
		print_specifiers(print);
		printf_putstr(print, print->type_s, 1);
	}
	else if (print->format_char == 'p')
	{
		print->type_p = va_arg(args, unsigned long);
		print_specifiers(print);
		if (!print->flag_0)
			printf_putstr(print, "0x", 1);
		print_p(print, print->type_p, 1);
	}
	else if (print->format_char == '%')
	{
		print_specifiers(print);
		printf_putchar(print, '%', 1);
	}
}

void	print_flag_minus(t_count *print)
{
	int	i;

	i = 0;
	if (print->precision && print->precision_len > print->arg_len)
		print->arg_len = print->precision_len;
	if (print->precision && print->type_d_i < 0)
		print->arg_len++;
	while (i < print->flag_minus - print->arg_len)
	{
		printf_putchar(print, ' ', 1);
		i++;
	}
}
