/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:54:47 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 10:54:53 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cmd_count(t_cmd *cmd)
{
    int count = 0;

    if (!cmd || !cmd->word)
        return 0;
    while (cmd->word[count] != NULL)
        count++;
    return count;
}
