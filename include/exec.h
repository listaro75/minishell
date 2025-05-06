/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luda-cun <luda-cun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:53:30 by luda-cun          #+#    #+#             */
/*   Updated: 2025/05/06 12:12:38 by luda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H
#include "minishell.h"
#include "buit-in.h"
#include "parsing.h"
#include "exit.h"

// # ════════════════════════════════════════════════ #
// #                   🛠️ EXIT                        #
// # ════════════════════════════════════════════════ #

// exit_code.c
void	minishell_error(char *str, int fd, char *color, int status);
void	free_token(t_token *token);

#endif