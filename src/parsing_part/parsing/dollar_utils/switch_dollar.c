/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:16:04 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:48:48 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	switch_dollar(t_token *token, unsigned int one, unsigned int *two)
{
	t_env	*env;

	env = token->envhead;
	while (env->next)
	{
		if (ft_strcmp(token->word[one], env->name) == 0)
		{
			free(token->word[one]);
			token->word[one] = ft_strcpy(env->value);
			return ;
		}
		env = env->next;
	}
	erased_str(token, &one);
	*two -= 1;
}
