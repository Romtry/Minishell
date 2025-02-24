#include "minishell.h"

void debug_tokens(char **tokens)
{
    int i = 0;
    printf("Debug: Tokens reçus:\n");
    while (tokens[i])
    {
        printf("Token[%d]: \"%s\"\n", i, tokens[i]);
        i++;
    }
}
int count_args(char **args)
{
    int count = 0;
    while (args[count] != NULL)
    {
        count++;
    }
    return count;
}

int handle_input_redirection(char *file)
{
    int fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("minishell: open");
        return -1;
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("minishell: dup2");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

int handle_output_redirection(char *file, int append)
{
    int flags;
    int fd;

    flags = O_WRONLY | O_CREAT;
    if (append)
        flags |= O_APPEND;
    else
        flags |= O_TRUNC;

    fd = open(file, flags, 0644);
    if (fd == -1)
    {
        perror("minishell: open");
        return (-1);
    }

    printf("Opened file %s with fd %d (mode: %s)\n", file, fd,
           append ? "append" : "truncate");

    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("minishell: dup2");
        close(fd);
        return (-1);
    }

    close(fd);
    return (0);
}

int handle_heredoc(char *delimiter)
{
    int pipe_fd[2];
    char *line;

    if (pipe(pipe_fd) == -1)
    {
        perror("minishell: pipe");
        return -1;
    }
    signal(SIGINT, SIG_DFL);
    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            write(1, "\n", 1);
            break;
        }
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        write(pipe_fd[1], line, ft_strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
    close(pipe_fd[1]);
    if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
    {
        perror("minishell: dup2");
        close(pipe_fd[0]);
        return -1;
    }
    close(pipe_fd[0]);
    return 0;
}

int handle_redirections(t_cmd *cmd)
{
    int i = 0, j = 0;
    int in_fd = -1, out_fd = -1;
    char **new_args = malloc(sizeof(char *) * (count_args(cmd->word[0]) + 1));

    // debug_tokens(cmd->word[0]);
    while (cmd->word[0][i])
    {
        if (ft_strcmp(cmd->word[0][i], ">>") == 0)
        {
            if (out_fd != -1) close(out_fd);
            out_fd = open(cmd->word[0][i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (out_fd == -1)
            {
                perror("minishell: open");
                free_array(new_args);
                return -1;
            }
            // printf("Detected append redirection (>>) for %s\n", cmd->word[0][i + 1]);
            i += 2;
        }
        else if (ft_strcmp(cmd->word[0][i], ">") == 0)
        {
            if (out_fd != -1) close(out_fd);
            out_fd = open(cmd->word[0][i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (out_fd == -1)
            {
                perror("minishell: open");
                free_array(new_args);
                return -1;
            }
            // printf("Detected output redirection (>) for %s\n", cmd->word[0][i + 1]);
            i += 2;
        }
        else if (ft_strcmp(cmd->word[0][i], "<<") == 0)
        {
            // printf("Detected heredoc (<<) for delimiter %s\n", cmd->word[0][i + 1]);
            if (handle_heredoc(cmd->word[0][i + 1]) == -1)
            {
                free_array(new_args);
                return -1;
            }
            i += 2;
        }
        else if (ft_strcmp(cmd->word[0][i], "<") == 0)
        {
            if (in_fd != -1) close(in_fd);
            in_fd = open(cmd->word[0][i + 1], O_RDONLY);
            if (in_fd == -1)
            {
                perror("minishell: open");
                free_array(new_args);
                return -1;
            }
            // printf("Detected input redirection (<) for %s\n", cmd->word[0][i + 1]);
            i += 2;
        }
        else
        {
            new_args[j++] = ft_strdup(cmd->word[0][i]);
            i++;
        }
    }
    new_args[j] = NULL;
    free_array(cmd->word[0]);
    cmd->word[0] = new_args;

    if (in_fd != -1) dup2(in_fd, STDIN_FILENO);
    if (out_fd != -1) dup2(out_fd, STDOUT_FILENO);

    if (in_fd != -1) close(in_fd);
    if (out_fd != -1) close(out_fd);

    return 0;
}
