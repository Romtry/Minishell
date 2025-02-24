/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:15:22 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/24 11:27:30 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	*token->exit_stat = 2;
	token->err = 1;
	free_token(token);
}
