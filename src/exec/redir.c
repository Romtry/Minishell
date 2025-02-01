# include "minishell.h"

int	handle_redirections(t_cmd *cmd)
{
	int     i;
	int     fd;

	i = 0;
	while (cmd->word[i])
	{
		if (cmd->type[i][0] == OUTPUTREDIR) // `>`
		{
			fd = open(cmd->word[i + 1][0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (perror("open"), -1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (cmd->type[i][0] == APPENDREDIR) // `>>`
		{
			fd = open(cmd->word[i + 1][0], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				return (perror("open"), -1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (cmd->type[i][0] == INPUTREDIR) // `<`
		{
			fd = open(cmd->word[i + 1][0], O_RDONLY);
			if (fd == -1)
				return (perror("open"), -1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (cmd->type[i][0] == HEREDOC) // `<<`
		{
			int     pipe_fd[2];
			char*   line;

			if (pipe(pipe_fd) == -1)
				return (perror("pipe"), -1);
			while (1)
			{
					line = readline("> ");
				if (!line || ft_strcmp(line, cmd->word[i + 1][0]) == 0)
					break;
				write(pipe_fd[1], line, ft_strlen(line));
				write(pipe_fd[1], "\n", 1);
				free(line);
			}
			free(line);
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
		}
		i++;
	}
	return (0);
}