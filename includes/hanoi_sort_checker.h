#ifndef HANOI_SORT_CHECKER_H
# define HANOI_SORT_CHECKER_H
# include "../mylibc/incs/mylibc.h"
#include <stdint.h>

t_list	*initialize_stack_a(char **argv);
void	execute_hanoisort_instruction(t_list **a, t_list **b, char *instr);
int		getn(t_list *lst);
void	exit_with_error(void);

#endif