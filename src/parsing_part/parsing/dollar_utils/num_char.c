/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:34:19 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:34:36 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*num_char(unsigned int n)
{
	unsigned int	i;
	unsigned int	n2;
	char			*ret;

	i = 0;
	n2 = n;
	while (n > 10)
	{
		i++;
		n = n/10;
	}
	i++;
	ret = malloc(sizeof(char) * (i + 1));
	ret[i] = '\0';
	i--;
	while (n2 > 10)
	{
		ret[i] = (n2 % 10) + '0';
		n2 = n2/10;
		i--;
	}
	ret[0] = n2 + '0';
	return (ret);
}
