#include "../includes/hanoi_sort.h"

static t_list	*add_new_instr_tolist(t_list *instr, char *op)
{
	t_list	*new;

	if (!op)
		exit_with_error();
	new = mylstnew((void *)op);
	if (!new)
		exit_with_error();
	mylstadd_front(&instr, new);
	return (instr);
}

//rotate through list, set pretail to make rot possible connect pretail to head
//skip 1 elem to be added to list when needed w/o losing pretail to head link
void	rotate(t_list **head, int reverse, t_list **instr, char *str)
{
	t_list	*pretail;
	t_list	*head_cpy;

	if (!(*head) || !(*head)->next)
		return ;
	pretail = *head;
	while (pretail->next->next)
		pretail = pretail->next;
	pretail->next->next = *head;
	if (!reverse)
	{
		head_cpy = (*head)->next;
		(*head)->next = NULL;
		*head = head_cpy;
		if (str)
			*instr = add_new_instr_tolist(*instr, mystrjoin("r", str));
	}
	else
	{
		*head = pretail->next;
		pretail->next = NULL;
		if (str)
			*instr = add_new_instr_tolist(*instr, mystrjoin("rr", str));
	}
}

void	swap(t_list **head, t_list **instr, char *str)
{
	t_list	*swap;

	if (!(*head) || !(*head)->next)
		return ;
	swap = (*head)->next;
	(*head)->next = swap->next;
	swap->next = *head;
	*head = swap;
	*instr = add_new_instr_tolist(*instr, mystrjoin("s", str));
}

void	push(t_list **don, t_list **acc, t_list **instr, char *str)
{
	t_list	*swap;

	if (!(*don))
		return ;
	swap = (*don)->next;
	(*don)->next = *acc;
	*acc = *don;
	*don = swap;
	*instr = add_new_instr_tolist(*instr, mystrjoin("p", str));
}
