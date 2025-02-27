/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 08:51:08 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/27 08:51:42 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    piped_commands(t_cmd *cmd)
{
    int        count;
    int        input_fd;
    int        pipe_fd[2];
    pid_t    pid;
    int        i;

    count = cmd_count(cmd);
    input_fd = STDIN_FILENO;
    i = 0;
    while (i < count)
    {
        int    need_pipe = (i < count - 1);
        if (!create_pipe(pipe_fd, need_pipe))
            return ;
        pid = fork();
        if (pid == -1)
            return (handle_fork_error());
        else if (pid == 0)
            handle_child(i, cmd, input_fd, pipe_fd);
        else
            handle_parent(&input_fd, pipe_fd, i, count);
        i++;
    }
    wait_for_children();
}
