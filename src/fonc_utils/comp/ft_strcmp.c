/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:48:08 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/11 15:48:25 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	ft_strcmp(char *str, char *str2)
{
	unsigned int	i;

	i = 0;
	while (str[i] && str2[i] && str[i] == str2[i])
		i++;
	if (!str[i] && !str2[i])
		return (0);
	return (1);
}
