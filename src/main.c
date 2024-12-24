/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:17:12 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/24 10:19:54 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(unsigned int n)
{
	if (n == 0)
		printf("");
}

void	lexer(t_token *token, char *input)
{
	unsigned int	i;
	unsigned int	c;

	i = 0;
	c = 0;
	token->word = malloc(sizeof(char *) * (count_word(input) + 1));
	token->type = malloc(sizeof(t_type) * (count_word(input) + 1));
	while (input[i] && is_sep(input[i]) == 0)
		i++;
	while (c < count_word(input))
	{
		i += malloc_word(token, input + i, c);
		c++;
	}
	token->word[c] = NULL;
	token->type[c] = '\0';
	print_token(token);
}

int	main(void)
{
	t_token token;
	char	*input;

	while (1)
	{
		input = readline(BLUE"(satoru caca)> \e[0m");
		// printf("%s\n", input);
		add_history (input);
		lexer(&token, input);
		// get_type(&token);
		parsing(&token, 0);
		// exec(&token);
		free_token(&token);
	}
	rl_clear_history();
}
