/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:38:09 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 13:57:57 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	char_int(char *str)
{
	int				ret;
	int				temp;
	int				signe;
	unsigned int	i;

	ret = 0;
	signe = 1;
	i = 0;
	if (str[0] == '-')
		signe = -1;
	while (str[i])
	{
		temp = str[i] - '0';
		ret = ret * 10;
		ret = ret + temp;
		i++;
	}
	ret = ret * signe;
	return (ret);
}

static unsigned int	exit_util(char *str, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (2);
		i++;
	}
	if (n == 0)
		return(256 - (char_int(str) % 256));
	else
		return(char_int(str) % 256);
}

void	exit_shell(t_cmd *cmd)
{
	if (cmd->word[0][2])
	{
		if (cmd->word[0][1][0] == '-')
			*cmd->exit_stat = exit_util(cmd->word[0][2], 0);
	}
		else
			*cmd->exit_stat = exit_util(cmd->word[0][1], 1);
	printf("exit\n");
	exit(*cmd->exit_stat);
}
