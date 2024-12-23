/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:20:13 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/24 13:55:34 by rothiery         ###   ########.fr       */
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

char	*ft_strjoin(char *str1, char *str2)
{
	char			*ret;
	unsigned int	l;
	unsigned int	i;

	i = -1;
	l = ft_strlen(str1) + ft_strlen(str2);
	ret = malloc(sizeof(char) * l + 1);
	while (str1[++i])
		ret[i] = str1[i];
	i--;
	while (str2[++i - ft_strlen(str1)])
		ret[i] = str2[i - ft_strlen(str1)];
	free(str1);
	ret[i] = '\0';
	return (ret);
}

char	*ft_strcpy(char *str)
{
	unsigned int	i;
	char			*ret;

	i = -1;
	ret = malloc(ft_strlen(str) + 1);
	while (str[++i])
		ret[i] = str[i];
	ret[i] = '\0';
	return (ret);
}
