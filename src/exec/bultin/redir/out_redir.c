/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:11:44 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/19 15:44:47 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	out_redir_ret(int fd)
{
	perror("minishell: dup2");
	close(fd);
	return (-1);
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
		*cmd->exit_stat = 1;
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (out_redir_ret(fd));
	close(fd);
	*i += 2;
	return (0);
}
