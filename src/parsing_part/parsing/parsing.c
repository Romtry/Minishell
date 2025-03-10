/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:16:16 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/10 09:44:38 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parsing2(t_token *token)
{
	unsigned int	i;

	i = 0;
	while (token->err != 1 && token->word[i])
	{
		if (token->type[i] == PIPE)
			pipe_pars(token, i);
		else if (token->type[i] == HEREDOC)
			pars_heredoc(token, i);
		else if (token->type[i] == DOLLAR && token->type[i + 1] == WORD)
			dollar_pars(token, &i);
		else if (token->type[i] == DOLLAR && !token->type[i + 1])
			token->type[i] = WORD;
		else if (token->type[i] == DQUOTED && token->word[i][0] == '$')
			dollar_quote(token, i);
		if (token->err == 1)
			return ;
		i++;
	}
	redir_pars(token);
}

unsigned int	parsing(t_token *token)
{
	unsigned int	i;

	i = -1;
	while (token->word[++i])
	{
		if (token->type[i] == SQUOTE || token->type[i] == DQUOTE)
			secnd_quote(token, &i, token->type[i]);
		if (token->err == 1)
			return (1);
	}
	i--;
	if (token->word[i] && token->type[i] == SEP)
		erased_str(token, &i);
	parsing2(token);
	if (token->err == 1)
		return (1);
	sep_clean(token);
	return (0);
}
