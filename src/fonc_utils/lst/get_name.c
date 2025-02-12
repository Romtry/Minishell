/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:36:35 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:36:54 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char const *content, unsigned int *i)
{
	char	*temp;

	while (content[*i] && content[*i] != '=')
		*i += 1;
	temp = malloc(sizeof(char) * (*i + 1));
	*i = 0;
	while (content[*i] && content[*i] != '=')
	{
		temp[*i] = content[*i];
		*i += 1;
	}
	temp[*i] = '\0';
	return (temp);
}
