/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:31:35 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 10:31:46 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    char *d;
    const char *s;

    d = dest;
    s = src;
    while (n--)
        *d++ = *s++;
    return dest;
}
