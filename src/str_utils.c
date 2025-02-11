/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:16:31 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/11 15:48:22 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	wich_type(char c)
{
	if (is_sep(c) == 0)
		return (SEP);
	else if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (INPUTREDIR);
	else if (c == '>')
		return (OUTPUTREDIR);
	else if (c == '\'')
		return (SQUOTE);
	else if (c == '\"')
		return (DQUOTE);
	else if (c == '$')
		return (DOLLAR);
	else
		return (1);
}
