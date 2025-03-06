/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:33:14 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/06 10:54:16 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	out_redir_ret(int fd)
{
	perror("minishell: dup2");
	close(fd);
	return (-1);
}

int	handle_out_redir(t_cmd *cmd, int *i)
{
	int			append;
	char		*filename;
	int			fd;
	int			flags;
	const char	*redir_type;

	flags = O_WRONLY | O_CREAT;
	filename = cmd->word[0][*i + 1];
	append = !ft_strcmp(cmd->word[0][*i], ">>");
	determine_redirection_params(append, &flags, &redir_type);
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		perror("minishell: open");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (out_redir_ret(fd));
	close(fd);
	*i += 2;
	return (0);
}


int	handle_heredoc_redir(t_cmd *cmd, int *i)
{
	if (handle_heredoc(cmd, cmd->word[0][*i + 1]) == -1)
		return (-1);
	if (cmd->heredoc_interrupted)
	{
		cmd->heredoc_interrupted = 0;
		*i = 0;
		return (-1);
	}
	*i += 2;
	return (0);
}

int	handle_in_redir(t_cmd *cmd, int *i)
{
	int	fd;

	fd = open(cmd->word[0][*i + 1], O_RDONLY);
	if (fd == -1)
	{
		perror("minishell: open");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	*i += 2;
	return (0);
}

void	read_heredoc_lines(t_cmd *cmd, int pipe_fd, char *delimiter)
{
	char	*line;

	while (!cmd->heredoc_interrupted)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			cmd->heredoc_interrupted = 1;
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
