/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenisation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luda-cun <luda-cun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:20:07 by mhanarte          #+#    #+#             */
/*   Updated: 2025/05/06 13:52:32 by luda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Vérifie si un caractère est un opérateur
 *
 * Détermine si le caractère passé en paramètre est un opérateur de shell
 * (|, &, <, >, (, ))
 *
 * @param c Le caractère à vérifier
 * @return int 1 si c'est un opérateur, 0 sinon
 */
int	is_operator(char c)
{
	if (c == '|' || c == '&' || c == '<' || c == '>' || c == '(' || c == ')')
		return (1);
	return (0);
}

/**
 * @brief Vérifie si un token est un opérateur logique
 *
 * Détermine si le type de token correspond à un opérateur logique
 * (PIPE, OR, AND)
 *
 * @param type Le type de token à vérifier
 * @return int 1 si c'est un opérateur logique, 0 sinon
 */
int	is_token_operator(t_token_type type)
{
	if (type == PIPE || type == OR || type == AND)
		return (1);
	return (0);
}

/**
 * @brief Vérifie si une ligne contient des guillemets non fermés
 *
 * Parcourt la ligne pour détecter les guillemets simples ou doubles
 * non fermés, en gérant correctement l'imbrication des guillemets.
 *
 * @param line La chaîne à analyser
 * @return int 1 si des guillemets sont non fermés, 0 sinon
 */
int	check_unclosed_quotes(char *line)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (line[i] == '\"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (in_single || in_double);
}

/**
 * @brief Vérifie si une ligne contient des parenthèses mal équilibrées
 *
 * Parcourt la ligne pour détecter les parenthèses ouvrantes et fermantes,
 * en vérifiant leur équilibre et en ignorant les parenthèses à l'intérieur
 * de guillemets. Détecte aussi les parenthèses fermantes orphelines.
 *
 * @param line La chaîne à analyser
 * @return int 1 si les parenthèses sont mal équilibrées, 0 sinon
 */
int	check_unclosed_paren(char *line)
{
	int	i;
	int	in_single;
	int	in_double;
	int	parent_left;
	int	parent_right;
	int	wrong;

	wrong = 0;
	i = 0;
	in_single = 0;
	in_double = 0;
	parent_left = 0;
	parent_right = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (line[i] == '\"' && !in_single)
			in_double = !in_double;
		else if (line[i] == '(' && !in_double && !in_single)
			parent_left++;
		else if (line[i] == ')' && !in_double && !in_single
			&& parent_left > parent_right)
			parent_right++;
		else if (line[i] == ')')
			wrong++;
		i++;
	}
	if (parent_right != parent_left || wrong)
		return (1);
	return (0);
}

/**
 * @brief Vérifie si une ligne contient des erreurs de syntaxe
 *
 * Effectue diverses vérifications sur la ligne pour détecter des erreurs
 * de syntaxe comme des guillemets ou des parenthèses non fermés.
 * Affiche un message d'erreur approprié si une erreur est détectée.
 *
 * @param line La chaîne à analyser
 * @return int 1 si la ligne contient des erreurs, 0 sinon
 */
int	is_invalid_line(char *line)
{
	if (!line || !*line)
		return (0);
	if (check_unclosed_quotes(line))
		return (ft_printf("Quote must be enclosed by an other same quote\n",
				RED, 2));
	if (check_unclosed_paren(line))
		return (ft_printf("Parenthesis must be enclosed by an other parenthesis\n",
				RED, 2));
	return (0);
}
