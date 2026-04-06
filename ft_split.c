#include "push_swap.h"

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	count_words(char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i])
			count++;
		while (s[i] && !ft_isspace(s[i]))
			i++;
	}
	return (count);
}

static char	*extract_word(char *s, int *pos)
{
	char	*word;
	int		start;
	int		len;
	int		m;

	while (s[*pos] && ft_isspace(s[*pos]))
		(*pos)++;
	start = *pos;
	while (s[*pos] && !ft_isspace(s[*pos]))
		(*pos)++;
	len = *pos - start;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	m = 0;
	while (m < len)
	{
		word[m] = s[start + m];
		m++;
	}
	word[m] = '\0';
	return (word);
}

static int	fill_result(char **result, char *s, int cnt)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < cnt)
	{
		result[j] = extract_word(s, &i);
		if (!result[j])
		{
			result[j] = NULL;
			free_split(result);
			return (0);
		}
		j++;
	}
	result[j] = NULL;
	return (1);
}

char	**ft_split_spaces(char *s, int *count)
{
	char	**result;
	int		cnt;

	cnt = count_words(s);
	*count = cnt;
	result = malloc((cnt + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (!fill_result(result, s, cnt))
		return (NULL);
	return (result);
}
