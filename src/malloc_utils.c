/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:20:13 by rothiery          #+#    #+#             */
/*   Updated: 2025/01/24 11:03:03 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *str1, char *str2)
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
	free(str1);
	ret[i] = '\0';
	return (ret);
}

char	*ft_strcpy(char *str)
{
	unsigned int	i;
	char			*ret;

	i = 0;
	ret = malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
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

char	**array_cpy(char **arr)
{
	unsigned int	i;
	unsigned int	i2;
	char			**ret;

	i = 0;
	i2 = 0;
	while (arr[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (arr[++i])
	{
		while (arr[i][i2])
			i2++;
		ret[i] = malloc(sizeof(char) * (i2 + 1));
		i2 = -1;
		while (arr[i][++i2])
			ret[i][i2] = arr[i][i2];
		ret[i][i2] = '\0';
		i2 = 0;
	}
	ret[i] = NULL;
	return (ret);
}

void	realloc_word(t_token *token, unsigned int *one, unsigned int two)
{
	unsigned int	i2;
	unsigned int	i;
	char			**temp;

	i = -1;
	token->tlen -= (two - *one);
	temp = malloc(sizeof(char *) * (token->tlen + 1));
	while (++i < *one)
		temp[i] = ft_strcpy(token->word[i]);
	i2 = i++;
	temp[i2] = ft_strcpy(token->word[i]);
	while (++i < two)
		temp[i2] = ft_strjoin(temp[i2], token->word[i]);
	while (token->word[++i])
		temp[++i2] = ft_strcpy(token->word[i]);
	temp[i2 + 1] = NULL;
	free_word(token);
	token->word = temp;
	get_type(token, *one, two);
}
