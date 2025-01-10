/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 12:34:52 by rothiery          #+#    #+#             */
/*   Updated: 2025/01/10 13:41:59 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	erased_str2(t_token *token, unsigned int s)
{
	char			**temp;
	unsigned int	i;
	unsigned int	i2;

	i = -1;
	token->tlen--;
	if (token->tlen == 0)
	{
		token->err = 1;
		return ;
	}
	temp = malloc(sizeof(char *) * (token->tlen + 1));
	while (++i < s)
		temp[i] = ft_strcpy(token->word[i]);
	i2 = i;
	i++;
	while (token->word[i])
		temp[i2++] = ft_strcpy(token->word[i++]);
	temp[i2] = NULL;
	free_word(token);
	token->word = temp;
	get_type(token, s, s);
}

void	erased_str(t_token *token, unsigned int *s)
{
	char			**temp;
	unsigned int	i;
	unsigned int	i2;

	i = -1;
	token->tlen--;
	if (token->tlen == 0)
	{
		token->err = 1;
		return ;
	}
	temp = malloc(sizeof(char *) * (token->tlen + 1));
	while (++i < *s)
		temp[i] = ft_strcpy(token->word[i]);
	i2 = i;
	i++;
	while (token->word[i])
		temp[i2++] = ft_strcpy(token->word[i++]);
	temp[i2] = NULL;
	free_word(token);
	token->word = temp;
	get_type(token, *s, *s);
	if (*s > 0)
		*s -= 1;
}

void	get_type(t_token *token, unsigned int one, unsigned int two)
{
	unsigned int	i;
	unsigned int	i2;
	unsigned int	*temp;

	i = -1;
	temp = malloc(sizeof(unsigned int) * (token->tlen + 1));
	while (token->word[++i] && i < one)
		temp[i] = token->type[i];
	if (one != two)
	{
		temp[i] = QUOTED;
		i2 = i + 1;
	}
	else
		i2 = i;
	i = two + 1;
	while (token->word[i2])
	{
		temp[i2] = token->type[i];
		i2++;
		i++;
	}
	temp[i2] = '\0';
	free(token->type);
	token->type = temp;
}

void	free_word(t_token *token)
{
	unsigned int	i;

	i = 0;
	if (token->word)
	{
		while (token->word[i])
		{
			free(token->word[i]);
			i++;
		}
		free(token->word);
		token->word = NULL;
	}
}

char	*ft_strjoin2(char *str1, char *str2)
{
	char			*ret;
	unsigned int	l;
	unsigned int	i;

	i = -1;
	l = ft_strlen(str1) + ft_strlen(str2);
	ret = malloc(sizeof(char) * l + 1);
	while (str1[++i])
		ret[i] = str1[i];
	i--;
	while (str2[++i - ft_strlen(str1)])
		ret[i] = str2[i - ft_strlen(str1)];
	ret[i] = '\0';
	return (ret);
}
