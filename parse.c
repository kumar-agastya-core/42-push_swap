#include "push_swap.h"

static int	has_duplicate(t_stack *s, int val)
{
	t_node	*cur;

	cur = s->top;
	while (cur)
	{
		if (cur->val == val)
			return (1);
		cur = cur->next;
	}
	return (0);
}

static void	parse_token(t_stack *a, char *token)
{
	long	val;

	if (!ft_atoi_safe(token, &val))
	{
		stack_free(a);
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	if (has_duplicate(a, (int)val))
	{
		stack_free(a);
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	stack_push_bottom(a, (int)val);
}

static void	parse_arg(t_stack *a, char *arg)
{
	char	**tokens;
	int		count;
	int		j;

	tokens = ft_split_spaces(arg, &count);
	if (!tokens || count == 0)
	{
		if (tokens)
			free_split(tokens);
		stack_free(a);
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	j = 0;
	while (j < count)
	{
		parse_token(a, tokens[j]);
		j++;
	}
	free_split(tokens);
}

t_stack	*parse_args(int argc, char **argv)
{
	t_stack	*a;
	int		i;

	a = stack_new();
	if (!a)
		return (NULL);
	i = 1;
	while (i < argc)
	{
		parse_arg(a, argv[i]);
		i++;
	}
	return (a);
}
