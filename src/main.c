/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:17:12 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/24 10:09:35 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(unsigned int n)
{
	if (n == 0)
		printf("");
}

int	main(void)
{
	t_token token;
	char	*input;

	while (1)
	{
		input = readline("(satoru caca)> ");
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
