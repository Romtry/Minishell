/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:17:06 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/24 10:34:55 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_token *token, unsigned int i)
{
	// int y;

	// y = 0;
	if(i == 0)
		if(exitmentioned(token))
			return ;
	while(token->word[i])
	{
		if(token->type[i] == 0)
		{
			if(!ft_strcmp("echo", token->word[i]))
			{
				puts("echoed\n");
				echo_pars();
				// echo(token, i);
				break;
			}
		}
		i++;
	}
}
