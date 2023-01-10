#include "../includes/hanoi_sort.h"

//update t_rotate cheapest_rot - min amount of rotations to push n to acc
//calculate the amount of rotates for 4 combinations and store its cost in ops
//rotate: [0] - only ra, [1] - only rb, [2] - rr, [3] - rrr
//sets trotate rot[] rr flags: 
//[0] no rr for a,b; [1] rr for both; [2] rrb but ra [3] rra but rb 
//int i[2] is used for 2 loop idx to minimize amount of lines for norminette
//i[1] is idx of rot case that was cheapest
static void	cheapest_rot(t_list *a, t_list *b, int push_n_i[2], t_rotate *trot)
{
	unsigned int	ops[4];
	unsigned int	min;
	int				i[2];

	ops[0] = dif_m(push_n_i[0], push_n_i[1]) + push_n_i[0];
	min = ops[0];
	ops[1] = dif_m(mylstsize(a) - push_n_i[0], mylstsize(b) - push_n_i[1]) \
				- push_n_i[0] + mylstsize(a) + 1;
	ops[2] = push_n_i[1] - push_n_i[0] + mylstsize(a) + 1;
	ops[3] = push_n_i[0] - push_n_i[1] + mylstsize(b) + 1;
	i[0] = -1;
	while (++i[0] < 4)
	{
		if (ops[i[0]] > min)
			continue ;
		min = ops[i[0]];
		i[1] = i[0];
	}
	if (min >= trot->cheapest_rotation)
		return ;
	trot->cheapest_rotation = min;
	trot->rot[0] = (i[1] == 1 || i[1] == 2);
	trot->rot[1] = (i[1] == 1 || i[1] == 3);
	trot->i_topush[0] = push_n_i[0] - 1;
	trot->i_topush[1] = push_n_i[1] - 1;
}

//set sort_utils 
static void	initialize_tsort(t_sort *sort_utils, t_list *acceptor)
{
	sort_utils->acceptor_2value_gap = UINT32_MAX;
	sort_utils->i_topush = INT32_MAX;
	sort_utils->is_minmax_updated = 0;
	sort_utils->min = getn(acceptor);
	sort_utils->max = getn(acceptor);
	sort_utils->itopush_prev_n = getn(mylstlast(acceptor));
	while (acceptor)
	{
		if (getn(acceptor) < sort_utils->min)
			sort_utils->min = getn(acceptor);
		if (getn(acceptor) > sort_utils->max)
			sort_utils->max = getn(acceptor);
		acceptor = acceptor->next;
	}
}

//get index of acceptor that we will push on top of a n from donor
//until new min/max is set rotate through acceptor 
//returns INT32_MAX if is_1_push_enough()is false for all acc
//sets itopush_prev_n of tsort to be n_acc
static int	acceptor_i_topush_ontopof(t_list *don, t_list *acc, int asc_s)
{
	int			idx;
	t_sort		sort_utils;

	initialize_tsort(&sort_utils, acc);
	idx = 1;
	while (acc)
	{
		if (is_1_push_enough(don, acc, &sort_utils, asc_s))
			sort_utils.i_topush = idx;
		sort_utils.itopush_prev_n = getn(acc);
		if (sort_utils.is_minmax_updated)
			break ;
		idx++;
		acc = acc->next;
	}
	return (sort_utils.i_topush);
}

//update trotate-> idx_topush[2] for 4 cases
//if we rotate: [0] - only ra, [1] - only rb, [2] - both rr, [3] - both rrr
//rotate a - while n_a idx > 0:  ra or rr; rotate b - while n_b idx > 0: rb
static void	rotate_stacks(t_list **a, t_list **b, t_list **ops, t_rotate *tr)
{
	int	rotb;

	rotb = 0;
	if (tr->rot[0])
		tr->i_topush[0] = mylstsize(*a) - tr->i_topush[0];
	if (tr->rot[1])
		tr->i_topush[1] = mylstsize(*b) - tr->i_topush[1];
	if (tr->rot[0] && tr->rot[1] && tr->i_topush[1] && ++rotb)
		tr->i_topush[1] = (tr->i_topush[0] % mylstsize(*b)) - tr->i_topush[1];
	if (!tr->rot[0] && !tr->rot[1] && tr->i_topush[1] && ++rotb)
		tr->i_topush[1] = tr->i_topush[1] - (tr->i_topush[0] % mylstsize(*b));
	while (tr->i_topush[0]--)
	{
		if (tr->rot[0] == tr->rot[1] && rotb)
			rotate(b, tr->rot[1], ops, NULL);
		rotate(a, tr->rot[0], ops, tr->instr_str);
	}
	if (tr->rot[0] == tr->rot[1])
	{
		tr->rot[1] = 0;
		if (tr->i_topush[1] < 0 && ++tr->rot[1])
			tr->i_topush[1] *= -1;
	}
	while (tr->i_topush[1]--)
		rotate(b, tr->rot[1], ops, "b\n");
}

//rotate donor and/or acceptor until with 1 push n can be sorted into acceptor
//in push_pair_idx[] store idx+1 (position) of n to push from donor
//and n that it should be pushed on top of in acceptor
//push_pair_idx[1] is always for b, push_pair_idx[0] for a
//____________________________________________________________________
//to minimize sorting instructions rotate both stacks as the same time
//use trotate to to store direction of rotate instr to find match
void	r_until_1push(t_list **a, t_list **b, t_list **op, int b_to_a)
{
	t_list		*donor;
	t_rotate	rot_utils;
	int			push_pair_idx[2];

	donor = *a;
	if (b_to_a)
		donor = *b;
	rot_utils.cheapest_rotation = INT32_MAX;
	push_pair_idx[b_to_a] = 1;
	while (donor)
	{
		if (!b_to_a)
			push_pair_idx[1] = acceptor_i_topush_ontopof(donor, *b, 1);
		else
			push_pair_idx[0] = acceptor_i_topush_ontopof(donor, *a, 0);
		cheapest_rot(*a, *b, push_pair_idx, &rot_utils);
		push_pair_idx[b_to_a]++;
		donor = donor->next;
	}
	if (rot_utils.i_topush[1] && rot_utils.rot[0] == rot_utils.rot[1])
		rot_utils.instr_str = mystrjoin("r\n", NULL);
	else
		rot_utils.instr_str = mystrjoin("a\n", NULL);
	rotate_stacks(a, b, op, &rot_utils);
	free(rot_utils.instr_str);
}
