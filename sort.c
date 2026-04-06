#include "push_swap.h"

static void	rotate_min_to_top(t_stack *a)
{
	int	min_pos;
	int	bwd;

	min_pos = stack_min_pos(a);
	bwd = a->size - min_pos;
	if (min_pos <= bwd)
		while (min_pos-- > 0)
			op_ra(a);
	else
		while (bwd-- > 0)
			op_rra(a);
}

void	sort_3(t_stack *a)
{
	int	top;
	int	mid;
	int	bot;

	top = a->top->val;
	mid = a->top->next->val;
	bot = a->top->next->next->val;
	if (top > mid && top < bot)
		op_sa(a);
	else if (top > mid && top > bot && mid > bot)
	{
		op_ra(a);
		op_sa(a);
	}
	else if (top > mid && top > bot && mid < bot)
		op_ra(a);
	else if (top < mid && top < bot && mid > bot)
	{
		op_rra(a);
		op_sa(a);
	}
	else if (top < mid && top > bot)
		op_rra(a);
}

static void	sort_4(t_stack *a, t_stack *b)
{
	rotate_min_to_top(a);
	op_pb(a, b);
	sort_3(a);
	op_pa(a, b);
}

static void	sort_5(t_stack *a, t_stack *b)
{
	rotate_min_to_top(a);
	op_pb(a, b);
	rotate_min_to_top(a);
	op_pb(a, b);
	sort_3(a);
	op_pa(a, b);
	op_pa(a, b);
}

void	sort(t_stack *a, t_stack *b)
{
	if (is_sorted(a))
		return ;
	if (a->size == 2)
		op_sa(a);
	else if (a->size == 3)
		sort_3(a);
	else if (a->size == 4)
		sort_4(a, b);
	else if (a->size == 5)
		sort_5(a, b);
	else
		sort_large(a, b);
}
