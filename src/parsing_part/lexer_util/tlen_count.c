/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tlen_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:33:07 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:33:59 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	tlen_count(char *str)
{
	unsigned int	save;
	unsigned int	ret;
	unsigned int	i;

	ret = 0;
	i = 0;
	while (str[i] && is_sep(str[i]) == 0)
		i++;
	while (str[i])
	{
		save = wich_type(str[i]);
		while (str[i] && save == wich_type(str[i]))
			i++;
		if ((!str[i]) && is_sep(str[i - 1]) == 0)
			break;
		ret++;
	}
	return (ret);
}
