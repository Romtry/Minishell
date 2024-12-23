/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttouahmi <ttouahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:17:17 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/23 16:29:32 by ttouahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_token *token, unsigned int i, int tlen)
{
    i++;
    while(token->type[i] != 2 && token->type[i] != 10 && i < tlen)
    {
        printf("%s", token->word[i]);
        i++;
    }
    printf("%s\n", token->word[i]);
    //printf("\n");
    parsing(token, i, tlen);
}
