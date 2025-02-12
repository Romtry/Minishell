/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:00:47 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 09:01:15 by rothiery         ###   ########.fr       */
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
