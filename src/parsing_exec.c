/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:17:06 by rothiery          #+#    #+#             */
/*   Updated: 2025/01/20 08:33:49 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	is_command(t_token *token, unsigned int *i)
{
	if (ft_strcmp(token->word[*i], "echo"))
		echo(token, i);
	else if (ft_strcmp(token->word[*i], "cd"))
		cd(token, i);
	else if (ft_strcmp(token->word[*i], "pwd"))
		pwd(token, i);
	else if (ft_strcmp(token->word[*i], "export"))
		export(token, i);
	else if (ft_strcmp(token->word[*i], "unset"))
		unset(token, i);
	else if (ft_strcmp(token->word[*i], "env"))
		env(token, i);
	else
		return (1);
	return (0);
}

void	parsing_exec(t_token *token, unsigned int *i)
{
	if(*i == 0)
		token->err = 1;
	else if (is_command(token, i) == 1)
		print_error(token, 2);
}
