/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfert_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:51:44 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 13:11:00 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	transfert_pipe(t_cmd *cmd, unsigned int *p, unsigned int *i2)
{
	cmd->word[*p][*i2] = NULL;
	cmd->type[*p][*i2] = '\0';
	*p += 1;
	*i2 = 0;
}
