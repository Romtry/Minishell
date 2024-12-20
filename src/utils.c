#include "minishell.h"

unsigned int	ft_strlen(char *str)
{
	unsigned int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

unsigned int	is_sep(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (0);
	return (1);
}

unsigned int	malloc_word(t_token *token, char *input, unsigned int c)
{
	unsigned int	i;
	unsigned int	save;

	i = 0;
	save = is_sep(input[0]);
	while (input[i] && save == is_sep(input[i]))
		i++;
	token->word[c] = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (input[i] && save == is_sep(input[i]))
	{
		token->word[c][i] = input[i];
		i++;
	}
	token->word[c][i] = '\0';
	return (i);
}

unsigned int	count_word(char *str)
{
	unsigned int	save;
	unsigned int	ret;
	unsigned int	i;

	ret = 0;
	i = 0;
	save = 0;
	while (str[i] && is_sep(str[i]) == 0)
		i++;
	while (str[i])
	{
		while (str[i] && is_sep(str[i]) == 1)
			i++;
		ret++;
		if (!str[i])
			break;
		while (str[i] && is_sep(str[i]) == 0)
			i++;
		if (!str[i])
			break;
		ret++;
	}
	return (ret);
}

unsigned int	ft_strcmp(char *str, char *str2)
{
	unsigned int	i;
	unsigned int	n;

	n = ft_strlen(str2);
	i = 0;
	while (str[i] && str[i] == str2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return (1);
}

