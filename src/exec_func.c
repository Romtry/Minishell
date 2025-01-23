/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 10:54:40 by rothiery          #+#    #+#             */
/*   Updated: 2025/01/13 16:47:26 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// void	echo(t_token *token, unsigned int *i)
// {
//     i++;
//     while(token->type[i] != 2 && token->type[i] != 10 && i < token->tlen)
//     {
//         printf("%s", token->word[i]);
//         i++;
//     }
//     printf("%s\n", token->word[i]);
//     //printf("\n");
//     parsing2(token, i);
// }

void exec_pwd(void)
{
    char *pwd;

    pwd = getcwd(NULL, 0);
    if (pwd == NULL)
    {
        printf("prout");
        return ;
    }
    printf("%s\n",pwd);
    free(pwd);
}

void    exec_env(t_token *token)
{
    t_env *current;

    current = token->envhead;
    while (current)
    {
        printf("%s=%s\n", current->name, current->value);
        current = current->next;
    }
}
