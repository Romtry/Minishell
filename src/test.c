/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:17:00 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/30 08:32:06 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token)
{
	unsigned int	i;
	const char		*t_type_str[] = {
		"WORD",
    	"SEP",           // whitespace
    	"PIPE",          // |
    	"INPUTREDIR",    // <
    	"OUTPUTREDIR",   // >
    	"HEREDOC",       // <<
    	"APPENDREDIR",   // >>
    	"SINGLEQUOTE",   // '
    	"DOUBLEQUOTE",   // "
    	"DOLLAR",        // $
    	"EMPTY"          // NULL
	};
	i = 0;
	while (token->word[i])
	{
		printf("word %u = [%s] type = %s\n", i, token->word[i], t_type_str[token->type[i]]);
		i++;
	}
}

void	print_array(char **array)
{
	unsigned int	i;

	i = 0;
	while (array[i])
	{
		printf("[%s]", array[i]);
		i++;
	}
	printf("\n");
}
