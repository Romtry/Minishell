/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:14:15 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/11 14:05:05 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_redir(t_cmd *cmd, int *i, int *j, char **new_args)
{
	if (!ft_strcmp(cmd->word[0][*i], ">>")
		|| !ft_strcmp(cmd->word[0][*i], ">"))
		return (handle_out_redir(cmd, i));
	if (!ft_strcmp(cmd->word[0][*i], "<"))
		return (handle_in_redir(cmd, i));
	new_args[(*j)++] = ft_strndup(cmd->word[0][*i],
			ft_strlen(cmd->word[0][*i]));
	(*i)++;
	return (0);
}

void	dup2err(t_cmd *cmd, char **new_args)
{
	perror("minishell: dup2");
	close(cmd->heredoc_fd);
	free_array(new_args);
}

int	end_func(t_cmd *cmd, char **new_args, int j, int k)
{
	new_args[j] = NULL;
	free_array(cmd->word[k]);
	cmd->word[k] = new_args;
	return (0);
}

int	handle_redirections(t_cmd *cmd)
{
	int		i;
	int		j;
	char	**new_args;
	int		count;

	i = 0;
	j = 0;
	count = count_args(cmd->word[0]);
	new_args = ft_calloc(count + 1, sizeof(char *));
	if (!new_args)
		return (-1);
	while (cmd->word[0][i])
	{
		if (process_redir(cmd, &i, &j, new_args) == -1)
			return (free_array(new_args), -1);
	}
	// if (cmd->heredoc_fd != -1)
	// {
	// 	if (dup2(cmd->heredoc_fd, STDIN_FILENO) == -1)
	// 		return (dup2err(cmd, new_args), -1);
	// 	close(cmd->heredoc_fd);
	// 	cmd->heredoc_fd = -1;
	// }
	return (end_func(cmd, new_args, j, 0));
}
