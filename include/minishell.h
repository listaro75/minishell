/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luda-cun <luda-cun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:58:32 by mhanarte          #+#    #+#             */
/*   Updated: 2025/05/06 13:49:06 by luda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/include_libft/libft.h"

typedef enum e_token_type
{
	WORD,        // Un mot classique (commande, argument, nom de fichier)
	PIPE,        // |
	REDIR_IN,    // <
	REDIR_OUT,   // >
	APPEND,      // >>
	HEREDOC,     // <<
	AND,         // &&
	OR,          // ||
	PAREN_LEFT,  // (
	PAREN_RIGHT, // )
	END          // Fin de la liste
}	t_token_type;

typedef struct s_token
{
	t_token_type type;    // Type du token
	char *content;        // Texte du token
	int quoted;           // Était-il entre quotes ?
	int expandable;       // Faut-il l'expanser ? (ex: $VAR)
	struct s_token *next; // Token suivant dans la liste
}	t_token;

# include "buit-in.h"
# include "exec.h"
# include "exit.h"
# include "parsing.h"

#endif