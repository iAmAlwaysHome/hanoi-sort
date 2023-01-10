#include "../includes/hanoi_sort.h"

void	exit_with_error(void)
{
	myputstr_fd("Error\n", 2);
	exit(1);
}

//print instructions set up as libft.h t_list, after that free lst
static void	print_hanoisort_instructions(t_list *instructions, int i)
{
	if (!instructions)
		return ;
	if (instructions->next)
		print_hanoisort_instructions(instructions->next, i + 1);
	myputstr_fd((char *)instructions->content, 1);
	if (i == 0)
		mylstclear(&instructions, &free);
}

//exits if no parameters are given
//initializes stack a as a libft.h t_list by parsing input str 
//sorts stack a, prints out commands used
//if argc==2 frees memory allocated by mysplit earlier otherwise just exits
int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	t_list	*instructions;
	int		i;

	if (argc == 1)
		return (0);
	argv++;
	if (argc == 2)
		argv = mysplit(argv[0], ' ');
	instructions = NULL;
	b = NULL;
	a = initialize_stack_a(argv);
	sort_stack_a(&a, &b, &instructions);
	print_hanoisort_instructions(instructions, 0);
	if (argc == 2)
	{
		i = 0;
		while (argv[i])
			free(argv[i++]);
		free(argv);
	}
	return (0);
}
