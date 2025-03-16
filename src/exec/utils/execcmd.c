/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:15:54 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/16 16:26:33 by rothiery         ###   ########.fr       */
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

void	execute_command(t_cmd *cmd, int saved_stdout, int saved_stdin, int k)
{
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (!cmd || !cmd->word[0] || !cmd->word[0][0])
		return (help_norming(true, saved_stdout, saved_stdin));
	while (cmd->word[k])
	{
		if (execute_heredoc(cmd, &k, 0, 0) == -1)
		{
			*cmd->exit_stat = 130;
			cmd->exit = 2;
			break ;
		}
		k++;
	}
	if (cmd->exit)
		return (help_norming(true, saved_stdout, saved_stdin));
	if (cmd->has_pipe >= 2)
		execute_piped_commands(cmd);
	else
	{
		if (handle_redirections(cmd) != -1)
			execute_command2(cmd);
		help_norming(false, saved_stdout, saved_stdin);
	}
}
