#include "../includes/hanoi_sort_checker.h"

static void	swap(t_list **stack, t_list **a, t_list **b)
{
	t_list	*tmp;

	if (!stack)
	{
		swap(b, a, b);
		stack = a;
	}
	if (!(*stack) || !(*stack)->next)
		return ;
	tmp = (*stack)->next;
	(*stack)->next = tmp->next;
	tmp->next = *stack;
	*stack = tmp;
}

static void	push(t_list **stack, t_list **a, t_list **b)
{
	t_list	*tmp;
	t_list	**donor;

	if (stack == b)
		donor = a;
	else
		donor = b;
	if (!(*donor))
		return ;
	tmp = (*donor)->next;
	(*donor)->next = *stack;
	*stack = *donor;
	*donor = tmp;
}

//rotate through list, set pretail to make rot possible connect pretail to head
//skip 1 elem to be added to list when needed w/o losing pretail to head link
static int	rotate(t_list **stack, t_list **a, t_list **b, int reverse)
{
	t_list	*pretail;
	t_list	*tmp;

	if (!stack && *b && rotate(b, a, b, reverse))
		stack = a;
	if (!stack || !(*stack) || !(*stack)->next)
		return (1);
	pretail = *stack;
	while (pretail->next->next)
		pretail = pretail->next;
	pretail->next->next = *stack;
	if (!reverse)
	{
		tmp = (*stack)->next;
		(*stack)->next = NULL;
		*stack = tmp;
	}
	else
	{
		*stack = pretail->next;
		pretail->next = NULL;
	}
	return (1);
}

//exits if instruction is not one of the allowed by hanoi_sort pdf specs
void	execute_hanoisort_instruction(t_list **a, t_list **b, char *instr)
{
	t_list	**stack;

	stack = NULL;
	if (instr[mystrlen(instr) - 2] == 'a')
		stack = a;
	else if (instr[mystrlen(instr) - 2] == 'b')
		stack = b;
	if ((instr[1] != 'a' && instr[1] != 'b' && instr[1] != instr[0])
		|| mystrlen(instr) > 4 || mystrlen(instr) < 3)
		exit_with_error();
	if (instr[0] == 's')
		swap(stack, a, b);
	else if (instr[0] == 'p')
		push(stack, a, b);
	else if (instr[0] == 'r' && mystrlen(instr) == 4)
		rotate(stack, a, b, 1);
	else if (instr[0] == 'r' && mystrlen(instr) == 3)
		rotate(stack, a, b, 0);
	else
		exit_with_error();
}
