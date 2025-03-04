/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:09:31 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/04 10:06:51 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(const char *str, char target)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == target)
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && str[i] != target)
			i++;
	}
	return (count);
}

static char	*grab_words(const char *str, char target, int reset)
{
	static int	i = 0;
	int			start;
	int			end;
	char		*word;

	if (reset)
	{
		i = 0;
		return (NULL);
	}
	while (str[i] == target)
		i++;
	start = i;
	while (str[i] != '\0' && str[i] != target)
		i++;
	end = i;
	if (start == end)
		return (NULL);
	word = malloc(end - start + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, str + start, end - start + 1);
	return (word);
}

char	**ft_split(const char *str, char target)
{
	char	**ret;
	int		j;
	char	*word;
	int		count;

	count = count_words(str, target);
	ret = malloc(sizeof(char *) * (count + 1));
	if (!ret)
		return (NULL);
	j = 0;
	grab_words(str, target, 1);
	word = grab_words(str, target, 0);
	while (word)
	{
		ret[j++] = word;
		word = grab_words(str, target, 0);
	}
	ret[j] = NULL;
	return (ret);
}
