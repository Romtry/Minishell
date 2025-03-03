/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:16:30 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 11:16:36 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->word[0][0], "echo") == 0)
		echo(cmd);
	else if (ft_strcmp(cmd->word[0][0], "cd") == 0)
		cd(cmd);
	else if (ft_strcmp(cmd->word[0][0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(cmd->word[0][0], "export") == 0)
		ft_export(cmd);
	else if (ft_strcmp(cmd->word[0][0], "unset") == 0)
		unset(cmd);
	else if (ft_strcmp(cmd->word[0][0], "env") == 0)
		env_builtin();
	else if (ft_strcmp(cmd->word[0][0], "exit") == 0)
		exit_shell(cmd);
}
