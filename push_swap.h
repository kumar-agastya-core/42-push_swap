#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_node
{
	int				val;
	int				index;
	struct s_node	*next;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
	int		size;
}	t_stack;

typedef struct s_costs
{
	int	ca_f;
	int	ca_b;
	int	cb_f;
	int	cb_b;
}	t_costs;

/* ft_utils.c */
void	ft_putstr_fd(char *s, int fd);
int		ft_isdigit(char c);
int		ft_isspace(char c);
int		ft_atoi_safe(const char *s, long *result);

/* ft_split.c */
char	**ft_split_spaces(char *s, int *count);
void	free_split(char **arr);

/* stack_init.c */
t_stack	*stack_new(void);
void	stack_free(t_stack *s);
void	stack_push_bottom(t_stack *s, int val);

/* stack_utils.c */
int		stack_min_pos(t_stack *s);
int		stack_max_pos(t_stack *s);
int		is_sorted(t_stack *s);
void	assign_indices(t_stack *a);

/* parse.c */
t_stack	*parse_args(int argc, char **argv);

/* op_swap.c */
void	op_sa(t_stack *a);
void	op_sb(t_stack *b);
void	op_ss(t_stack *a, t_stack *b);

/* op_push.c */
void	op_pa(t_stack *a, t_stack *b);
void	op_pb(t_stack *a, t_stack *b);

/* op_rotate.c */
void	op_ra(t_stack *a);
void	op_rb(t_stack *b);
void	op_rr(t_stack *a, t_stack *b);

/* op_rev_rotate.c */
void	op_rra(t_stack *a);
void	op_rrb(t_stack *b);
void	op_rrr(t_stack *a, t_stack *b);

/* sort.c */
void	sort(t_stack *a, t_stack *b);
void	sort_3(t_stack *a);

/* sort_insert.c */
void	fill_costs(t_stack *a, t_stack *b, t_costs *c, int pos_b);
int		cost_total(t_costs *c);
int		get_best_pos(t_stack *a, t_stack *b);

/* sort_exec.c */
void	exec_insertion(t_stack *a, t_stack *b, t_costs *c);

/* sort_large.c */
void	sort_large(t_stack *a, t_stack *b);

#endif
