/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_es.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:28:15 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:34:33 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	switch_es(t_token *token, unsigned int i)
{
	char	*temp;

	erased_str(token, &i);
	i++;
	temp = ft_strcpy(token->word[i] + 1);
	free(token->word[i]);
	token->word[i] = num_char(token->exit_stat);
	token->word[i] = ft_strjoin(token->word[i], temp);
	free(temp);
}
