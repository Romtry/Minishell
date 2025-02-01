/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:16:31 by rothiery          #+#    #+#             */
/*   Updated: 2025/01/24 14:07:30 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	ft_strlen(char *str)
{
	unsigned int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
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
		return (SEP);
	else if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (INPUTREDIR);
	else if (c == '>')
		return (OUTPUTREDIR);
	else if (c == '\'')
		return (SQUOTE);
	else if (c == '\"')
		return (DQUOTE);
	else if (c == '$')
		return (DOLLAR);
	else
		return (1);
}

unsigned int	ft_strncmp(char *str, char *str2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (str[i] && str2[i] && str[i] == str2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return (1);
}

unsigned int	ft_strcmp(char *str, char *str2)
{
	unsigned int	i;

	i = 0;
	while (str[i] && str2[i] && str[i] == str2[i])
		i++;
	if (!str[i] && !str2[i])
		return (0);
	return (1);
}
