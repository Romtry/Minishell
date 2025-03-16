/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:17:00 by rothiery          #+#    #+#             */
/*   Updated: 2025/03/16 12:54:57 by rothiery         ###   ########.fr       */
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

void	env_print(t_env *env, bool b)
{
	if (!env)
	{
		printf(RED"!env\e[0m\n");
		return ;
	}
	while (env->next)
	{
		if (b == true)
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
		else
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}
