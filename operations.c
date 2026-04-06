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
