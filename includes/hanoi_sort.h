#ifndef HANOI_SORT_H
# define HANOI_SORT_H
# include "../mylibc/incs/mylibc.h"
#include <stdint.h>

//used for sorting and getting lst idx of n cheap to push
//to sort (descending) min must be on top of max (reverse for ascending)
//dif and itopush_prev_n are used to decide if we can just push n on top of acc
typedef struct s_sort {
	int				min;
	int				max;
	unsigned int	acceptor_2value_gap;
	int				i_topush;
	int				itopush_prev_n;
	int				is_minmax_updated;
}	t_sort;

//i_topush[] - idx of [0] a [1] b; donor i will be pushed on top of acceptor
//rot[] - flags for reverse rotation of [0] a [1] b to use rr rrr for both
//cheapest_rotation - min amount of rotations to push n to acc
//instr_str - a single instruction 
typedef struct s_rotate {
	int				i_topush[2];
	int				rot[2];
	unsigned int	cheapest_rotation;
	char			*instr_str;
}	t_rotate;

void			exit_with_error(void);

//exits if parameters are nonnumeric, duplicate numeric or >MAXINT <MININT
t_list			*initialize_stack_a(char **argv);
int				getn(t_list *lst);

//add new members to instructions list, store instruction str as their content
void			push(t_list **don, t_list **acc, t_list **instr, char *str);
void			swap(t_list **head, t_list **instr, char *str);
//rotate through list, set tail, to make rot possible connect tail to head
//skip 1 element to be added to list when needed w/o losing tail to head link
void			rotate(t_list **head, int reverse, t_list **instr, char *str);

//fill and sort (descending) b from a, until 3 n left in a or a is_sorted
//sort (ascending) 3 n in a ; fill and sort (ascending) a from already sorted b
//rotate a until it is sorted (ascending), free memory used by stack lists
void			sort_stack_a(t_list **a, t_list **b, t_list **instr);
unsigned int	dif_m(int a, int b);

//rotate donor and/or acceptor until with 1 push n can be sorted in acceptor
void			r_until_1push(t_list **a, t_list **b, t_list **op, int b_to_a);

//return 1 if when n from donor is pushed on acceptor, acceptor is still sorted
int				is_1_push_enough(t_list *d, t_list *acc, t_sort *ts, int asc);

#endif
