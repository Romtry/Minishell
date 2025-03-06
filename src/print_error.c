/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:15:22 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/06 14:58:11 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(t_token *token, unsigned int n)
{
	if (n == 0)
		write(2, RED"Command error !"CLEAR, 31);
	else if (n == 1)
		write(2, RED"Quote not closed !"CLEAR, 34);
	else if (n == 2)
		write(2, RED"syntax error near unexpected token '|' !"CLEAR, 56);
	else if (n == 3)
		write(2, RED"syntax error near unexpected token 'newline'"CLEAR, 60);
	else if (n == 4)
		write(2, RED"syntax error near unexpected token '<'"CLEAR, 54);
	else if (n == 5)
		write(2, RED"syntax error near unexpected token '>'"CLEAR, 54);
	*token->exit_stat = 2;
	token->err = 1;
	free_token(token);
}
