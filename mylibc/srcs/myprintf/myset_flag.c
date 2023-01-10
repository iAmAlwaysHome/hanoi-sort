 

#include "../../incs/mylibc.h"

void	set_flag_plus(t_count *print, int *i, char *str)
{
	print->flag_plus = 1;
	(*i)++;
	while (str[*i] == '+')
		(*i)++;
}

void	set_flag_minus(t_count *print, int *i)
{
	print->flag_minus = 1;
	(*i)++;
}

void	set_flag_hash(t_count *print, int *i)
{
	print->flag_hash = 1;
	(*i)++;
}

void	set_flag_space(t_count *print, int *i)
{
	print->flag_space = 1;
	(*i)++;
}

void	set_flag_0(t_count *print, int *i)
{
	print->flag_0 = 1;
	(*i)++;
}
