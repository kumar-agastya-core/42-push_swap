#include "push_swap.h"

static void	do_rotate(t_stack *s)
{
	t_node	*first;
	t_node	*last;

	if (!s || s->size < 2)
		return ;
	first = s->top;
	last = s->top;
	while (last->next)
		last = last->next;
	s->top = first->next;
	first->next = NULL;
	last->next = first;
}

void	op_ra(t_stack *a)
{
	do_rotate(a);
	ft_putstr_fd("ra\n", 1);
}

void	op_rb(t_stack *b)
{
	do_rotate(b);
	ft_putstr_fd("rb\n", 1);
}

void	op_rr(t_stack *a, t_stack *b)
{
	do_rotate(a);
	do_rotate(b);
	ft_putstr_fd("rr\n", 1);
}
