/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:18:49 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/24 12:12:35 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd	*cmd)
{
	unsigned int	i;
	unsigned int	i2;

	i = 0;
	i2 = 0;
	while (cmd->word[i])
	{
		while (cmd->word[i][i2])
		{
			free(cmd->word[i][i2]);
			i2++;
		}
		free(cmd->word[i]);
		free(cmd->type[i]);
		i2 = 0;
		i++;
	}
	free(cmd->type);
	free(cmd->word);
	free(cmd->old_environ);
	free(cmd);
}
