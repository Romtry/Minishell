/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:16:31 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/23 13:05:35 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

unsigned int	wich_type(char c)
{
	if (is_sep(c) == 0)
		return (1);
	else if (c == '|')
		return (2);
	else if (c == '<')
		return (3);
	else if (c == '>')
		return (4);
	else if (c == '\'')
		return (5);
	else if (c == '\"')
		return (6);
	else if (c == '$')
		return (7);
	else
		return (0);
}

unsigned int	malloc_word(t_token *token, char *input, unsigned int c)
{
	unsigned int	i;
	unsigned int	save;

	i = 0;
	save = wich_type(input[0]);
	while (input[i] && save == wich_type(input[i]))
		i++;
	token->word[c] = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (input[i] && save == wich_type(input[i]))
	{
		token->word[c][i] = input[i];
		i++;
	}
	token->type[c] = save;
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
	while (str[i] && is_sep(str[i]) == 0)
		i++;
	while (str[i])
	{
		save = wich_type(str[i]);
		while (str[i] && save == wich_type(str[i]))
			i++;
		if ((!str[i]) && is_sep(str[i - 1]) == 0)
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

