#include "../includes/hanoi_sort_checker.h"

int	getn(t_list *lst)
{
	return (*(int *)lst->content);
}

static size_t	get_nbr_len(int nbr, char *value)
{
	size_t	nbr_len;

	nbr_len = 1 + (value[0] == '-' || value[0] == '+');
	while (nbr / 10)
	{
		nbr_len++;
		nbr /= 10;
	}
	return (nbr_len);
}

//if str_len does not equal to nbr_len - str includes not numeric chars
//or num parameter > MAXINT which would result in str being > than nbr_len
//allows only numeric char and 1 leading sign char or exits_with_err
//checks list for duplicate numeric parameter and exits with error if needed
//if num parameter > MAXINT atoi will overflow 
static void	check_nbr(int nbr, t_list *head, char *value)
{
	int		i;

	i = -1;
	while (value[++i])
		if ((!myisdigit(value[i]) && value[i] != '-' && value[i] != '+')
			|| (i && (value[i] == '-' || value[i] == '+')))
			exit_with_error();
	while (head)
	{
		if (getn(head) == nbr)
			exit_with_error();
		head = head->next;
	}
	if (get_nbr_len(nbr, value) != mystrlen(value))
		exit_with_error();
}

//use myatoi() to parse **input_str into stack_a list
//only adds element to the list if there are non numeric chars (except -,+) 
//or duplicates for existing elem in stack_a or parameters >MAXINT <MININT
t_list	*initialize_stack_a(char **str)
{
	int		*nbr;
	int		i;
	t_list	*head;

	i = 0;
	while (str[i])
		i++;
	head = NULL;
	while (i--)
	{
		nbr = malloc(sizeof(int));
		*nbr = myatoi(str[i]);
		check_nbr(*nbr, head, str[i]);
		mylstadd_front(&head, mylstnew((void *)nbr));
	}
	return (head);
}
