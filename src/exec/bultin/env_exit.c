/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:17:17 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/19 15:15:38 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(t_cmd *cmd)
{
	t_env	*head;
	t_env	*current;

	if (cmd->word[0][1])
		return ((void)printf("env : '%s': No such file or directory\n",
				cmd->word[0][1]));
	head = get_env(false);
	if (head == NULL)
	{
		printf("No environment variables found.\n");
		return ;
	}
	*cmd->exit_stat = 0;
	current = head;
	env_print(current);
	free_env(head);
}

static int	char_int(char *str)
{
	int				ret;
	int				temp;
	int				signe;
	unsigned int	i;

	ret = 0;
	signe = 1;
	i = 0;
	if (str[i] == '-')
		signe = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		temp = str[i] - '0';
		ret = ret * 10;
		ret = ret + temp;
		i++;
	}
	ret = ret * signe;
	return (ret);
}

static bool	verif(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (i == 0)
		return (write(2, " numeric argument required\n", 27), false);
	while (str[i])
	{
		if (str[i] != ' ')
			return (write(2, " numeric argument required\n", 27), false);
		i++;
	}
	return (true);
}

static unsigned int	exit_util(char *str)
{
	unsigned int	i;
	bool			b;

	b = false;
	i = 0;
	while (str[i] == ' ')
		i++;
	str = str + i;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			b = true;
		str = str + 1;
	}
	if (verif(str) == false)
		return (2);
	if (b == true)
		return (256 - (char_int(str) % 256));
	else
		return (char_int(str) % 256);
}

void	exit_shell(t_cmd *cmd)
{
	if (cmd->word[0][1] && cmd->word[0][2])
	{
		*cmd->exit_stat = 1;
		write(2, " too many arguments\n", 20);
	}
	else
	{
		if (cmd->word[0][1])
			*cmd->exit_stat = exit_util(cmd->word[0][1]);
		else
			*cmd->exit_stat = 0;
		printf("exit\n");
		cmd->exit = 1;
	}
}
