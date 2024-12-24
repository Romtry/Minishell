/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:17:06 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/24 11:02:14 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_pars(t_token *token, unsigned int *i)
{
	if (!token->type[*i + 1] || token->type[*i + 1] != 1)
		print_error(0);
}

void	parsing2(t_token *token, unsigned int i)
{
	// int y;

	// y = 0;
	if(i == 0)
		if(exitmentioned(token))
			return ;
	while(token->word[i])
	{
		if(token->type[i] == WORD)
		{
			if(!ft_strcmp("echo", token->word[i]))
			{
				puts("echoed\n");
				echo_pars(token, &i);
				break;
			}
		}
		i++;
	}
}
