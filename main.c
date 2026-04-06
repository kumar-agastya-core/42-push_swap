#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc < 2)
		return (0);
	a = parse_args(argc, argv);
	if (!a)
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	b = stack_new();
	if (!b)
	{
		stack_free(a);
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	sort(a, b);
	stack_free(a);
	stack_free(b);
	return (0);
}
