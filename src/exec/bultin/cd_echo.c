/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:09:58 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/01 10:45:09 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cd2(void)
{
	t_env	*home_env;

	home_env = get_env(false);
	while (home_env && ft_strcmp(home_env->name, "HOME") != 0)
		home_env = home_env->next;
	if (!home_env)
		return (NULL);
	return (home_env->value);
}

void	cd(t_cmd *cmd)
{
	char	*path;
	int		i;

	i = 1;
	if (!cmd->word[0][i])
	{
		path = cd2();
		if (path == NULL)
			return ((void)printf("minishell: cd: HOME not set\n"));
	}
	else if (cmd->word[0][2])
	{
		*cmd->exit_stat = 1;
		write(2, "cd : too many arguments\n", 24);
		exit(1);
	}
	else
		path = cmd->word[0][i];
	if (chdir(path) != 0)
	{
		*cmd->exit_stat = 1;
		write(2, "minishell: cd: No such file or directory\n", 41);
	}
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
