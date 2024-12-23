/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttouahmi <ttouahmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:17:06 by rothiery          #+#    #+#             */
/*   Updated: 2024/12/23 16:17:30 by ttouahmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(t_token *token, char *input)
{
	unsigned int	i;
	unsigned int	c;

	i = 0;
	c = 0;
	token->word = malloc(sizeof(char *) * (count_word(input) + 1));
	token->type = malloc(sizeof(t_type) * (count_word(input) + 1));
	while (input[i] && is_sep(input[i]) == 0)
		i++;
	while (c < count_word(input))
	{
		i += malloc_word(token, input + i, c);
		c++;
	}
	token->word[c] = NULL;
	token->type[c] = '\0';
	print_token(token);
}

void	get_type(t_token *token)
{

}

void	parsing(t_token *token, int i, int tlen)
{
	// int y;

	// y = 0;
	if(i == 0)
		if(exitmentioned(token))
			return ;
	while(token->word[i])
	{
		if(token->type[i] == 0)
		{
			if(!ft_strcmp("echo", token->word[i]))
			{
				puts("echoed\n");
				echo(token, i, tlen);
			}
		}
		i++;
	}
}