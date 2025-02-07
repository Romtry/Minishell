# include "minishell.h"

void	execute_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->word[0][0], "echo") == 0)
		echo(cmd);
	else if (ft_strcmp(cmd->word[0][0], "cd") == 0)
		cd(cmd);
	else if (ft_strcmp(cmd->word[0][0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(cmd->word[0][0], "export") == 0)
		ft_export(cmd);
	else if (ft_strcmp(cmd->word[0][0], "unset") == 0)
		unset(cmd);
	else if (ft_strcmp(cmd->word[0][0], "env") == 0)
		env_builtin();
	else if (ft_strcmp(cmd->word[0][0], "exit") == 0)
		exit_shell();
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}
