/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luda-cun <luda-cun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:56:31 by mhanarte          #+#    #+#             */
/*   Updated: 2025/05/12 16:45:24 by luda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenisation(char *line)
{
	int		i;
	char	*tmp;
	int		expandable;
	int		quoted;
	char	*word;
	t_token	*token;

	quoted = 0;
	expandable = 0;
	i = 0;
	token = NULL;
	tmp = ft_strtrim(line, " \t\n\r\v\f");
	if (!tmp || !*tmp || is_invalid_line(tmp))
		return (free(tmp), NULL);
	while (tmp[i])
	{
		if (ft_isspace(tmp[i]))
			i++;
		else if (tmp[i] == '|' && tmp[i + 1] != '|')
		{
			token = add_token(&token, PIPE, ft_strdup("|"), 0, 0);
			i++;
		}
		else if (tmp[i] == '>' && tmp[i + 1] != '>')
		{
			token = add_token(&token, REDIR_OUT, ft_strdup(">"), 0, 0);
			i++;
		}
		else if (tmp[i] == '<' && tmp[i + 1] != '<')
		{
			token = add_token(&token, REDIR_IN, ft_strdup("<"), 0, 0);
			i++;
		}
		else if (tmp[i] == '|' && tmp[i + 1] == '|')
		{
			token = add_token(&token, OR, ft_strdup("||"), 0, 0);
			i += 2;
		}
		else if (tmp[i] == '&' && tmp[i + 1] == '&')
		{
			token = add_token(&token, AND, ft_strdup("&&"), 0, 0);
			i += 2;
		}
		else if (tmp[i] == '>' && tmp[i + 1] == '>')
		{
			token = add_token(&token, APPEND, ft_strdup(">>"), 0, 0);
			i += 2;
		}
		else if (tmp[i] == '<' && tmp[i + 1] == '<')
		{
			token = add_token(&token, HEREDOC, ft_strdup("<<"), 0, 0);
			i += 2;
		}
		else if (tmp[i] == '(')
		{
			token = add_token(&token, PAREN_LEFT, ft_strdup("("), 0, 0);
			i++;
		}
		else if (tmp[i] == ')')
		{
			token = add_token(&token, PAREN_RIGHT, ft_strdup(")"), 0, 0);
			i++;
		}
		else
		{
			word = extract_word(tmp, &i, &quoted, &expandable);
			token = add_token(&token, WORD, word, quoted, expandable);
		}
	}
	free(tmp);
	return (token);
}

t_token	*add_token(t_token **lst, t_token_type type, char *content, int quoted,
		int expandable)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->content = content;
	new->quoted = quoted;
	new->expandable = expandable;
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (*lst);
}

char	*extract_word(char *line, int *i, int *quoted, int *expandable)
{
	char	buffer[4096];
	int		j;

	j = 0;
	if (line[*i] == '\'')
	{
		(*i)++;
		*quoted = 1;
		*expandable = 0;
		while (line[*i] != '\'')
		{
			buffer[j] = line[*i];
			j++;
			(*i)++;
		}
		(*i)++;
	}
	else if (line[*i] == '\"')
	{
		(*i)++;
		*quoted = 1;
		*expandable = 1;
		while (line[*i] != '\"')
		{
			buffer[j] = line[*i];
			j++;
			(*i)++;
		}
		(*i)++;
	}
	else
	{
		*quoted = 0;
		*expandable = 1;
		while (line[*i])
		{
			if (line[*i] == '&' && line[*i + 1] != '&')
				;
			else if (is_operator(line[*i]) || line[*i] == '\''
				|| line[*i] == '\"' || ft_isspace(line[*i]))
				break ;
			buffer[j] = line[*i];
			j++;
			(*i)++;
		}
	}
	buffer[j] = '\0';
	return (ft_strdup(buffer));
}
