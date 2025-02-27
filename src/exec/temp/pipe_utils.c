/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 08:54:24 by rothiery          #+#    #+#             */
/*   Updated: 2025/02/27 08:54:49 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    create_pipe(int pipe_fd[2], int need_pipe)
{
    if (need_pipe && pipe(pipe_fd) == -1)
    {
        perror("minishell: pipe");
        return (0);
    }
    return (1);
}
