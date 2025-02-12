/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:51:11 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:51:26 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_array(t_token *token, t_cmd *cmd)
{
	unsigned int	i;
	unsigned int	i2;
	unsigned int	i3;

	i = 0;
	i2 = 0;
	i3 = 0;
	while (token->word[i3])
	{
		while (token->word[i3] && token->type[i3] != PIPE)
		{
			i3++;
			i2++;
		}
		cmd->word[i] = malloc(sizeof(char *) * (i2 + 1));
		cmd->type[i] = malloc(sizeof(enum e_type) * (i2 + 1));
		i++;
		if (token->word[i3])
			i3++;
		i2 = 0;
	}
}
