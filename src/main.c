/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:17:12 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/11 15:32:35 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	exit_stat = 0;

void	print_error(t_token *token, unsigned int n)
{
	if (n == 0)
		perror(RED"Command error tu seras privé de tarte au caca !"CLEAR);
	else if (n == 1)
		perror(RED"Quote not closed so no caca pie !"CLEAR);
	else if (n == 2)
		perror(RED"syntax error near unexpected token '|' !"CLEAR);
	else if (n == 3)
		perror(RED"syntax error near unexpected token 'newline'"CLEAR);
	else if (n == 4)
		perror(RED"syntax error near unexpected token '<'"CLEAR);
	else if (n == 5)
		perror(RED"syntax error near unexpected token '>'"CLEAR);
	exit_stat = 2;
	token->err = 1;
	free_token(token);
}

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

unsigned int	rl(t_token *token)
{
	char	*input;

	input = readline(BLUE"(satoru caca)> "RESET);
	if (!input)
		return (1);
	if (input[0] == '\0')
	{
		free(input);
		return (1);
	}
	add_history (input);
	lexer(token, input);
	free(input);
	return (0);
}

int	main(void)
{
	t_token	*token;
	t_cmd	*cmd;

	signal(SIGINT, handle_signal);
	token = malloc(sizeof(t_token));
	while (1)
	{
		if (rl(token) == 1)
			break;
		token->exit_stat = exit_stat;
		parsing(token);
		if (token->err == 0)
		{
			cmd = malloc(sizeof(t_cmd));
			transfert(token, cmd);
			cmd->exit_stat = &exit_stat;
			execute_command(cmd);
			// print_cmd(cmd);
			free_cmd(cmd);
		}
	}
	free(token);
	rl_clear_history();
	return (exit_stat);
}
