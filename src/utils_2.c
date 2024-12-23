/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:20:13 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/23 15:07:39 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_token(t_token *token)
{
	unsigned int	i;

	i = 0;
	while (token->word[i])
	{
		free(token->word[i]);
		i++;
	}
	free(token->word);
	free(token->type);
}

int exitmentioned(t_token *token)
{
	unsigned int	i;

	i = 0;
	while (token->word[i])
	{
		if (!ft_strcmp("exit",token->word[i]))
		{
			puts("exited\n");
			return (1);
		}
		i++;
	}
	return (0);
}
