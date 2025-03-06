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

static t_env	*process_env_var(char *env_str, t_env *env_head)
{
	char	*name;
	char	*value;
	char	*equal_sign;

	equal_sign = ft_strchr(env_str, '=');
	if (equal_sign)
	{
		name = ft_strndup(env_str, equal_sign - env_str);
		value = ft_strndup(equal_sign + 1, ft_strlen(equal_sign) - 1);
	}
	else
	{
		name = ft_strndup(env_str, ft_strlen(env_str));
		value = ft_strndup("", 0);
	}
	if (!name || !value)
	{
		free(name);
		free(value);
		return (NULL);
	}
	return (existing(name, value, env_head));
}

t_env	**get_env_head(void)
{
	static t_env	*env_head;
	extern char		**__environ;
	int				i;

	if (env_head == NULL)
	{
		i = -1;
		while (__environ[++i])
		{
			env_head = process_env_var(__environ[i], env_head);
			if (!env_head)
				return (NULL);
		}
	}
	return (&env_head);
}
