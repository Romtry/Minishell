include "minishell.c"

void	execute_piped_commands(t_cmd *cmd, char **envp)
{
	int			i;
	int			pipe_fd[2];
	int			prev_fd;
	pid_t	pid;

	i = 0;
	prev_fd = -1;
	while (cmd->word[i])
	{
		if (cmd->word[i + 1] && pipe(pipe_fd) < 0)
		{
			perror("pipe");
			return ;
		}
		pid = fork();
		if (pid == 0)
		{
			if (handle_redirections(cmd) == -1)
				exit(1);

			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (cmd->word[i + 1])
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
				close(pipe_fd[0]);
			}
			if (execve(cmd->word[i][0], cmd->word[i], envp) == -1)
			{
				perror("execve");
				exit(1);
			}
		}
		else if (pid < 0)
		{
			perror("fork");
			return ;
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->word[i + 1])
			close(pipe_fd[1]);
		prev_fd = pipe_fd[0];
		i++;
	}
	while (wait(NULL) > 0)
		;
}