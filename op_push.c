#include "push_swap.h"

static void	do_push(t_stack *src, t_stack *dst)
{
	t_node	*node;

	if (!src || src->size == 0)
		return ;
	node = src->top;
	src->top = node->next;
	src->size--;
	node->next = dst->top;
	dst->top = node;
	dst->size++;
}

void	op_pa(t_stack *a, t_stack *b)
{
	do_push(b, a);
	ft_putstr_fd("pa\n", 1);
}

void	op_pb(t_stack *a, t_stack *b)
{
	do_push(a, b);
	ft_putstr_fd("pb\n", 1);
}
