/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:49:55 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/07 08:40:48 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

}

int	handle_fd_dup(int fd, int std_fd)
{
	if (dup2(fd, std_fd) == -1)
	{
		perror("minishell: dup2");
		return (-1);
	}
	return (0);
}

void	read_heredoc_lines(int pipe_fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			write(1, "\n", 1);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd, line, ft_strlen(line));
		write(pipe_fd, "\n", 1);
		free(line);
	}
}


int	process_redir(t_cmd *cmd, int *i, int *j, char **new_args)
{
	if (!ft_strcmp(cmd->word[0][*i], ">>")
		|| !ft_strcmp(cmd->word[0][*i], ">"))
		return (handle_out_redir(cmd, i));
	if (!ft_strcmp(cmd->word[0][*i], "<<"))
		return (handle_heredoc_redir(cmd, i));
	if (!ft_strcmp(cmd->word[0][*i], "<"))
		return (handle_in_redir(cmd, i));
	new_args[(*j)++] = ft_strndup(cmd->word[0][*i],
			ft_strlen(cmd->word[0][*i]));
	(*i)++;
	return (0);
}

void	determine_redirection_params(int append, int *flags,
		const char **redir_type)
{
	if (append)
	{
		*flags |= O_APPEND;
		*redir_type = "append";
	}
	else
	{
		*flags |= O_TRUNC;
		*redir_type = "output";
	}
}
