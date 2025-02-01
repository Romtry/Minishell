# include "minishell.h"

void	execute_command(t_cmd *cmd, char **envp, t_env **env)
{
	if (!cmd || !cmd->word[0] || !cmd->word[0][0])
		return ;
	if (handle_redirections(cmd) == -1)
		return ;
	if (is_builtin(cmd->word[0][0]))
	{
		execute_builtin(cmd, env);
		return ;
	}
	if (cmd->word[1])
	{
		execute_piped_commands(cmd, envp);
		return ;
	}
	execute_external(cmd, envp);
}
