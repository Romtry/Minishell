/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:15:54 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/24 11:15:57 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void execute_command(t_cmd *cmd)
{
    int saved_stdout = dup(STDOUT_FILENO);
    int saved_stdin = dup(STDIN_FILENO);

    if (!cmd || !cmd->word[0] || !cmd->word[0][0])
    {
        close(saved_stdout);
        close(saved_stdin);
        return;
    }
    if (handle_redirections(cmd) == -1)
    {
        close(saved_stdout);
        close(saved_stdin);
        return;
    }
    if (cmd->has_pipe >= 2)
    {
        // for (int i = 0; cmd->word[i]; i++)
        // {
        //     printf("Command[%d]: %s\n", i, cmd->word[i][0] ? cmd->word[i][0] : "(null)");
        // }
        execute_piped_commands(cmd);
    }
    else if (is_builtin(cmd->word[0][0]))
    {
        execute_builtin(cmd);
    }
    else
    {
        execute_external(cmd);
    }
    dup2(saved_stdout, STDOUT_FILENO);
    dup2(saved_stdin, STDIN_FILENO);
    close(saved_stdout);
    close(saved_stdin);
}
