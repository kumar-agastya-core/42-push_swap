#include "push_swap.h"

static void	exec_fwd(t_stack *a, t_stack *b, t_costs *c)
{
	int	ca_f;
	int	cb_f;

	ca_f = c->ca_f;
	cb_f = c->cb_f;
	while (ca_f > 0 && cb_f > 0)
	{
		op_rr(a, b);
		ca_f--;
		cb_f--;
	}
	while (ca_f > 0)
	{
		op_ra(a);
		ca_f--;
	}
	while (cb_f > 0)
	{
		op_rb(b);
		cb_f--;
	}
}

static void	exec_bwd(t_stack *a, t_stack *b, t_costs *c)
{
	int	ca_b;
	int	cb_b;

	ca_b = c->ca_b;
	cb_b = c->cb_b;
	while (ca_b > 0 && cb_b > 0)
	{
		op_rrr(a, b);
		ca_b--;
		cb_b--;
	}
	while (ca_b > 0)
	{
		op_rra(a);
		ca_b--;
	}
	while (cb_b > 0)
	{
		op_rrb(b);
		cb_b--;
	}
}

static void	exec_afwd_bbwd(t_stack *a, t_stack *b, t_costs *c)
{
	int	ca_f;
	int	cb_b;

	ca_f = c->ca_f;
	cb_b = c->cb_b;
	while (ca_f > 0)
	{
		op_ra(a);
		ca_f--;
	}
	while (cb_b > 0)
	{
		op_rrb(b);
		cb_b--;
	}
}

static void	exec_abwd_bfwd(t_stack *a, t_stack *b, t_costs *c)
{
	int	ca_b;
	int	cb_f;

	ca_b = c->ca_b;
	cb_f = c->cb_f;
	while (ca_b > 0)
	{
		op_rra(a);
		ca_b--;
	}
	while (cb_f > 0)
	{
		op_rb(b);
		cb_f--;
	}
}

void	exec_insertion(t_stack *a, t_stack *b, t_costs *c)
{
	int	best;
	int	fwd_fwd;
	int	bwd_bwd;

	best = cost_total(c);
	if (c->ca_f > c->cb_f)
		fwd_fwd = c->ca_f;
	else
		fwd_fwd = c->cb_f;
	if (c->ca_b > c->cb_b)
		bwd_bwd = c->ca_b;
	else
		bwd_bwd = c->cb_b;
	if (best == fwd_fwd)
		exec_fwd(a, b, c);
	else if (best == bwd_bwd)
		exec_bwd(a, b, c);
	else if (best == c->ca_f + c->cb_b)
		exec_afwd_bbwd(a, b, c);
	else
		exec_abwd_bfwd(a, b, c);
	op_pa(a, b);
}
