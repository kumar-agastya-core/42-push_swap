#include "push_swap.h"

static void	push_one_chunk(t_stack *a, t_stack *b, int pushed, int chunk_size)
{
	int	remaining;
	int	target_max;

	target_max = pushed + chunk_size;
	remaining = a->size;
	while (remaining > 0 && a->size > 3)
	{
		if (a->top->index >= pushed && a->top->index < target_max)
		{
			op_pb(a, b);
			if (b->top->index < pushed + chunk_size / 2)
				op_rb(b);
		}
		else
			op_ra(a);
		remaining--;
	}
}

static void	push_chunks_to_b(t_stack *a, t_stack *b)
{
	int	chunk_size;
	int	pushed;

	chunk_size = 30;
	if (a->size > 100)
		chunk_size = 100;
	pushed = 0;
	while (a->size > 3)
	{
		push_one_chunk(a, b, pushed, chunk_size);
		pushed += chunk_size;
	}
}

static void	do_insertion(t_stack *a, t_stack *b, int pos_b)
{
	t_costs	c;

	fill_costs(a, b, &c, pos_b);
	exec_insertion(a, b, &c);
}

static void	rotate_to_min(t_stack *a)
{
	int	min_pos;
	int	bwd;

	min_pos = stack_min_pos(a);
	bwd = a->size - min_pos;
	if (min_pos <= bwd)
	{
		while (min_pos > 0)
		{
			op_ra(a);
			min_pos--;
		}
	}
	else
	{
		while (bwd > 0)
		{
			op_rra(a);
			bwd--;
		}
	}
}

void	sort_large(t_stack *a, t_stack *b)
{
	assign_indices(a);
	push_chunks_to_b(a, b);
	sort_3(a);
	while (b->size > 0)
		do_insertion(a, b, get_best_pos(a, b));
	rotate_to_min(a);
}
