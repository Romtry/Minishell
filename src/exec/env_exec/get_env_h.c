/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_h.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:35:49 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/01 10:41:49 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*nodup(char *name, char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
	{
		perror("malloc");
		free(name);
		free(value);
		return (NULL);
	}
	new_var->name = name;
	new_var->value = value;
	return (new_var);
}

t_env	*existing(char *name, char *value, t_env *env_head)
{
	t_env	*existing;
	t_env	*new_var;

	existing = env_head;
	while (existing)
	{
		if (ft_strcmp(existing->name, name) == 0)
		{
			free(name);
			free(value);
			break ;
		}
		existing = existing->next;
	}
	if (!existing)
	{
		new_var = nodup(name, value);
		if (new_var == NULL)
			return (NULL);
		new_var->next = env_head;
		return (new_var);
	}
	return (env_head);
}

t_env	**get_env_head(void)
{
	static t_env	*env_head = NULL;
	extern char		**__environ;
	char			*name;
	char			*value;
	int				i;

	i = -1;
	while (__environ[++i])
	{
		value = ft_strchr(__environ[i], '=');
		if (value)
		{
			name = ft_strndup(__environ[i], value - __environ[i]);
			value = ft_strndup(value + 1, ft_strlen(value) - 1);
		}
		else
		{
			name = ft_strndup(__environ[i], ft_strlen(__environ[i]));
			value = ft_strndup("", 0);
		}
		env_head = existing(name, value, env_head);
		if (env_head == NULL)
			return (NULL);
	}
	return (&env_head);
}
