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

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n)
	{
		*str = '\0';
		n--;
		str++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

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
		{
			free_array(new_args);
			return (-1);
		}
	}
	new_args[j] = NULL;
	free_array(cmd->word[0]);
	cmd->word[0] = new_args;
	return (0);
}
