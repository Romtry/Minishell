/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:55:42 by rothiery          #+#    #+#             */
/*   Updated: 2025/01/24 14:39:03 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_pars(t_token *token, unsigned int i)
{
	if (i == 0 || i == token->tlen - 1)
		return (free_token(token), print_error(token, 2));
	else if (ft_strlen(token->word[i]) != 1)
		return (free_token(token), print_error(token, 2));
	else if (token->type[i - 1] == WORD || token->type[i - 1] == DOLLAR
		|| token->type[i - 1] == SEP)
	{
		if ((token->type[i + 1] == WORD || token->type[i + 1] == DOLLAR
			|| token->type[i + 1] == SQUOTE || token->type[i + 1] == DQUOTE)
			|| (token->type[i + 1] == SEP && (token->type[i + 1] == WORD
			|| token->type[i + 1] == DOLLAR || token->type[i + 1] == SQUOTE
			|| token->type[i + 1] == DQUOTE)))
			return ;
	}
	print_error(token, 2);
}

void	redir(t_token *token)
{
	unsigned int	i;

	i = 0;
	while (token->word[i])
	{
		if (token->type[i] == OUTPUTREDIR || token->type[i] == APPENDREDIR
			|| token->type[i] == INPUTREDIR || token->type[i] == HEREDOC)
		{
			if (i + 1 >= token->tlen)
				return (free_token(token), print_error(token, 3));
			if (token->type[i + 1] != WORD && (i + 3 < token->tlen
					|| token->type[i + 1] != SEP || token->type[i + 2] != WORD))
				return (free_token(token), print_error(token, 3));
		}
		i++;
	}
}

void	dollar_pars(t_token *token, unsigned int *i)
{
	if (*i > 0 && *i + 1 >= token->tlen && token->type[*i - 1] == WORD)
	{
		token->word[*i - 1] = ft_strjoin(token->word[*i - 1], "$");
		erased_str(token, i);
	}
	else if (*i + 1 >= token->tlen && (*i == 0 || token->type[*i - 1] != WORD))
		token->type[*i] = WORD;
	else
		pars_dollar(token, *i);
	*i -= 1;
}

void	parsing2(t_token *token)
{
	unsigned int	i;

	i = 0;
	while (token->word[i])
	{
		if (token->type[i] == PIPE)
			pipe_pars(token, i);
		else if (token->type[i] == DOLLAR || (token->type[i] == DQUOTED
				&& token->word[i][0] == '$'))
			dollar_pars(token, &i);
		if (token->err == 1)
			return ;
		i++;
	}
	redir(token);
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
	return (0);
}
