/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:55:42 by rothiery          #+#    #+#             */
/*   Updated: 2025/01/10 13:29:47 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_pars(t_token *token, unsigned int i)
{
	if (i == 0 || i == token->tlen - 1)
		return (free_token(token), print_error(token, 2));
	else if (ft_strlen(token->word[i]) != 1)
		return (free_token(token), print_error(token, 2));
	else if (token->type[i - 1] == WORD || token->type[i - 1] == DOLLAR)
	{
		if (token->type[i + 1] == WORD || token->type[i + 1] == DOLLAR
			|| token->type[i + 1] == SINGLEQUOTE || token->type[i + 1] == DOUBLEQUOTE)
			return ;
	}
	print_error(token, 2);
}

void	redir(t_token *token, unsigned int i)
{
	if (!token->word[i + 1])
		return(free_token(token), print_error(token, 3));
}

void	pars_dollar(t_token *token, unsigned int i)
{
	t_env	*list;

	list = token->envhead;
	while (list)
	{
		if (ft_strcmp(list->name, token->word[i + 1]) == 0 && token->type[i + 1] == WORD)
		{
			erased_str(token, &i);
			if (i == 0)
				i--;
			free(token->word[i + 1]);
			token->word[i + 1] = ft_strcpy(list->value);
			return ;
		}
		list = list->next;
	}
	if (i < token->tlen && i > 0 && token->type[i - 1] == WORD && token->type[i + 1] != WORD)
		token->word[i - 1] = ft_strjoin(token->word[i - 1], "$");
	else if (token->type[i + 1] == QUOTED)
		token->word[i + 1] = ft_strjoin2("$", token->word[i + 1]);
	else if (i < token->tlen && token->type[i + 1] == WORD)
		erased_str(token, &i);
	erased_str(token, &i);
	token->type[i] = WORD;
}

void	parsing2(t_token *token)
{
	unsigned int	i;

	i = 0;
	while (token->word[i])
	{
		if (token->type[i] == PIPE)
			pipe_pars(token, i);
		else if (token->type[i] == OUTPUTREDIR || token->type[i] == APPENDREDIR
			|| token->type[i] == INPUTREDIR || token->type[i] == HEREDOC)
			redir(token, i);
		else if (token->type[i] == DOLLAR)
		{
			pars_dollar(token, i);
			i--;
		}
		if (token->err == 1)
			return ;
		i++;
	}
}

unsigned int	parsing(t_token *token)
{
	unsigned int	i;

	i = -1;
	while (token->word[++i])
	{
		if (token->type[i] == SINGLEQUOTE || token->type[i] == DOUBLEQUOTE)
			secnd_quote(token, &i, token->type[i]);
		if (token->err == 1)
			return (1);
		// if (i > 0 && token->type[i - 1] == SEP)
		// {
		// 	i--;
		// 	erased_str(token, &i);
		// }
	}
	i--;
	if (token->word[i] && token->type[i] == SEP)
		erased_str(token, &i);
	parsing2(token);
	if (token->err == 1)
		return (1);
	return (0);
}
