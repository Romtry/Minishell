#include "minishell.h"
static void    setup_io(int input_fd, int pipe_fd[2], int is_not_last);
void    execute_command2(t_cmd *tmp_cmd);
static void    handle_child(int i, t_cmd *cmd, int input_fd, int pipe_fd[2]);
static void    handle_parent(int *input_fd, int pipe_fd[2], int i, int count);
static int    create_pipe(int pipe_fd[2], int need_pipe);
static void    handle_fork_error(void);
static void    wait_for_children(void);
void    piped_commands(t_cmd *cmd);

static void    setup_io(int input_fd, int pipe_fd[2], int is_not_last)
{
    if (input_fd != STDIN_FILENO)
        dup2(input_fd, STDIN_FILENO);
    if (is_not_last)
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
    }
}

void    execute_command2(t_cmd *tmp_cmd)
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
    execve(cmd_path, tmp_cmd->word[0], get_env(0));
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
    count = cmd_count(cmd);
    is_not_last = (i < count - 1);
    setup_io(input_fd, pipe_fd, is_not_last);
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
