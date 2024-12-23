/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttouahmi <ttouahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:17:17 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/23 16:08:54 by ttouahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_token *token, unsigned int i)
{
    while(token->word[i + 1] && token->type[i + 1] != 2 && token->type[i + 1] != 10)
    {
        printf("%s", token->word[i]);
        i++;
    }
    if(token->type[i] != 10)
        printf("%s", token->word[i]);
    parsing(token, i);
}
