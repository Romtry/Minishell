/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:15:54 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/19 16:09:44 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command2(t_cmd *cmd)
{
	if (cmd->word[0][0] == NULL)
		return ;
	else if (is_builtin(cmd->word[0][0]))
		execute_builtin(cmd);
	else
		execute_external(cmd);
}

int	execute_heredoc(t_cmd *cmd, int *k, int i, int j)
{
	char	**new_args;
	int		count;

	count = count_args(cmd->word[*k]);
	new_args = ft_calloc(count + 1, sizeof(char *));
	if (!new_args)
		return (-1);
	while (i < count)
	{
		if (ft_strcmp(cmd->word[*k][i], "<<") == 0)
		{
			if (handle_heredoc_redir(cmd, &i, *k) == -1)
				return (free_array(new_args), -1);
		}
		else
		{
			new_args[j] = ft_strndup(cmd->word[*k][i],
					ft_strlen(cmd->word[*k][i]));
			if (!new_args[j])
				return (free_array(new_args), -1);
			j++;
			i++;
		}
	}
	return (end_func(cmd, new_args, j, *k));
}

void	help_norming(bool b, int saved_stdout, int saved_stdin)
{
	if (b == true)
	{
		close(saved_stdout);
		close(saved_stdin);
	}
	else
	{
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdout);
		close(saved_stdin);
	}
}

static void	init_heredoc_fds(t_cmd *cmd, int num_commands)
{
	int	i;

	i = 0;
	while (i < num_commands)
		cmd->heredoc_fds[i++] = -1;
}

static void	process_heredocs(t_cmd *cmd, int *k)
{
	while (cmd->word[*k])
	{
		if (execute_heredoc(cmd, k, 0, 0) == -1)
		{
			*cmd->exit_stat = 130;
			cmd->exit = 2;
			break ;
		}
		(*k)++;
	}
}

void	execute_command(t_cmd *cmd, int saved_stdout, int saved_stdin, int k)
{
	int	num_commands;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (!cmd || !cmd->word[0] || !cmd->word[0][0])
		return (help_norming(true, saved_stdout, saved_stdin));
	num_commands = cmd_count(cmd);
	cmd->heredoc_fds = malloc(num_commands * sizeof(int));
	if (!cmd->heredoc_fds)
		return (help_norming(true, saved_stdout, saved_stdin));
	init_heredoc_fds(cmd, num_commands);
	process_heredocs(cmd, &k);
	if (cmd->exit)
		return (free(cmd->heredoc_fds), help_norming(true, saved_stdout, saved_stdin));
	if (cmd->has_pipe >= 2)
		execute_piped_commands(cmd);
	else
	{
		if (handle_redirections(cmd) != -1)
			execute_command2(cmd);
		help_norming(false, saved_stdout, saved_stdin);
	}
	free(cmd->heredoc_fds);
}
