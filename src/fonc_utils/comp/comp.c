/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 08:59:16 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/07 17:01:44 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	ft_strcmp(char *str, char *str2)
{
	unsigned int	i;

	i = 0;
	if (str && str2)
	{
		while (str[i] && str2[i] && str[i] == str2[i])
			i++;
		if (!str[i] && !str2[i])
			return (0);
	}
	return (1);
}

unsigned int	ft_strncmp(char *str, char *str2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (str && str2)
	{
		while (str[i] && str2[i] && str[i] == str2[i] && i < n)
			i++;
		if (i == n)
			return (0);
	}
	return (1);
}
