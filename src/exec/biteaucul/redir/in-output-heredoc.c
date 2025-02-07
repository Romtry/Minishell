#include "minishell.h"

// > marche, >> ?, < ?, << ?

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

int handle_heredoc(char *delimiter)
{
    int pipe_fd[2];
    char *line;

    if (pipe(pipe_fd) == -1)
    {
        perror("minishell: pipe");
        return -1;
    }
    while (1)
    {
        line = readline("> ");
        if (!line || strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        write(pipe_fd[1], line, strlen(line));
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