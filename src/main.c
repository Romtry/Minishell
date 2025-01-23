/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:17:12 by rothiery          #+#    #+#             */
/*   Updated: 2025/01/23 14:07:42 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(t_token *token, unsigned int n)
{
	if (n == 0)
		printf(RED"Command error tu seras privé de tarte au caca !"CLEAR);
	else if (n == 1)
		printf(RED"Quote not closed so no caca pie !"CLEAR);
	else if (n == 2)
		printf(RED"syntax error near unexpected token '|' !"CLEAR);
	else if (n == 3)
		printf(RED"syntax error near unexpected token 'newline'"CLEAR);
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

void	init_env(t_token *token)
{
	t_env			*env;
	unsigned int	i;

	i = 0;
	token->envhead = ft_lstnew(ENV[0]);
	env = token->envhead;
	while (ENV[i])
	{
		env->next = ft_lstnew(ENV[i]);
		env = env->next;
		i++;
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
	init_env(token);
	while (1)
	{
		if (rl(token) == 1)
			break;
		parsing(token);
		cmd = malloc(sizeof(t_cmd));
		transfert(token, cmd);
		// puts("ICI\n");
		if (token->err == 0)
			print_cmd(cmd);
		free_cmd(cmd);
	}
	free_env(token);
	rl_clear_history();
	return (0);
}
