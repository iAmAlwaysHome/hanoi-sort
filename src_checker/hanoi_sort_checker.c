#include "../includes/hanoi_sort_checker.h"

void	exit_with_error(void)
{
	myputstr_fd("Error\n", 2);
	exit(1);
}

static void	free_memory(char **input_str, t_list *a, t_list *b, int argc)
{
	int	i;

	mylstclear(&a, &free);
	mylstclear(&b, &free);
	if (argc == 2)
	{
		i = 0;
		while (input_str[i])
			free(input_str[i++]);
		free(input_str);
	}
}

//check all elements of a list to be sorted in asc order
static int	is_sorted(t_list *begin)
{
	while (begin && begin->next)
	{
		if (getn(begin) > getn(begin->next))
			return (0);
		begin = begin->next;
	}
	return (1);
}

//read stdin with get_next_line into buf, write buf into pipe with pipe_fd[1]
//read pipe data from pipe_fd[0] with get_next_line into buffer 
//execute_hanoisort_instruction, free used line, get next; when done - close fd
//_________________________________________________________________________
//int pipe(int fds[2]) 
//fd[0] fd for reading data from the pipe, fd[1] - for writing data to the pipe
static void	execute_from_pipe(int pipe_fd[2], t_list **a, t_list **b)
{
	char	*buffer;

	pipe(pipe_fd);
	buffer = get_next_line(0);
	while (buffer)
	{
		write(pipe_fd[1], buffer, mystrlen(buffer));
		if (buffer)
			free(buffer);
		buffer = get_next_line(0);
	}
	if (buffer)
		free(buffer);
	close(pipe_fd[1]);
	buffer = get_next_line(pipe_fd[0]);
	while (buffer)
	{
		execute_hanoisort_instruction(a, b, buffer);
		if (buffer)
			free(buffer);
		buffer = get_next_line(pipe_fd[0]);
	}
	close(pipe_fd[0]);
}

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	int		pipe_fd[2];

	if (argc == 1)
		return (0);
	argv++;
	if (argc == 2)
		argv = mysplit(argv[0], ' ');
	b = NULL;
	a = initialize_stack_a(argv);
	execute_from_pipe(pipe_fd, &a, &b);
	if (is_sorted(a) && !b)
		myputstr_fd("OK\n", 1);
	else
		myputstr_fd("KO\n", 1);
	free_memory(argv, a, b, argc);
	return (0);
}
