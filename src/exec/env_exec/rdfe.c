/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdfe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:52:28 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 10:52:37 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remove_duplicates_from_environ(void)
{
    extern char **__environ;
    int i, j, k;

    for (i = 0; __environ[i]; i++)
    {
        for (j = i + 1; __environ[j]; j++)
        {
            if (ft_strcmp(__environ[i], __environ[j]) == 0)
            {
                free(__environ[j]);
                for (k = j; __environ[k]; k++)
                {
                    __environ[k] = __environ[k + 1];
                }
                j--;
            }
        }
    }
}
