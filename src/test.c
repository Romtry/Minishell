/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:17:00 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/16 15:37:07 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(t_cmd *cmd)
{
	unsigned int	i;
	unsigned int	i2;
	const char		*t_type_str[] = {
		"END",
		"WORD",
		"SEP",				// whitespace
		"PIPE",				// |
		"INPUTREDIR",		// <
		"OUTPUTREDIR",		// >
		"HEREDOC",			// <<
		"APPENDREDIR",		// >>
		"SQUOTE",			// '
		"DQUOTE",			// "
		"DOLLAR",			// $
		"EMPTY",			// NULL
		"DQUOTED",			//"WORD"
		"SQUOTED",			//'WORD'
	};
	i = -1;
	i2 = -1;
	while (cmd->word[++i])
	{
		while (cmd->word[i][++i2])
		{
			printf("word[%u][%u]", i, i2);
			printf(" = [%s]", cmd->word[i][i2]);
			printf(" type = %s\n", t_type_str[cmd->type[i][i2]]);
		}
		i2 = -1;
	}
}

// void	print_token(t_token *token)
// {
// 	unsigned int	i;
// 	const char		*t_type_str[] = {
// 		"END",
// 		"WORD",
// 		"SEP",				// whitespace
// 		"PIPE",				// |
// 		"INPUTREDIR",		// <
// 		"OUTPUTREDIR",		// >
// 		"HEREDOC",			// <<
// 		"APPENDREDIR",		// >>
// 		"SINGLEQUOTE",		// '
// 		"DOUBLEQUOTE",		// "
// 		"DOLLAR",			// $
// 		"EMPTY",			// NULL
// 		"DQUOTED",			// "WORD"
// 		"SQUOTED",			// 'WORD'
// 	};
// 	i = 0;
// 	while (token->word[i])
// 	{
// 		printf("word %u = [%s] ", i, token->word[i]);
// 		printf("type = %s\n", t_type_str[token->type[i]]);
// 		i++;
// 	}
// }

char	**sort_env(char **env)
{
	unsigned int	i;
	unsigned int	i2;
	char			*temp;

	if (!env[1])
		return (printf("declare -x %s", env[0]), NULL);
	i = 1;
	i2 = 0;
	while (env[i])
	{
		while (env[i][i2])
		{
			if (!env[i][i2] || env[i - 1][i2] > env[i][i2])
			{
				temp = env[i - 1];
				env[i - 1] = env[i];
				env[i] = temp;
				if (i == 1)
					i--;
				else
					i -= 2;
				break ;
			}
			else if (env[i - 1][i2] < env[i][i2])
				break ;
			i2++;
		}
		i2 = 0;
		i++;
	}
	return (env);
}

void	print_array(char **array, bool b)
{
	unsigned int	i;
	char			**env;

	i = -1;
	if (b == true)
	{
		env = sort_env(array);
		if (env == NULL)
			return ;
		while (env[++i])
			printf("declare -x %s\n", env[i]);
		return ;
	}
	while (array[++i])
		printf("%s\n", array[i]);
	printf("\n");
}

void	env_print(t_env *env)
{
	if (!env)
	{
		printf(RED"!env\e[0m\n");
		return ;
	}
	while (env->next)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}
