/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:14:15 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/04 10:14:37 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n)
	{
		*str = '\0';
		n--;
		str++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

int	handle_redirections(t_cmd *cmd)
{
	int		i;
	int		j;
	char	**new_args;
	int		count;

	i = 0;
	j = 0;
	count = count_args(cmd->word[0]);
	new_args = ft_calloc(count + 1, sizeof(char *));
	if (!new_args)
		return (-1);
	while (cmd->word[0][i])
	{
		if (process_redir(cmd, &i, &j, new_args) == -1)
		{
			free_array(new_args);
			return (-1);
		}
	}
	new_args[j] = NULL;
	free_array(cmd->word[0]);
	cmd->word[0] = new_args;
	return (0);
}
