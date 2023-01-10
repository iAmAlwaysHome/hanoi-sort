/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myprint_specifiers_checker.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprotsen <eprotsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 01:44:45 by eprotsen          #+#    #+#             */
/*   Updated: 2022/10/22 01:44:46 by eprotsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/mylibc.h"

void	print_specifiers(t_count *print)
{
	myargument_size(print);
	if (print->format_char == 's' && !print->type_s)
	{
		print->type_s = "(null)";
		print->arg_len = 6;
	}
	if (print->precision)
		print_precision(print);
	print_sign(print);
	if (print->flag_minus)
	{
		print->flag_minus = print->width;
		print->width = 0;
	}
	else if (print->flag_0 && !print->precision
		&& print->format_char != 's' && print->format_char != 'c')
	{
		print->flag_0_len = print->width;
		print->width = 0;
	}
	print_width(print);
	print_flag_0(print);
}

void	print_precision(t_count *print)
{
	if (print->format_char == 'd' || print->format_char == 'i'
		|| print->format_char == 'u' || print->format_char == 'x'
		|| print->format_char == 'X')
	{
		if (!print->type_d_i && !print->type_u && !print->type_x_x
			&& !print->precision_len)
		{
			print->noprint = 1;
			print->arg_len--;
		}
		if (print->type_d_i < 0)
				print->arg_len--;
		if (print->arg_len < print->precision_len)
		{
			print->flag_0 = 1;
			print->flag_0_len = print->precision_len;
		}
	}
	if (print->format_char == 's')
	{
		if (print->arg_len < print->precision_len)
			print->precision_len = print->arg_len;
		print->arg_len = print->precision_len;
	}
}

void	print_sign(t_count *print)
{
	if (print->flag_plus)
		print->arg_len++;
	if (print->flag_plus && !print->precision && print->type_d_i >= 0
		&& print->format_char == 'i')
		printf_putchar(print, '+', 1);
	else if (print->flag_plus && !print->precision && print->type_d_i >= 0
		&& print->format_char == 'd')
		printf_putchar(print, '+', 1);
	else if (print->flag_plus && !print->precision && print->format_char == 'u')
		printf_putchar(print, '+', 1);
	if (print->flag_space && !print->precision && print->type_d_i >= 0
		&& print->format_char == 'd')
		printf_putchar(print, ' ', 1);
	else if (print->flag_space && !print->precision && print->type_d_i >= 0
		&& print->format_char == 'i')
		printf_putchar(print, ' ', 1);
	else if (print->flag_space && !print->precision
		&& print->format_char == 'u')
		printf_putchar(print, ' ', 1);
}

void	print_width(t_count *print)
{
	int	i;

	i = 0;
	if (print->type_d_i < 0 && print->flag_0)
		print->width--;
	if (print->precision && print->precision_len > print->arg_len)
	{
		print->width -= print->precision_len;
		print->width += print->arg_len;
	}
	while (i < print->width - print->arg_len)
	{
		printf_putchar(print, ' ', 1);
		i++;
	}
}

void	print_flag_0(t_count *print)
{
	int	i;

	i = 0;
	if (print->type_d_i < 0 && print->flag_0)
	{
		print->flag_0_len++;
		print->arg_len++;
		printf_putchar(print, '-', 1);
	}
	while (i < print->flag_0_len - print->arg_len)
	{
		printf_putchar(print, '0', 1);
		i++;
	}
}
