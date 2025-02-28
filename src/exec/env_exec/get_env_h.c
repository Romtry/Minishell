/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_h.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:35:49 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/28 14:23:30 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_var(t_env *env_head)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
	{
		perror("malloc");
		free(env_head->name);
		free(env_head->value);
		return (NULL);
	}
	new_var->name = env_head->name;
	new_var->value = env_head->value;
	new_var->next = env_head;
}

bool	geh(t_env *env_head)
{
	int		duplicate_found;
	t_env	*existing;

	duplicate_found = 0;
	existing = env_head;
	while (existing)
	{
		if (ft_strcmp(existing->name, env_head->name) == 0)
		{
			free(env_head->name);
			free(env_head->value);
			duplicate_found = 1;
			return (false);
		}
		existing = existing->next;
	}
	if (duplicate_found == 0)
	{
		env_head = new_var();
		if (env_head == NULL)
			return (false);
	}
	return (true);
}

t_env	**get_env_head(void)
{
	static t_env	*env_head;
	extern char		**__environ;
	char			*equal;
	int				i;

	env_head = NULL;
	i = -1;
	while (__environ[++i])
	{
		equal = ft_strchr(__environ[i], '=');
		if (equal)
		{
			env_head->name = ft_strndup(__environ[i], equal - __environ[i]);
			env_head->value = ft_strndup(equal + 1, ft_strlen(equal) - 1);
		}
		else
		{
			env_head->name = ft_strndup(__environ[i], ft_strlen(__environ[i]));
			env_head->value = ft_strndup("", 0);
		}
		if (geh(env_head) == false)
			return (NULL);
	}
	return (&env_head);
}

void	remove_duplicates_from_env_head(void)
{
	t_env	*current;
	t_env	*prev;
	t_env	*temp;

	current = *get_env_head();
	prev = NULL;
	while (current)
	{
		temp = *get_env_head();
		while (temp != current)
		{
			if (ft_strcmp(temp->name, current->name) == 0)
			{
				if (prev)
					prev->next = current->next;
				else
					*get_env_head() = current->next;
				free(current->name);
				free(current->value);
				free(current);
				current = prev ? prev->next : *get_env_head();
				break ;
			}
			temp = temp->next;
		}
		if (temp == current)
		{
			prev = current;
			current = current->next;
		}
	}
}
