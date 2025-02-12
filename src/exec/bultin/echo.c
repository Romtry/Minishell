/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:06:58 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 10:07:19 by rothiery         ###   ########.fr       */
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
    while (cmd->word[0][i] && ft_strcmp(cmd->word[0][i], " ") == 0)
        i++;
    if (cmd->word[0][i] && is_n_option(cmd->word[0][i]))
    {
        n_line = 0;
        i++;
    }
    while (cmd->word[0][i])
    {
        if (ft_strcmp(cmd->word[0][i], " ") != 0)
        {
            printf("%s", cmd->word[0][i]);
            if (cmd->word[0][i + 1] && ft_strcmp(cmd->word[0][i + 1], " ") == 0)
                printf(" ");
        }
        i++;
    }
    if (n_line)
        printf("\n");
}
