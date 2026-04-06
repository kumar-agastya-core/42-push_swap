#include "push_swap.h"

static void	do_rev_rotate(t_stack *s)
{
	t_node	*last;
	t_node	*second_last;

	if (!s || s->size < 2)
		return ;
	last = s->top;
	second_last = NULL;
	while (last->next)
	{
		second_last = last;
		last = last->next;
	}
	second_last->next = NULL;
	last->next = s->top;
	s->top = last;
}

void	op_rra(t_stack *a)
{
	do_rev_rotate(a);
	ft_putstr_fd("rra\n", 1);
}

void	op_rrb(t_stack *b)
{
	do_rev_rotate(b);
	ft_putstr_fd("rrb\n", 1);
}

void	op_rrr(t_stack *a, t_stack *b)
{
	do_rev_rotate(a);
	do_rev_rotate(b);
	ft_putstr_fd("rrr\n", 1);
}
