/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:36:27 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/06 10:53:43 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	export_verif(char *str)
{
	unsigned int	i;

	i = 0;
	if (str[0] == '_' || ft_is_alpha(str[0]) == true)
	{
		while (str[i])
		{
			if (str[i] == '=')
				return (true);
			else if (ft_is_alnum(str[i]) == false && str[i] != '_')
				return (false);
			i++;
		}
		return (true);
	}
	return (false);
}

void	no_word(void)
{
	t_env	*current;

	current = get_env(false);
	env_print(current);
	free_env(current);
}

void	check(int i, t_cmd *cmd)
{
	if (cmd->word[0][i])
	{
		*cmd->exit_stat = 1;
		write(2, " not a valid identifier\n", 24);
	}
}

char	*value_init(char *cmd, char **name)
{
	char	*equal_sign;
	char	*value;
	char	*temp;

	equal_sign = ft_strchr(cmd, '=');
	if (equal_sign)
	{
		*name = ft_strndup(cmd, equal_sign - cmd);
		value = ft_strndup(equal_sign + 1, ft_strlen(equal_sign) - 1);
	}
	else
	{
		*name = ft_strndup(cmd, ft_strlen(cmd));
		value = ft_strndup("", 0);
	}
	if (value[0] == '"' && value[ft_strlen(value) - 1] == '"')
	{
		temp = ft_strndup(value + 1, ft_strlen(value) - 2);
		free(value);
		value = temp;
	}
	return (value);
}

void	ft_export(t_cmd *cmd)
{
	int		i;
	t_env	**env_head_ptr;
	char	*name;
	char	*value;

	i = 1;
	env_head_ptr = get_env_head();
	if (!env_head_ptr)
		return (perror("get_env_head"));
	if (!cmd->word[0][1])
		return (no_word());
	while (cmd->word[0][i] && export_verif(cmd->word[0][i]) == true)
	{
		value = value_init(cmd->word[0][i], &name);
		if (var_init(env_head_ptr, name, value) == true)
			var_work(env_head_ptr, name, value);
		free(name);
		free(value);
		i++;
	}
	check(i, cmd);
	sync_env_with_system(cmd);
}
