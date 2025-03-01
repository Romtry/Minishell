/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:14:15 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/01 11:00:15 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	out_redir_ret(int fd, char **new_args)
{
	perror("minishell: dup2");
	close(fd);
	free_array(new_args);
	return (-1);
}

int	handle_out_redir(t_cmd *cmd, int *i, char **new_args)
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
		free_array(new_args);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (out_redir_ret(fd, new_args));
	close(fd);
	*i += 2;
	return (0);
}

int	handle_heredoc_redir(t_cmd *cmd, int *i, char **new_args)
{
	printf("Detected heredoc for %s\n", cmd->word[0][*i +1]);
	if (handle_heredoc(cmd->word[0][*i +1]) == -1)
		return (free_array(new_args), -1);
	*i += 2;
	return (0);
}

int	handle_in_redir(t_cmd *cmd, int *i, char **new_args)
{
	int	fd;

	fd = open(cmd->word[0][*i +1], O_RDONLY);
	if (fd == -1)
		return (perror("minishell: open"), free_array(new_args), -1);
	printf("Detected input redirection for %s\n", cmd->word[0][*i +1]);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		free_array(new_args);
		return (-1);
	}
	close(fd);
	*i += 2;
	return (0);
}

int	handle_redirections(t_cmd *cmd)
{
	int		i;
	int		j;
	int		in_fd;
	int		out_fd;
	char	**new_args;

	i = 0;
	j = 0;
	in_fd = -1;
	out_fd = -1;
	new_args = malloc(sizeof(char *) * (count_args(cmd->word[0]) + 1));
	while (cmd->word[0][i])
	{
		if (process_redir(cmd, &i, &j, new_args) == -1)
			return (-1);
	}
	new_args[j] = NULL;
	free_array(cmd->word[0]);
	cmd->word[0] = new_args;
	if (in_fd != -1)
		dup2(in_fd, STDIN_FILENO);
	if (out_fd != -1)
		dup2(out_fd, STDOUT_FILENO);
	return (0);
}
