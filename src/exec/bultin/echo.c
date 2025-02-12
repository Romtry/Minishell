/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:06:58 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 15:19:41 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  is_n_option(char *arg)
{
	int     i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void    echo(t_cmd *cmd)
{
    int     i;
    int     n_line;

    i = 1;
    n_line = 1;
    if (cmd->word[0][1] && is_n_option(cmd->word[0][i]))
    {
        n_line = 0;
        i++;
    }
    while (cmd->word[0][i])
    {
        printf("%s", cmd->word[0][i]);
        i++;
        if (cmd->word[0][i])
            printf(" ");
    }
    if (n_line)
        printf("\n");
}
