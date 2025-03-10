/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:09:58 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/10 10:00:29 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cd2(void)
{
	t_env	*home_env;
	t_env	*head;
	char	*home;

	home = NULL;
	head = get_env(false);
	home_env = head;
	while (home_env && ft_strcmp(home_env->name, "HOME") != 0)
		home_env = home_env->next;
	if (home_env)
		home = ft_strndup(home_env->value, ft_strlen(home_env->value));
	return (free_env(head), home);
}

static char	*handle_tilde(char *path, t_cmd *cmd, bool *should_free)
{
	char	*home;
	char	*expanded_path;

	if (path[0] != '~')
	{
		*should_free = false;
		return (path);
	}
	home = cd2();
	if (!home)
	{
		*cmd->exit_stat = 1;
		write(2, "minishell: cd: HOME not set\n", 28);
		return (NULL);
	}
	if (path[1] == '\0' || path[1] == '/')
		expanded_path = ft_strjoin(home, path + 1, false);
	else
		expanded_path = ft_strndup(path, ft_strlen(path));
	free(home);
	*should_free = true;
	return (expanded_path);
}

static bool	handle_no_args(t_cmd *cmd, char **path, bool *should_free)
{
	*path = cd2();
	if (*path == NULL)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		*cmd->exit_stat = 1;
		return (false);
	}
	*should_free = true;
	return (true);
}

static void	handle_too_many_args(t_cmd *cmd)
{
	*cmd->exit_stat = 1;
	write(2, "cd : too many arguments\n", 24);
}

static bool	handle_single_arg(t_cmd *cmd, char **path, bool *should_free)
{
	*path = cmd->word[0][1];
	*path = handle_tilde(*path, cmd, should_free);
	if (!*path)
		return (false);
	return (true);
}

void	cd(t_cmd *cmd)
{
	char	*path;
	bool	should_free_path;

	should_free_path = false;
	if (!cmd->word[0][1])
	{
		if (!handle_no_args(cmd, &path, &should_free_path))
			return ;
	}
	else if (cmd->word[0][2])
		return (handle_too_many_args(cmd));
	else
	{
		if (handle_single_arg(cmd, &path, &should_free_path) == false)
			return ;
	}
	if (chdir(path) != 0 && cmd->exit == 0)
	{
		*cmd->exit_stat = 1;
		write(2, "minishell: cd: No such file or directory\n", 41);
	}
	else
		*cmd->exit_stat = 0;
	if (should_free_path)
		free(path);
}
