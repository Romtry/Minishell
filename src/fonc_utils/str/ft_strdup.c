/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:33:58 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 10:34:30 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strdup(const char *s)
{
    char *dup;
    size_t len;

    len = ft_strlen(s);
    dup = (char *)malloc(len + 1);
    if (!dup)
        return NULL;
    ft_memcpy(dup, s, len + 1);
    return dup;
}
