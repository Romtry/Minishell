/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:17:12 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/24 15:03:55 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(unsigned int n)
{
	if (n == 0)
		printf(RED"Command error tu seras privé de tarte au caca !\e[0m\n");
	if (n == 1)
		printf(RED"Single quote not closed so no caca pie !\e[0m\n");
}

void	lexer(t_token *token, char *input)
{
	unsigned int	i;
	unsigned int	c;

	i = 0;
	c = 0;
	token->tlen = count_word(input);
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

int	main(void)
{
	t_token token;
	char	*input;

	while (1)
	{
		input = readline(BLUE"(satoru caca)> "RESET);
		// printf("%s\n", input);
		add_history (input);
		lexer(&token, input);
		// get_type(&token);
		puts("avant parsing\n");
		print_token(&token);
		parsing(&token);
		puts("après parsing\n");
		print_token(&token);
		// exec(&token);
		free_token(&token);
	}
	rl_clear_history();
}
