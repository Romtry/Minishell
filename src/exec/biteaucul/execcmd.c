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

//enkever cleaned ptet
void cleanup_command(t_cmd *cmd)
{
    int i = 0, j = 0;
    char **cleaned_word = malloc(sizeof(char *) * 256);
    t_type *cleaned_type = malloc(sizeof(t_type) * 256);

    if (!cleaned_word || !cleaned_type)
    {
        perror("minishell: malloc");
        return;
    }
    while (cmd->word[0][i] && cmd->type[0][i] != END)
    {
        if (cmd->type[0][i] != SEP)
        {
            cleaned_word[j] = cmd->word[0][i];
            cleaned_type[j] = cmd->type[0][i];
            j++;
        }
        i++;
    }

    cleaned_word[j] = NULL;
    cleaned_type[j] = END;

    free(cmd->word[0]);
    free(cmd->type[0]);
    cmd->word[0] = cleaned_word;
    cmd->type[0] = cleaned_type;
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
    cleanup_command(cmd);
    if (handle_redirections(cmd) == -1)
    {
        close(saved_stdout);
        close(saved_stdin);
        return;
    }
    if (is_builtin(cmd->word[0][0]))
    {
        execute_builtin(cmd);
    }
    else if (cmd->word[1])
    {
        execute_piped_commands(cmd);
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