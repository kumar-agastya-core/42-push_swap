#include "push_swap.h"

int	stack_min_pos(t_stack *s)
{
	t_node	*cur;
	int		min_val;
	int		min_pos;
	int		pos;

	if (!s->top)
		return (-1);
	cur = s->top;
	min_val = cur->val;
	min_pos = 0;
	pos = 0;
	while (cur)
	{
		if (cur->val < min_val)
		{
			min_val = cur->val;
			min_pos = pos;
		}
		pos++;
		cur = cur->next;
	}
	return (min_pos);
}

int	stack_max_pos(t_stack *s)
{
	t_node	*cur;
	int		max_val;
	int		max_pos;
	int		pos;

	if (!s->top)
		return (-1);
	cur = s->top;
	max_val = cur->val;
	max_pos = 0;
	pos = 0;
	while (cur)
	{
		if (cur->val > max_val)
		{
			max_val = cur->val;
			max_pos = pos;
		}
		pos++;
		cur = cur->next;
	}
	return (max_pos);
}

int	is_sorted(t_stack *s)
{
	t_node	*cur;

	if (!s || s->size <= 1)
		return (1);
	cur = s->top;
	while (cur->next)
	{
		if (cur->val > cur->next->val)
			return (0);
		cur = cur->next;
	}
	return (1);
}

void	assign_indices(t_stack *a)
{
	t_node	*cur;
	t_node	*inner;
	int		rank;

	cur = a->top;
	while (cur)
	{
		rank = 0;
		inner = a->top;
		while (inner)
		{
			if (inner->val < cur->val)
				rank++;
			inner = inner->next;
		}
		cur->index = rank;
		cur = cur->next;
	}
}
