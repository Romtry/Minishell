/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:33:14 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/19 15:41:18 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_in_redir(t_cmd *cmd, int *i)
{
	int	fd;

	fd = open(cmd->word[0][*i + 1], O_RDONLY);
	if (fd == -1)
	{
		perror("minishell: open");
		*cmd->exit_stat = 1;
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
