/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luda-cun <luda-cun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:12:40 by mhanarte          #+#    #+#             */
/*   Updated: 2025/05/12 16:45:57 by luda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Fonction qui affiche le prompt et récupère l'entrée de l'utilisateur
 *
 * Affiche un prompt coloré, lit l'entrée utilisateur avec readline et ajoute
 * cette entrée à l'historique si elle n'est pas vide. Gère également le cas où
 * l'utilisateur fait Ctrl+D en quittant correctement le programme.
 *
 * @return char* L'entrée utilisateur allouée dynamiquement par readline
 */
char	*prompt(void)
{
	char	*input;

	input = readline(BOLD MAGENTA "➜ minishell: " RESET);
	if (!input)
		minishell_error("Exit\n", 1, RED, 0);
	if (*input)
		add_history(input);
	return (input);
}

/**
 * @brief Fonction principale du shell
 *
 * Initialise les variables nécessaires et crée la boucle principale du shell.
 * À chaque itération : affiche le prompt, récupère l'entrée, la tokenise,
 * vérifie la validité des tokens et les affiche si nécessaire.
 *
 * @param argc Nombre d'arguments du programme
 * @param argv Tableau des arguments du programme
 * @param envp Tableau des variables d'environnement
 * @return int Code de retour du programme (0 en cas de succès)
 */
int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*token;

	(void)argv;
	(void)envp;
	if (argc != 1)
		minishell_error("Wrong number of argument\n", 1, RED, 0);
	while (1)
	{
		input = prompt();
		token = tokenisation(input);
		if (!check_possible_token(token))
			print_token(token);
		free(token);
		free(input);
	}
	return (0);
}
