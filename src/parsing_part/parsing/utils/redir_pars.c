/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:24:58 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/04 09:58:30 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_pars2(t_token *token, unsigned int i)
{
	if (token->type[i] == OUTPUTREDIR && ft_strlen(token->word[i]) >= 3)
		print_error(token, 4);
	else if (token->type[i] == INPUTREDIR
		&& ft_strlen(token->word[i]) >= 4)
		print_error(token, 5);
	else if (i + 1 >= token->tlen)
		print_error(token, 3);
}

void	redir_pars(t_token *token)
{
	unsigned int	i;

	i = 0;
	while (token->word[i])
	{
		if (token->type[i] == OUTPUTREDIR || token->type[i] == APPENDREDIR
			|| token->type[i] == INPUTREDIR || token->type[i] == HEREDOC)
		{
			redir_pars2(token, i);
			if (token->err == 1)
				return ;
			if (!(token->type[i + 1] == WORD || token->type[i + 1] == DQUOTED
					|| token->type[i + 1] == SQUOTED)
				&& (i + 3 > token->tlen || (token->type[i + 1] != SEP
						|| !(token->type[i + 2] == WORD || token->type[i + 2]
							== DQUOTED || token->type[i + 2] == SQUOTED))))
				return (free_token(token), print_error(token, 3));
		}
		i++;
	}
}
