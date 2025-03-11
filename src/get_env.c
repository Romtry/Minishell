/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:10:58 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/11 12:21:07 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_env_array(void)
{
	extern char	**environ;

	return (array_cpy(environ));
}

static t_env	*get_env_list(void)
{
	extern char		**environ;
	t_env			*envhead;
	t_env			*temp;
	unsigned int	i;

	envhead = ft_lstnew(environ[0]);
	if (!envhead)
		return (NULL);
	temp = envhead;
	i = 1;
	while (environ[i])
	{
		temp->next = ft_lstnew(environ[i]);
		if (!temp->next)
			return (NULL);
		temp = temp->next;
		i++;
	}
	temp->next = ft_lstnew(environ[i - 1]);
	return (envhead);
}

void	*get_env(bool b)
{
	if (b == true)
		return (get_env_array());
	return (get_env_list());
}

void	free_end(t_env *env, t_token *token)
{
	if (env)
		free_env(env);
	else
		write(1, "\n", 1);
	if (token->env_change == true)
		free_array(token->old_environ);
}
