/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:06:06 by mhanarte          #+#    #+#             */
/*   Updated: 2025/04/28 14:04:03 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token_type_name(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIR_IN)
		return ("REDIR_IN");
	if (type == REDIR_OUT)
		return ("REDI_OUT");
	if (type == APPEND)
		return ("APPEND");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == AND)
		return ("AND");
	if (type == OR)
		return ("OR");
	if (type == END)
		return ("END");
	if (type == PAREN_LEFT)
		return ("PAREN_LEFT");
	if (type == PAREN_RIGHT)
		return ("PAREN_RIGHT");
	return ("UNKNOWN");
}

void	print_token(t_token *token)
{
	if (!token)
		return ;
	while (token)
	{
		printf("Token type: %-12s | value: %s\n",
			get_token_type_name(token->type),
			token->content ? token->content : "(null)");
		if (token->quoted)
			printf("quotate\n");
		else
			printf("non quotate\n");
		if (token->expandable)
			printf("expandable\n");
		else
			printf("non expandable\n");
		token = token->next;
	}
}
