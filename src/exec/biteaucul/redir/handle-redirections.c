#include "minishell.h"

//suprimer les histoires de new normalement pas bez

int handle_redirections(t_cmd *cmd)
{
    int i = 0, j = 0;
    char **new_word = malloc(sizeof(char *) * 256);
    t_type *new_type = malloc(sizeof(t_type) * 256);

    if (!new_word || !new_type)
        return -1;
    while (cmd->type[0][i] != END)
    {
        if (cmd->type[0][i] == INPUTREDIR || cmd->type[0][i] == OUTPUTREDIR ||
            cmd->type[0][i] == APPENDREDIR || cmd->type[0][i] == HEREDOC)
        {
            char *filename = cmd->word[0][i + 1];
            int append = (cmd->type[0][i] == APPENDREDIR);
            if (cmd->type[0][i] == OUTPUTREDIR || cmd->type[0][i] == APPENDREDIR)
            {
                printf("Handling output redirection to file: %s\n", filename);
                if (handle_output_redirection(filename, append) == -1)
                {
                    free(new_word);
                    free(new_type);
                    return -1;
                }
            }
            i += 2;
        }
        else
        {
            new_word[j] = cmd->word[0][i];
            new_type[j] = cmd->type[0][i];
            j++;
            i++;
        }
    }
    new_word[j] = NULL;
    new_type[j] = END;
    free(cmd->word[0]);
    free(cmd->type[0]);
    cmd->word[0] = new_word;
    cmd->type[0] = new_type;
    return 0;
}