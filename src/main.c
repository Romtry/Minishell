/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:17:12 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/24 12:15:57 by rothiery         ###   ########.fr       */
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
	char	**env;

	env = get_env(true);
	print_array(env);
	free_array(env);
	input = readline(BLUE"(satoru caca)> "RESET);
	env = get_env(true);
	print_array(env);
	free_array(env);
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
	parsing(token);
	return (0);
}

void	cmd_work(t_token *token, unsigned int *exit_stat)
{
	t_cmd			*cmd;

	cmd = malloc(sizeof(t_cmd));
	transfert(token, cmd);
	cmd->exit_stat = exit_stat;
	cmd->env_change = &token->env_change;
	cmd->old_environ = malloc(sizeof(char **));
	if (token->env_change == true)
		*cmd->old_environ = token->old_environ;
	execute_command(cmd);
	if (token->env_change == true)
		token->old_environ = *cmd->old_environ;
	free_cmd(cmd);
}

int	main(void)
{
	t_token			*token;
	unsigned int	temp;
	unsigned int	exit_stat;

	exit_stat = 0;
	signal(SIGINT, handle_signal);
	token = malloc(sizeof(t_token));
	token->exit_stat = &exit_stat;
	token->env_change = false;
	while (1)
	{
		temp = rl_lexer(token);
		if (temp == 1)
			break;
		else if (temp == 2)
			continue;
		if (token->err == 0)
			cmd_work(token, &exit_stat);
	}
	if (token->env_change == true)
		free_array(token->old_environ);
	free(token);
	rl_clear_history();
	return (exit_stat);
}
