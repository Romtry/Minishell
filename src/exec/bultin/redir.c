/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:14:15 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/28 09:44:15 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void debug_tokens(char **tokens)
// {
//     int i = 0;
//     printf("Debug: Tokens reçus:\n");
//     while (tokens[i])
//     {
//         printf("Token[%d]: \"%s\"\n", i, tokens[i]);
//         i++;
//     }
// }

static int count_args(char **args)
{
    int count = 0;
    while (args[count])
        count++;
    return count;
}

static int handle_fd_dup(int fd, int std_fd)
{
    if (dup2(fd, std_fd) == -1)
    {
        perror("minishell: dup2");
        return -1;
    }
    return 0;
}

// static int handle_input_redirection(char *file)
// {
//     int fd = open(file, O_RDONLY);
    
//     if (fd == -1)
//         return perror("minishell: open"), -1;
//     if (handle_fd_dup(fd, STDIN_FILENO) == -1)
//         return (close(fd), -1);
//     close(fd);
//     return 0;
// }

// static void set_output_mode(int append, char **mode)
// {
//     if (append)
//         *mode = "append";
//     else
//         *mode = "truncate";
// }

// static int handle_output_redirection(char *file, int append)
// {
//     int flags = O_WRONLY | O_CREAT;
//     int fd;
//     char *mode;

//     set_output_mode(append, &mode);
//     if (append)
//         flags |= O_APPEND;
//     else
//         flags |= O_TRUNC;
//     fd = open(file, flags, 0644);
//     if (fd == -1)
//         return perror("minishell: open"), -1;
//     printf("Opened file %s with fd %d (mode: %s)\n", file, fd, mode);
//     if (handle_fd_dup(fd, STDOUT_FILENO) == -1)
//         return (close(fd), -1);
//     close(fd);
//     return 0;
// }

static void read_heredoc_lines(int pipe_fd, char *delimiter)
{
    char *line;
    
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
        write(pipe_fd, line, ft_strlen(line));
        write(pipe_fd, "\n", 1);
        free(line);
    }
}

int handle_heredoc(char *delimiter)
{
    int pipe_fd[2];
    
    if (pipe(pipe_fd) == -1)
        return perror("minishell: pipe"), -1;
    signal(SIGINT, SIG_DFL);
    read_heredoc_lines(pipe_fd[1], delimiter);
    close(pipe_fd[1]);
    if (handle_fd_dup(pipe_fd[0], STDIN_FILENO) == -1)
        return (close(pipe_fd[0]), -1);
    close(pipe_fd[0]);
    return 0;
}

static int process_redir(t_cmd *cmd, int *i, int *j, char **new_args)
{
    if (!ft_strcmp(cmd->word[0][*i], ">>") || !ft_strcmp(cmd->word[0][*i], ">"))
        return (handle_out_redir(cmd, i, new_args));
    if (!ft_strcmp(cmd->word[0][*i], "<<"))
        return (handle_heredoc_redir(cmd, i, new_args));
    if (!ft_strcmp(cmd->word[0][*i], "<"))
        return (handle_in_redir(cmd, i, new_args));
    new_args[(*j)++] = ft_strndup(cmd->word[0][*i], ft_strlen(cmd->word[0][*i]));
    (*i)++;
    return 0;
}

static void determine_redirection_params(int append, int *flags, const char **redir_type)
{
    if (append)
    {
        *flags |= O_APPEND;
        *redir_type = "append";
    }
    else
    {
        *flags |= O_TRUNC;
        *redir_type = "output";
    }
}

int handle_out_redir(t_cmd *cmd, int *i, char **new_args)
{
    int append = !ft_strcmp(cmd->word[0][*i], ">>");
    char *filename = cmd->word[0][*i + 1];
    int fd;
    int flags = O_WRONLY | O_CREAT;
    const char *redir_type;

    determine_redirection_params(append, &flags, &redir_type);
    fd = open(filename, flags, 0644);
    if (fd == -1)
    {
        perror("minishell: open");
        free_array(new_args);
        return -1;
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("minishell: dup2");
        close(fd);
        free_array(new_args);
        return -1;
    }
    close(fd);
    *i += 2;
    return 0;
}

int handle_heredoc_redir(t_cmd *cmd, int *i, char **new_args)
{
    printf("Detected heredoc for %s\n", cmd->word[0][*i +1]);
    if (handle_heredoc(cmd->word[0][*i +1]) == -1)
        return free_array(new_args), -1;
    *i += 2;
    return 0;
}

int handle_in_redir(t_cmd *cmd, int *i, char **new_args)
{
    int fd;

    fd = open(cmd->word[0][*i +1], O_RDONLY);
    if (fd == -1)
        return perror("minishell: open"), free_array(new_args), -1;
    printf("Detected input redirection for %s\n", cmd->word[0][*i +1]);
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("minishell: dup2");
        close(fd);
        free_array(new_args);
        return -1;
    }
    close(fd);
    *i += 2;
    return 0;
}

static void apply_redirections(int in_fd, int out_fd)
{
    if (in_fd != -1)
        dup2(in_fd, STDIN_FILENO);
    if (out_fd != -1)
        dup2(out_fd, STDOUT_FILENO);
}

int handle_redirections(t_cmd *cmd)
{
    int i = 0;
    int j = 0;
    int in_fd = -1;
    int out_fd = -1;
    char **new_args = malloc(sizeof(char *) * (count_args(cmd->word[0]) + 1));

    // debug_tokens(cmd->word[0]);
    while (cmd->word[0][i])
    {
        if (process_redir(cmd, &i, &j, new_args) == -1)
            return -1;
    }
    new_args[j] = NULL;
    free_array(cmd->word[0]);
    cmd->word[0] = new_args;
    apply_redirections(in_fd, out_fd);
    return 0;
}
