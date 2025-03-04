/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copies.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:02:28 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/04 10:07:54 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	while (n--)
		*d++ = *s++;
	return (dest);
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

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	i;

	if (!dst || !src)
		return (0);
	srcsize = ft_strlen(src);
	i = 0;
	if (dstsize != 0)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srcsize);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	len;

	len = 0;
	while (s[len] && len < n)
		len++;
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}
