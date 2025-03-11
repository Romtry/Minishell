/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:17:12 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/11 09:16:46 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

unsigned int	rl_lexer(t_token *token)
{
	char	*input;

	input = readline(BLUE"(minishell)> "RESET);
	if (!input)
		return (1);
	if (input[0] == '\0')
	{
		free(input);
		return (2);
	}
	add_history(input);
	lexer(token, input);
	free(input);
	if (!token->word[0])
		return (free_token(token), 2);
	parsing(token);
	return (0);
}

unsigned int	cmd_work(t_token *token, unsigned int *exit_stat, t_env **env)
{
	t_cmd			*cmd;

	if (token->err == 0)
	{
		cmd = malloc(sizeof(t_cmd));
		transfert(token, cmd);
		cmd->env_head_ptr = env;
		cmd->exit = 0;
		cmd->exit_stat = exit_stat;
		cmd->env_change = &token->env_change;
		cmd->old_environ = malloc(sizeof(char **));
		cmd->heredoc_fd = -1;
		if (token->env_change == true)
			*cmd->old_environ = token->old_environ;
		execute_command(cmd, 0, 0, 0);
		if (token->env_change == true)
			token->old_environ = *cmd->old_environ;
		if (cmd->exit == 1)
			token->err = 2;
		free_cmd(cmd);
	}
	else
		free_token(token);
	return (token->err);
}

static t_token	*token_init(unsigned int *exit_stat, t_env ***env)
{
	t_token	*token;

	*env = get_env_head();
	token = malloc(sizeof(t_token));
	token->exit_stat = exit_stat;
	token->env_change = false;
	return (token);
}

int	main(void)
{
	t_env			**env;
	t_token			*token;
	unsigned int	temp;
	unsigned int	exit_stat;

	exit_stat = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	token = token_init(&exit_stat, &env);
	while (1)
	{
		temp = rl_lexer(token);
		if (temp == 1)
			break ;
		else if (temp == 2)
			continue ;
		if (cmd_work(token, &exit_stat, env) == 2)
			break ;
	}
	free_env(*env);
	if (token->env_change == true)
		free_array(token->old_environ);
	free(token);
	rl_clear_history();
	return (exit_stat);
}
