#include "push_swap.h"

static int	get_max_val(t_stack *a)
{
	t_node	*cur;
	int		max_val;

	cur = a->top;
	max_val = cur->val;
	while (cur->next)
	{
		if (cur->next->val > max_val)
			max_val = cur->next->val;
		cur = cur->next;
	}
	return (max_val);
}

static int	get_insert_pos(t_stack *a, int val)
{
	t_node	*cur;
	int		pos;
	int		tgt_pos;
	int		tgt_val;

	if (val > get_max_val(a))
		return ((stack_max_pos(a) + 1) % a->size);
	cur = a->top;
	pos = 0;
	tgt_pos = 0;
	tgt_val = INT_MAX;
	while (cur)
	{
		if (cur->val > val && cur->val < tgt_val)
		{
			tgt_val = cur->val;
			tgt_pos = pos;
		}
		pos++;
		cur = cur->next;
	}
	return (tgt_pos);
}

void	fill_costs(t_stack *a, t_stack *b, t_costs *c, int pos_b)
{
	t_node	*cur;
	int		i;
	int		tgt_a;

	cur = b->top;
	i = 0;
	while (i < pos_b && cur)
	{
		cur = cur->next;
		i++;
	}
	tgt_a = get_insert_pos(a, cur->val);
	c->ca_f = tgt_a;
	if (tgt_a == 0)
		c->ca_b = 0;
	else
		c->ca_b = a->size - tgt_a;
	c->cb_f = pos_b;
	if (pos_b == 0)
		c->cb_b = 0;
	else
		c->cb_b = b->size - pos_b;
}

int	cost_total(t_costs *c)
{
	int	best;
	int	tmp;

	if (c->ca_f > c->cb_f)
		best = c->ca_f;
	else
		best = c->cb_f;
	if (c->ca_b > c->cb_b)
		tmp = c->ca_b;
	else
		tmp = c->cb_b;
	if (tmp < best)
		best = tmp;
	tmp = c->ca_f + c->cb_b;
	if (tmp < best)
		best = tmp;
	tmp = c->ca_b + c->cb_f;
	if (tmp < best)
		best = tmp;
	return (best);
}

int	get_best_pos(t_stack *a, t_stack *b)
{
	t_costs	c;
	int		cost;
	int		best_cost;
	int		best_pos;
	int		pos_b;

	pos_b = 0;
	best_pos = 0;
	best_cost = INT_MAX;
	while (pos_b < b->size)
	{
		fill_costs(a, b, &c, pos_b);
		cost = cost_total(&c);
		if (cost < best_cost)
		{
			best_cost = cost;
			best_pos = pos_b;
		}
		pos_b++;
	}
	return (best_pos);
}
