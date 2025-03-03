/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:23:21 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/12 13:10:06 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_pars(t_token *token, unsigned int i)
{
	if (i == 0 || i == token->tlen - 1 || ft_strlen(token->word[i]) != 1)
	{
		free_token(token);
		print_error(token, 2);
		exit(EXIT_FAILURE);
	}
	if (token->type[i - 1] == WORD || token->type[i - 1] == DOLLAR
		|| token->type[i - 1] == SEP)
	{
		if ((token->type[i + 1] == WORD || token->type[i + 1] == DOLLAR
				|| token->type[i + 1] == SQUOTE || token->type[i + 1] == DQUOTE
				|| token->type[i + 1] == INPUTREDIR || token->type[i + 1] == OUTPUTREDIR
				|| token->type[i + 1] == HEREDOC || token->type[i + 1] == APPENDREDIR)
			|| (token->type[i + 1] == SEP && (token->type[i + 2] == WORD
					|| token->type[i + 2] == DOLLAR || token->type[i + 2] == SQUOTE
					|| token->type[i + 2] == DQUOTE
					|| token->type[i + 2] == INPUTREDIR || token->type[i + 2] == OUTPUTREDIR
					|| token->type[i + 2] == HEREDOC || token->type[i + 2] == APPENDREDIR)))
			return ;
	}
	free_token(token);
	print_error(token, 2);
	exit(EXIT_FAILURE);
}
