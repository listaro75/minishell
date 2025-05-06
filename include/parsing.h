/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luda-cun <luda-cun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:58:47 by luda-cun          #+#    #+#             */
/*   Updated: 2025/05/06 12:12:23 by luda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H
#include "minishell.h"
#include "buit-in.h"
#include "exit.h"
#include "exec.h"
// # ════════════════════════════════════════════════ #
// #                   🛠️ PARSING                     #
// # ════════════════════════════════════════════════ #

// check_token.c
int check_possible_token(t_token *token);
int check_end_line(t_token *token);
int check_between_token(t_token *token);
int check_parenthesis(t_token *token);

// tokenisation.c
t_token *tokenisation(char *line);
t_token *add_token(t_token **lst, t_token_type type, char *content, int quoted,
				   int expandable);
char *extract_word(char *line, int *i, int *quoted, int *expandable);

// utils_tokenisation.c
int is_invalid_line(char *line);
int is_operator(char c);
int check_unclosed_paren(char *line);
int is_token_operator(t_token_type type);

// temp.c
void print_token(t_token *token);
char *get_token_type_name(t_token_type type);

#endif