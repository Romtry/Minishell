/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:17:17 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/24 10:08:35 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_token *token, unsigned int i)
{
    i++;
    while(token->type[i] != 2 && token->type[i] != 10 && i < token->tlen)
    {
        printf("%s", token->word[i]);
        i++;
    }
    printf("%s\n", token->word[i]);
    //printf("\n");
    parsing(token, i);
}
