/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:25:53 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 10:25:59 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cd(t_cmd *cmd)
{
    char *path;
    t_env *home_env;
    int i = 1;

    while (cmd->word[0][i] && ft_strcmp(cmd->word[0][i], " ") == 0)
        i++;
    if (!cmd->word[0][i])
    {
        home_env = get_env(1);
        while (home_env && ft_strcmp(home_env->name, "HOME") != 0)
            home_env = home_env->next;
        if (!home_env)
        {
            printf("minishell: cd: HOME not set\n");
            return;
        }
        path = home_env->value;
    }
	else if (cmd->word[0][2])
	{
		*cmd->exit_stat = 1;
		write(2, "cd : too many arguments\n", 24);
		exit(1);
	}
	else
        path = cmd->word[0][i];
    if (chdir(path) != 0)
        perror("minishell: cd");
}
