/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:40:25 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:40:34 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin2(char *str1, char *str2)
{
	char			*ret;
	unsigned int	l;
	unsigned int	i;

	i = -1;
	l = ft_strlen(str1) + ft_strlen(str2);
	ret = malloc(sizeof(char) * l + 1);
	while (str1[++i])
		ret[i] = str1[i];
	i--;
	while (str2[++i - ft_strlen(str1)])
		ret[i] = str2[i - ft_strlen(str1)];
	ret[i] = '\0';
	return (ret);
}
