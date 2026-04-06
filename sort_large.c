#include "push_swap.h"

# define PS_MAX(a, b) ((a) > (b) ? (a) : (b))
# define PS_MIN(a, b) ((a) < (b) ? (a) : (b))

static void	push_chunks_to_b(t_stack *a, t_stack *b)
{
	int	chunk_size;
	int	pushed;
	int	target_max;
	int	remaining;

	chunk_size = 30;
	if (a->size > 100)
		chunk_size = 100;
	pushed = 0;
	while (a->size > 3)
	{
		target_max = pushed + chunk_size;
		remaining = a->size;
		while (remaining-- > 0 && a->size > 3)
		{
			if (a->top->index >= pushed && a->top->index < target_max)
			{
				op_pb(a, b);
				if (b->top->index < pushed + chunk_size * 1 / 2)
					op_rb(b);
			}
			else
				op_ra(a);
		}
		pushed += chunk_size;
	}
}

static int	get_insert_pos(t_stack *a, int val)
{
	t_node	*cur;
	int		pos;
	int		max_pos;
	int		max_val;
	int		tgt_pos;
	int		tgt_val;

	cur = a->top;
	pos = 0;
	max_pos = 0;
	max_val = cur->val;
	tgt_pos = 0;
	tgt_val = INT_MAX;
	while (cur)
	{
		if (cur->val > max_val)
		{
			max_val = cur->val;
			max_pos = pos;
		}
		if (cur->val > val && cur->val < tgt_val)
		{
			tgt_val = cur->val;
			tgt_pos = pos;
		}
		pos++;
		cur = cur->next;
	}
	if (val > max_val)
		return ((max_pos + 1) % a->size);
	return (tgt_pos);
}

static int	get_best_pos(t_stack *a, t_stack *b)
{
	t_node	*bcur;
	int		tgt_a;
	int		ca_f;
	int		ca_b;
	int		cb_f;
	int		cb_b;
	int		cost;
	int		best_cost;
	int		best_pos;
	int		pos_b;

	bcur = b->top;
	pos_b = 0;
	best_pos = 0;
	best_cost = INT_MAX;
	while (bcur)
	{
		tgt_a = get_insert_pos(a, bcur->val);
		ca_f = tgt_a;
		ca_b = (tgt_a == 0) ? 0 : (a->size - tgt_a);
		cb_f = pos_b;
		cb_b = (pos_b == 0) ? 0 : (b->size - pos_b);
		cost = PS_MIN(PS_MIN(PS_MAX(ca_f, cb_f), PS_MAX(ca_b, cb_b)),
				PS_MIN(ca_f + cb_b, ca_b + cb_f));
		if (cost < best_cost)
		{
			best_cost = cost;
			best_pos = pos_b;
		}
		pos_b++;
		bcur = bcur->next;
	}
	return (best_pos);
}

static void	exec_insertion(t_stack *a, t_stack *b, int ca_f, int ca_b,
		int cb_f, int cb_b)
{
	int	best;

	best = PS_MIN(PS_MIN(PS_MAX(ca_f, cb_f), PS_MAX(ca_b, cb_b)),
			PS_MIN(ca_f + cb_b, ca_b + cb_f));
	if (best == PS_MAX(ca_f, cb_f))
	{
		while (ca_f > 0 && cb_f > 0)
		{
			op_rr(a, b);
			ca_f--;
			cb_f--;
		}
		while (ca_f-- > 0)
			op_ra(a);
		while (cb_f-- > 0)
			op_rb(b);
	}
	else if (best == PS_MAX(ca_b, cb_b))
	{
		while (ca_b > 0 && cb_b > 0)
		{
			op_rrr(a, b);
			ca_b--;
			cb_b--;
		}
		while (ca_b-- > 0)
			op_rra(a);
		while (cb_b-- > 0)
			op_rrb(b);
	}
	else if (best == ca_f + cb_b)
	{
		while (ca_f-- > 0)
			op_ra(a);
		while (cb_b-- > 0)
			op_rrb(b);
	}
	else
	{
		while (ca_b-- > 0)
			op_rra(a);
		while (cb_f-- > 0)
			op_rb(b);
	}
	op_pa(a, b);
}

static void	do_insertion(t_stack *a, t_stack *b, int pos_b)
{
	t_node	*cur;
	int		tgt_a;
	int		ca_f;
	int		ca_b;
	int		cb_f;
	int		cb_b;
	int		i;

	cur = b->top;
	i = 0;
	while (i < pos_b && cur)
	{
		cur = cur->next;
		i++;
	}
	tgt_a = get_insert_pos(a, cur->val);
	ca_f = tgt_a;
	ca_b = (tgt_a == 0) ? 0 : (a->size - tgt_a);
	cb_f = pos_b;
	cb_b = (pos_b == 0) ? 0 : (b->size - pos_b);
	exec_insertion(a, b, ca_f, ca_b, cb_f, cb_b);
}

void	sort_large(t_stack *a, t_stack *b)
{
	int	min_pos;
	int	bwd;

	assign_indices(a);
	push_chunks_to_b(a, b);
	sort_3(a);
	while (b->size > 0)
		do_insertion(a, b, get_best_pos(a, b));
	min_pos = stack_min_pos(a);
	bwd = a->size - min_pos;
	if (min_pos <= bwd)
		while (min_pos-- > 0)
			op_ra(a);
	else
		while (bwd-- > 0)
			op_rra(a);
}
