/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:45:35 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:36:50 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew(char *content)
{
	t_env			*env;
	unsigned int	i;

	i = 0;
	env = NULL;
	env = malloc(sizeof(t_env));
	if (env)
	{
		env->name = get_name(content, &i);
		if (content[i])
			env->value = ft_strcpy(content + (i + 1));
		env->next = NULL;
	}
	return (env);
}
