 

#include "../../incs/mylibc.h"

void	set_format_specifier(t_count *print, char *str)
{
	int	i;

	i = 0;
	while (str[i] && !mystrchr("csdiupxX%%", str[i]))
	{
		if (str[i] == '+')
			set_flag_plus(print, &i, str);
		if (str[i] == '-')
			set_flag_minus(print, &i);
		if (str[i] == '#')
			set_flag_hash(print, &i);
		if (str[i] == ' ')
			set_flag_space(print, &i);
		else if (str[i] == '0')
			set_flag_0(print, &i);
		if (myisdigit(str[i]))
			set_width(print, &i, str);
		if (str[i] == '.')
			set_precision(print, &i, str);
	}
	print->format_char = str[i];
}

void	set_width(t_count *print, int *i, char *str)
{
	while (!mystrchr(" -+#.csdiupxX%%", str[*i]))
	{
		print->width = (print->width * 10) + (str[*i] - '0');
		(*i)++;
	}
}

void	set_precision(t_count *print, int *i, char *str)
{
	print->precision = 1;
	(*i)++;
	while (!mystrchr(" -+#.csdiupxX%%", str[*i]))
	{
		print->precision_len = (print->precision_len * 10) + (str[*i] - '0');
		(*i)++;
	}
}
