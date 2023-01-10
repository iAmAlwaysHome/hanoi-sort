#include "../includes/hanoi_sort.h"

//find gap between 2 values in acceptor
unsigned int	dif_m(int a, int b)
{
	if (a > b)
		return (a - b);
	else
		return (b - a);
}

//return 1 if when n from donor is pushed on acceptor, acceptor is still sorted
//update min max of tsort if needed and set is_minmax_updated
//if des itopush_prev_n > cur itopush_prev_n (reverse for asc) returns 1
//sets acceptor_2value_gap
//___________________________________________________________
//for the algorithm to work
//b is filled from a in descending order if stack_a == 0 (or a if it is 1)
//store min n and max n for b, to be updated when new min/max is found
//(max n must immediately follow min n as 1 rotate operation will result 
//in sorted b; think of stacks not as lines, but circles - we do not care 
//for the order of n but their sequence because of rotate)
int	is_1_push_enough(t_list *d, t_list *acc, t_sort *ts, int asc)
{
	if (getn(d) < ts->min || getn(d) > ts->max)
	{
		if ((asc && getn(acc) == ts->max) || (!asc && getn(acc) == ts->min))
		{
			ts->is_minmax_updated = 1;
			return (1);
		}
		return (0);
	}
	if (!((asc && ts->itopush_prev_n > getn(d) && getn(d) > getn(acc))
			|| (!asc && ts->itopush_prev_n < getn(d) && getn(d) < getn(acc))))
		return (0);
	ts->acceptor_2value_gap = dif_m(ts->itopush_prev_n, getn(acc));
	return (1);
}

//check all elements of a list to be sorted in asc order
//if return_lst_len == 1 return  returns amount of sorted elem 
//of partially or fully sorted list
//or if return_lst_len == 0 checks the list to be fully sorted
//returns 1 if fully sorted, 0 otherwise
static int	is_sorted(t_list *head, int return_sorted_elem_amount)
{
	int	i;

	i = 0;
	while (head && head->next)
	{
		if (getn(head) > getn(head->next))
			return (i * return_sorted_elem_amount);
		i++;
		head = head->next;
	}
	return ((!return_sorted_elem_amount) + i * return_sorted_elem_amount);
}

//sort 3 nbrs in ascending order by defining operations for each combination
//is_sorted(*a, 1) partially and fully sorted list return n>1, not sorted - 0
//is_sorted(*a, 0) fully sorted list return 1; partially and not sorted - 0
//stack a [x,y,z] numbers (goal: x<y<z; 5 not sorted combinations)
//1. if x,y,z not sorted, and y,z not sorted - y > z && x > y = x > y > z
//2. if x,y,z not sorted, and x>z - x > z && x > y =  x > z > y 
//3. if x,y,z not sorted, and x<z - x < z && x > y = y < x < z
//4. if x,y,z partially sorted, and x > z = y > x > z
//5. if x,y,z partially sorted - y > x && z > x  = y > z > x
static void	sort_3_nbrs(t_list **a, t_list **instructions, char *stack)
{
	if (!is_sorted(*a, 1) && !is_sorted((*a)->next, 0))
	{
		swap(a, instructions, stack);
		rotate(a, 1, instructions, stack);
	}
	else if (!is_sorted(*a, 1) && getn(*a) > getn(mylstlast(*a)))
		rotate(a, 0, instructions, stack);
	else if (!is_sorted(*a, 1) && getn(*a) < getn(mylstlast(*a)))
		swap(a, instructions, stack);
	else if (is_sorted(*a, 1) && getn(*a) > getn(mylstlast(*a)))
		rotate(a, 1, instructions, stack);
	else if (is_sorted(*a, 1) && !is_sorted(*a, 0))
	{
		swap(a, instructions, stack);
		rotate(a, 0, instructions, stack);
	}
}

//fill and sort (descending) b from a, until 3 n left in a or a is_sorted
//rotate donor and/or acceptor until with 1 push n can be sorted in acceptor
//sort (ascending) 3 n in a ; fill and sort (ascending) a from already sorted b
//rotate a until it is sorted (ascending), free memory used by stack lists
void	sort_stack_a(t_list **a, t_list **b, t_list **instructions)
{
	int	reverse_rotate;

	while (mylstsize(*a) > 3 && !is_sorted(*a, 0))
	{
		if (mylstsize(*b) > 1)
			r_until_1push(a, b, instructions, 0);
		push(a, b, instructions, "b\n");
	}
	if (mylstsize(*a) == 2)
		swap(a, instructions, "a\n");
	else
		sort_3_nbrs(a, instructions, "a\n");
	while (*b)
	{
		r_until_1push(a, b, instructions, 1);
		push(b, a, instructions, "a\n");
	}
	reverse_rotate = 0;
	if (is_sorted(*a, 1) + 1 > mylstsize(*a) / 2)
		reverse_rotate = 1;
	while (!is_sorted(*a, 0))
		rotate(a, reverse_rotate, instructions, "a\n");
	mylstclear(a, &free);
	mylstclear(b, &free);
}
