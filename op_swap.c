#include "push_swap.h"

static void	do_swap(t_stack *s)
{
	int	tmp;

	if (!s || s->size < 2)
		return ;
	tmp = s->top->val;
	s->top->val = s->top->next->val;
	s->top->next->val = tmp;
	tmp = s->top->index;
	s->top->index = s->top->next->index;
	s->top->next->index = tmp;
}

void	op_sa(t_stack *a)
{
	do_swap(a);
	ft_putstr_fd("sa\n", 1);
}

void	op_sb(t_stack *b)
{
	do_swap(b);
	ft_putstr_fd("sb\n", 1);
}

void	op_ss(t_stack *a, t_stack *b)
{
	do_swap(a);
	do_swap(b);
	ft_putstr_fd("ss\n", 1);
}
