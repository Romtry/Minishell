/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:33:14 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 10:33:21 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strndup(const char *s, size_t n)
{
    char *dup;
    size_t len;

    len = 0;
    while (s[len] && len < n)
        len++;
    dup = (char *)malloc(len + 1);
    if (!dup)
        return NULL;
    ft_memcpy(dup, s, len);
    dup[len] = '\0';
    return dup;
}
