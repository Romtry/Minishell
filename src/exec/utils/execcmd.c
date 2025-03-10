/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttouahmi <ttouahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:15:54 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/10 21:17:26 by ttouahmi         ###   ########.fr       */
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

int	execute_heredoc(t_cmd *cmd, int *k)
{
	int		i;
	int		j;
	char	**new_args;
	int		count;

	i = 0;
	j = 0;
	count = count_args(cmd->word[*k]);
	new_args = ft_calloc(count + 1, sizeof(char *));
	if (!new_args)
		return (-1);
	while (i < count)
	{
		if (ft_strcmp(cmd->word[*k][i], "<<") == 0)
		{
			if (handle_heredoc_redir(cmd, &i, *k) == -1)
			{
				free_array(new_args);
				return (-1);
			}
		}
		else
		{
			new_args[j] = ft_strndup(cmd->word[*k][i],ft_strlen(cmd->word[*k][i]));
			if (!new_args[j])
			{
				free_array(new_args);
				return (-1);
			}
			j++;
			i++;
		}
	}
	new_args[j] = NULL;
	free_array(cmd->word[*k]);
	cmd->word[*k] = new_args;
	return (0);
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
	
	int k = 0;
	int count = cmd_count(cmd);
	while (cmd->word[k])
	{
		execute_heredoc(cmd, &k);
		k++;
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
