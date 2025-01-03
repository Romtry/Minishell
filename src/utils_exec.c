/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:05:43 by ttouahmi          #+#    #+#             */
/*   Updated: 2024/12/26 14:22:04 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_token *token, unsigned int *i)
{
	printf("echoed\n");
	(void)token;
	(void)i;
}

void	cd(t_token *token, unsigned int *i)
{
	printf("cded\n");
	(void)token;
	(void)i;
}

void	pwd(t_token *token, unsigned int *i)
{
	printf("pwded\n");
	(void)token;
	(void)i;
}

void	export(t_token *token, unsigned int *i)
{
	printf("exported\n");
	(void)token;
	(void)i;
}

void	unset(t_token *token, unsigned int *i)
{
	printf("unseted\n");
	(void)token;
	(void)i;
}
