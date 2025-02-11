# include "minishell.h"

int cmd_count(t_cmd *cmd)
{
    int count = 0;

    if (!cmd || !cmd->word)
        return 0;
    while (cmd->word[count] != NULL)
        count++;
    return count;
}


void execute_command(t_cmd *cmd)
{
    int saved_stdout = dup(STDOUT_FILENO);
    int saved_stdin = dup(STDIN_FILENO);

    if (!cmd || !cmd->word[0] || !cmd->word[0][0])
    {
        close(saved_stdout);
        close(saved_stdin);
        return;
    }
    if (handle_redirections(cmd) == -1)
    {
        close(saved_stdout);
        close(saved_stdin);
        return;
    }
    if (cmd->has_pipe >= 2)
    {
        for (int i = 0; cmd->word[i]; i++)
        {
            printf("Command[%d]: %s\n", i, cmd->word[i][0] ? cmd->word[i][0] : "(null)");
        }
        execute_piped_commands(cmd);
    }
    else if (is_builtin(cmd->word[0][0]))
    {
        execute_builtin(cmd);
    }
    else
    {
        execute_external(cmd);
    }
    dup2(saved_stdout, STDOUT_FILENO);
    dup2(saved_stdin, STDIN_FILENO);
    close(saved_stdout);
    close(saved_stdin);
}