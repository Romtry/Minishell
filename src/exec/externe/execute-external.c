#include "minishell.h"

void execute_external(t_cmd *cmd)
{
    char **envp;
    pid_t pid;
    char *cmd_path;
    char **cleaned_args;
    int i;

    if (!cmd || !cmd->word[0] || !cmd->word[0][0])
    {
        printf("minishell: command not found\n");
        return;
    }
    cmd_path = get_command_path(cmd->word[0][0]);
    if (!cmd_path)
    {
        printf("minishell: command not found: %s\n", cmd->word[0][0]);
        return;
    }
    envp = get_env(0);
    cleaned_args = clean_arguments(cmd->word[0]);
    pid = fork();
    if (pid == 0)
    {
        if (execve(cmd_path, cleaned_args, envp) == -1)
        {
            perror("execve");
            free(cmd_path);
            free_array(envp);
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
        perror("fork");
    else
        waitpid(pid, NULL, 0);
    free(cmd_path);
    free_array(envp);
    free(cleaned_args);
}
