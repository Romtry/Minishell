/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:17:00 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/23 09:17:01 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token)
{
	unsigned int	i;

	i = 0;
	while (token->word[i])
	{
		printf("word %u = [%s]\n", i, token->word[i]);
		i++;
	}
}
