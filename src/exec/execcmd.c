# include "minishell.h"

void	execute_command(t_cmd *cmd)
{
	if (!cmd || !cmd->word[0] || !cmd->word[0][0])
		return ;
	if (handle_redirections(cmd) == -1)
		return ;
	if (is_builtin(cmd->word[0][0]))
	{
		execute_builtin(cmd);
		return ;
	}
	if (cmd->word[1])
	{
		execute_piped_commands(cmd);
		return ;
	}
	execute_external(cmd);
}
