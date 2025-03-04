/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:33:14 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/04 10:14:44 by rothiery         ###   ########.fr       */
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
		exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (out_redir_ret(fd));
	close(fd);
	*i += 2;
	return (0);
}

int	handle_heredoc_redir(t_cmd *cmd, int *i)
{
	if (handle_heredoc(cmd->word[0][*i +1]) == -1)
		exit(1);
	*i += 2;
	return (0);
}

int	handle_in_redir(t_cmd *cmd, int *i)
{
	int	fd;

	fd = open(cmd->word[0][*i +1], O_RDONLY);
	if (fd == -1)
	{
		perror("minishell: open");
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		exit(1);
	}
	close(fd);
	*i += 2;
	return (0);
}
