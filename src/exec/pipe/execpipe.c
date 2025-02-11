#include "minishell.h"

static char **clean_arguments(char **args)
{
    int i;
    int j;
    char **cleaned_args;
    int count;

    i = 0;
    count = 0;
    while (args[i])
    {
        if (args[i][0] != '\0') // Éviter les arguments vides
            count++;
        i++;
    }
    cleaned_args = malloc(sizeof(char *) * (count + 1));
    if (!cleaned_args)
        return (NULL);
    i = 0;
    j = 0;
    while (args[i])
    {
        if (args[i][0] != '\0')
            cleaned_args[j++] = args[i];
        i++;
    }
    cleaned_args[j] = NULL;
    return (cleaned_args);
}

int arg_count(char **args)
{
    int count;

    count = 0;
    while (args[count])
        count++;
    return (count);
}

void execute_piped_commands(t_cmd *cmd)
{
    int count;
    int input_fd;
    int pipe_fd[2];
    pid_t pid;
    int i;

    count = cmd_count(cmd);
    input_fd = STDIN_FILENO;
    i = 0;
    while (i < count)
    {
        if (i < count - 1 && pipe(pipe_fd) == -1)
        {
            perror("minishell: pipe");
            return;
        }

        pid = fork();
        if (pid == -1)
        {
            perror("minishell: fork");
            return;
        }

        if (pid == 0) // Child process
        {
            t_cmd tmp_cmd;
            tmp_cmd.word = &cmd->word[i];
            tmp_cmd.type = &cmd->type[i];

            if (handle_redirections(&tmp_cmd) == -1)
                exit(EXIT_FAILURE);

            if (input_fd != STDIN_FILENO)
                dup2(input_fd, STDIN_FILENO);
            if (i < count - 1)
            {
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
            }

            if (is_builtin(tmp_cmd.word[0][0]))
            {
                execute_builtin(&tmp_cmd);
                exit(0);
            }
            else
            {
                char *cmd_path = get_command_path(tmp_cmd.word[0][0]);
                if (!cmd_path)
                {
                    fprintf(stderr, "minishell: %s: command not found\n", tmp_cmd.word[0][0]);
                    exit(127);
                }
                execve(cmd_path, tmp_cmd.word[0], get_env(0));
                perror("minishell: execve");
                free(cmd_path);
                exit(EXIT_FAILURE);
            }
        }
        else // Parent
        {
            if (input_fd != STDIN_FILENO)
                close(input_fd);
            if (i < count - 1)
            {
                close(pipe_fd[1]);
                input_fd = pipe_fd[0];
            }
        }
        i++;
    }
    while (wait(NULL) > 0); // Wait for all children
}