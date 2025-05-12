/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luda-cun <luda-cun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:43:48 by mhanarte          #+#    #+#             */
/*   Updated: 2025/05/12 16:48:20 by luda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_possible_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (!token)
		return (0);
	if (token->type == PAREN_LEFT)
		tmp = tmp->next;
	if (tmp->type == PIPE || tmp->type == OR || tmp->type == AND
		|| check_end_line(token))
		return (ft_printf("bash: syntax error near unexpected token\n", RED,
				1));
	if (check_between_token(token))
		return (ft_printf("bash: parse error near\n", RED, 1));
	if (check_parenthesis(token))
		return (ft_printf("bash: bad use of parenthesis\n", RED, 1));
	return (0);
}

int	check_between_token(t_token *token)
{
	while (token->next)
	{
		if (token->type == PIPE || token->type == OR || token->type == AND)
		{
			if (!token->next)
				return (1);
			if (token->next->type == PAREN_LEFT
				|| token->next->type == PAREN_RIGHT)
				token = token->next;
			if (!token)
				return (1);
			if (token->next)
			{
				if (token->next->type == PIPE || token->next->type == AND
					|| token->next->type == OR || token->next->type == HEREDOC)
					return (1);
			}
		}
		else if (token->type == REDIR_IN || token->type == REDIR_OUT
			|| token->type == APPEND || token->type == HEREDOC)
		{
			if (!token->next)
				return (1);
			if (token->next->type == PAREN_LEFT
				|| token->next->type == PAREN_RIGHT)
				token = token->next;
			if (!token)
				return (1);
			if (token->next->type == PIPE || token->next->type == REDIR_IN
				|| token->next->type == REDIR_OUT || token->next->type == OR
				|| token->next->type == AND || token->next->type == APPEND
				|| token->next->type == HEREDOC)
				return (1);
		}
		token = token->next;
	}
	return (0);
}

int	check_end_line(t_token *token)
{
	if (token->next)
	{
		while (token->next->next)
			token = token->next;
		if (token->next->type != PAREN_RIGHT)
			token = token->next;
	}
	if (token->type == PIPE || token->type == OR || token->type == AND
		|| token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == HEREDOC || token->type == APPEND)
		return (1);
	return (0);
}

int	check_parenthesis(t_token *token)
{
	t_token	*tmp;
	t_token	*check;
	int		parent;
	int		content;

	tmp = token;
	while (tmp)
	{
		parent = 0;
		if (tmp->type == PAREN_LEFT)
		{
			content = 0;
			while (tmp && tmp->type == PAREN_LEFT)
			{
				parent++;
				tmp = tmp->next;
			}
			if (!tmp || tmp->type == PAREN_RIGHT
				|| is_token_operator(tmp->type))
				return (1);
			while (tmp && tmp->type != PAREN_RIGHT)
			{
				content++;
				check = tmp;
				tmp = tmp->next;
			}
			parent--;
			if (content == 0 || is_token_operator(check->type))
				return (1);
		}
		else
			tmp = tmp->next;
	}
	return (0);
}

int	is_command_token(t_token *token)
{
	return (token->type == WORD);
}
