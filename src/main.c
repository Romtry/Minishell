/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:17:12 by rothiery          #+#    #+#             */
/*   Updated: 2025/01/08 12:38:54 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(t_token *token, unsigned int n)
{
	if (n == 0)
		printf(RED"Command error tu seras privé de tarte au caca !\e[0m\n");
	else if (n == 1)
		printf(RED"Quote not closed so no caca pie !\e[0m\n");
	else if (n == 2)
		printf(RED"syntax error near unexpected token '|' no metal pipe for diner !\e[0m\n");
	else if (n == 3)
		printf(RED"syntax error near unexpected token 'newline'\e[0m\n");
	token->err = 1;
}

void	lexer(t_token *token, char *input)
{
	unsigned int	i;
	unsigned int	c;

	i = 0;
	c = 0;
	token->tlen = count_word(input);
	token->err = 0;
	token->word = malloc(sizeof(char *) * (token->tlen + 1));
	token->type = malloc(sizeof(t_type) * (token->tlen + 1));
	while (input[i] && is_sep(input[i]) == 0)
		i++;
	while (c < token->tlen)
	{
		i += malloc_word(token, input + i, c);
		c++;
	}
	token->word[c] = NULL;
	token->type[c] = '\0';
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
	printf("name = %s\n", token->envhead->name);
	env = token->envhead;
	while (ENV[i])
	{
		env->next = ft_lstnew(ENV[i]);
		env = env->next;
		i++;
	}
}

int	main(void)
{
	t_token *token;
	char	*input;

	signal(SIGINT, handle_signal);
	token = malloc(sizeof(t_token));
	init_env(token);
	ft_env_print(token->envhead);
	while (1)
	{
		input = readline(BLUE"(satoru caca)> "RESET);
		if (!input)
			break;
		if (input[0] == '\0')
		{
			free(input);
			continue;
		}
		add_history (input);
		lexer(token, input);
		free(input);
		if (parsing(token) == 0)
			// parsing_exec(&token);
		// print_token(&token);
		free_token(token);
	}
	free_env(token);
	rl_clear_history();
	return (0);
}
