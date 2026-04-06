#include "push_swap.h"

t_stack	*stack_new(void)
{
	t_stack	*s;

	s = malloc(sizeof(t_stack));
	if (!s)
		return (NULL);
	s->top = NULL;
	s->size = 0;
	return (s);
}

void	stack_free(t_stack *s)
{
	t_node	*cur;
	t_node	*next;

	if (!s)
		return ;
	cur = s->top;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	free(s);
}

void	stack_push_bottom(t_stack *s, int val)
{
	t_node	*node;
	t_node	*cur;

	node = malloc(sizeof(t_node));
	if (!node)
		return ;
	node->val = val;
	node->index = 0;
	node->next = NULL;
	if (!s->top)
	{
		s->top = node;
		s->size++;
		return ;
	}
	cur = s->top;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
	s->size++;
}

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
