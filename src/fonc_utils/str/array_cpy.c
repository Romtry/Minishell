/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_cpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:40:50 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:40:57 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**array_cpy(char **arr)
{
	unsigned int	i;
	unsigned int	i2;
	char			**ret;

	i = 0;
	i2 = 0;
	while (arr[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (arr[++i])
	{
		while (arr[i][i2])
			i2++;
		ret[i] = malloc(sizeof(char) * (i2 + 1));
		i2 = -1;
		while (arr[i][++i2])
			ret[i][i2] = arr[i][i2];
		ret[i][i2] = '\0';
		i2 = 0;
	}
	ret[i] = NULL;
	return (ret);
}
