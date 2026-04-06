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
