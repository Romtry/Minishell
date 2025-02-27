/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:19:21 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/27 14:54:38 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    execute_command2(t_cmd *tmp_cmd)
{
    char    *cmd_name;
    char    *cmd_path;

    cmd_name = tmp_cmd->word[0][0];
    if (is_builtin(cmd_name))
    {
        execute_builtin(tmp_cmd);
        exit(EXIT_SUCCESS);
    }
    cmd_path = get_command_path(cmd_name);
    if (!cmd_path)
    {
        fprintf(stderr, "minishell: %s: command not found\n", cmd_name);
        exit(127);
    }
    execve(cmd_path, tmp_cmd->word[0], get_env(true));
    perror("minishell: execve");
    free(cmd_path);
    exit(EXIT_FAILURE);
}


static void handle_child(int i, t_cmd *cmd, int input_fd, int pipe_fd[2])
{
    t_cmd    tmp_cmd;
    int      count;
    int      is_not_last;

    tmp_cmd.word = &cmd->word[i];
    tmp_cmd.type = &cmd->type[i];
    tmp_cmd.env_change = cmd->env_change;
    tmp_cmd.old_environ = cmd->old_environ;
    count = cmd_count(cmd);
    is_not_last = (i < count - 1);
    if (input_fd != STDIN_FILENO)
        dup2(input_fd, STDIN_FILENO);
    if (is_not_last)
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
    }
    if (handle_redirections(&tmp_cmd) == -1)
        exit(EXIT_FAILURE);
    execute_command2(&tmp_cmd);
}


static void    handle_parent(int *input_fd, int pipe_fd[2], int i, int count)
{
    if (*input_fd != STDIN_FILENO)
        close(*input_fd);
    if (i < count - 1)
    {
        close(pipe_fd[1]);
        *input_fd = pipe_fd[0];
    }
    else
        *input_fd = STDIN_FILENO;
}

static int    create_pipe(int pipe_fd[2], int need_pipe)
{
    if (need_pipe && pipe(pipe_fd) == -1)
    {
        perror("minishell: pipe");
        return (0);
    }
    return (1);
}

void    execute_piped_commands(t_cmd *cmd)
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
            return ((void)perror("minishell: fork"));
        else if (pid == 0)
            handle_child(i, cmd, input_fd, pipe_fd);
        else
            handle_parent(&input_fd, pipe_fd, i, count);
        i++;
    }
    while (wait(NULL) > 0)
        continue ;
}
