/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:47:34 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 14:00:10 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	ft_strncmp(char *str, char *str2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (str[i] && str2[i] && str[i] == str2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return (1);
}
