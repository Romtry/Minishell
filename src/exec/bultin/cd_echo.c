/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:09:58 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/06 15:51:22 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s) + 1;
	dup = malloc(len);
	if (dup)
		ft_memcpy(dup, s, len);
	return (dup);
}

static char	*cd2(void)
{
	t_env	*home_env;
	char	*home;

	home_env = get_env(false);
	while (home_env && ft_strcmp(home_env->name, "HOME") != 0)
		home_env = home_env->next;
	if (home_env)
		home = ft_strdup(home_env->value);
	free_env(get_env(false));
	return (home);
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
		cmd->exit = true;
		write(2, "minishell: cd: HOME not set\n", 28);
		return (NULL);
	}
	if (path[1] == '\0' || path[1] == '/')
		expanded_path = ft_strjoin(home, path + 1, false);
	else
		expanded_path = ft_strdup(path);
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
		cmd->exit = true;
		return (false);
	}
	*should_free = true;
	return (true);
}

static void	handle_too_many_args(t_cmd *cmd)
{
	*cmd->exit_stat = 1;
	cmd->exit = true;
	write(2, "cd : too many arguments\n", 24);
}

static void	handle_single_arg(t_cmd *cmd, char **path, bool *should_free)
{
	*path = cmd->word[0][1];
	*path = handle_tilde(*path, cmd, should_free);
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
		handle_single_arg(cmd, &path, &should_free_path);
		if (!path)
			return ;
	}
	if (chdir(path) != 0 && !cmd->exit)
	{
		*cmd->exit_stat = 1;
		write(2, "minishell: cd: No such file or directory\n", 41);
	}
	if (should_free_path)
		free(path);
}

static int	is_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo(t_cmd *cmd)
{
	int	i;
	int	n_line;

	i = 1;
	n_line = 1;
	if (cmd->word[0][1] && is_n_option(cmd->word[0][i]))
	{
		n_line = 0;
		i++;
	}
	while (cmd->word[0][i])
	{
		write(STDOUT_FILENO, cmd->word[0][i], ft_strlen(cmd->word[0][i]));
		i++;
		if (cmd->word[0][i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (n_line)
		write(STDOUT_FILENO, "\n", 1);
}
