/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:37:44 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/14 08:03:39 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void env_builtin(void)
{
	t_env	*head;

	head = get_env(false);
	if (head == NULL)
	{
		printf("No environment variables found.\n");
		return;
	}
	env_print(head);
	free_env(head);
}
