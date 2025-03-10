/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:26:18 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/10 09:55:22 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_cmd *cmd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		write(2, "minishell: pwd\n", 15);
	else
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	*cmd->exit_stat = 0;
}
