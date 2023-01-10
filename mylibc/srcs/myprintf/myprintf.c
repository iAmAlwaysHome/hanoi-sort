#include "../../incs/mylibc.h"

//every struct field except chars_printed is set to 0
void	clear_struct(t_count *print)
{
	print->format_char = 0;
	print->type_c = 0;
	print->type_u = 0;
	print->type_s = 0;
	print->type_d_i = 0;
	print->type_x_x = 0;
	print->type_p = 0;
	print->flag_0 = 0;
	print->flag_0_len = 0;
	print->precision = 0;
	print->precision_len = 0;
	print->flag_minus = 0;
	print->flag_space = 0;
	print->flag_hash = 0;
	print->flag_plus = 0;
	print->width = 0;
	print->arg_len = 0;
	print->noprint = 0;
}

void	print_format_string(const char *s, t_count *print, va_list args)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	str = 0;
	while (s[i])
	{
		j = 0;
		if (s[i] == '%')
		{
			i++;
			while (!mystrchr("cspdiuxX%%", s[i + j]))
				j++;
			str = mysubstr(s + i, 0, j + 1);
			set_format_specifier(print, str);
			print_arg(print, args);
			i += mystrlen(str) - 1;
			free(str);
			clear_struct(print);
		}
		else
			printf_putchar(print, s[i], 1);
		i++;
	}
}

int	myprintf(const char *s, ...)
{
	va_list		args;
	t_count		*print;

	print = malloc(sizeof(t_count));
	if (print == NULL)
		return (-1);
	clear_struct(print);
	print->chars_printed = 0;
	va_start(args, s);
	print_format_string(s, print, args);
	va_end(args);
	free(print);
	return (print->chars_printed);
}
