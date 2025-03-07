/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:15:54 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/04 10:10:35 by rothiery         ###   ########.fr       */
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

void	execute_command(t_cmd *cmd)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (!cmd || !cmd->word[0] || !cmd->word[0][0])
	{
		close(saved_stdout);
		close(saved_stdin);
		return ;
	}
	if (cmd->has_pipe >= 2)
		execute_piped_commands(cmd);
	else
	{
		if (handle_redirections(cmd) != -1)
			execute_command2(cmd);
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdout);
		close(saved_stdin);
	}
}
