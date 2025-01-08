/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:45:35 by rothiery          #+#    #+#             */
/*   Updated: 2025/01/08 12:41:50 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char const *content, unsigned int *i)
{
	char	*temp;

	while (content[*i] && content[*i] != '=')
		*i += 1;
	temp = malloc(sizeof(char) * (*i + 1));
	*i = 0;
	while (content[*i] && content[*i] != '=')
	{
		temp[*i] = content[*i];
		*i += 1;
	}
	temp[*i] = '\0';
	return (temp);
}

t_env	*ft_lstnew(char *content)
{
	t_env			*env;
	unsigned int	i;

	i = 0;
	env = NULL;
	env = malloc(sizeof(t_env));
	if (env)
	{
		env->name = get_name(content, &i);
		if (content + (i + 1))
			env->value = ft_strcpy(content + (i + 1));
		env->next = NULL;
	}
	return (env);
}

void	ft_env_print(t_env *env)
{
	if (!env)
	{
		printf(RED"!env\e[0m\n");
		return ;
	}
	while (env->next)
	{
		printf("%s = %s\n", env->name, env->value);
		env = env->next;
	}
}

void	free_env(t_token *token)
{
	t_env	*temp;

	while (token->envhead)
	{
		temp = token->envhead->next;
		free(token->envhead->name);
		free(token->envhead->value);
		free(token->envhead);
		token->envhead = temp;
	}
	free(token);
}
