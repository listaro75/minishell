/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:33:59 by mhanarte          #+#    #+#             */
/*   Updated: 2025/04/24 16:09:16 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int argc, char **argv, char **envp)
{
	int	i;
	int	pipe1[2];
	int	pipe2[2];
	int	here_doc;
	int	access;

	check_arg(argc, envp);
	pipe(pipe1);
	pipe(pipe2);
	here_doc = check_here_doc(argv, &pipe2);
	access = check_outfile(argv[argc - 1], here_doc);
	i = check_infile(argv[1], &pipe2, here_doc);
	while (i < argc - 3 - here_doc - access)
	{
		if (i % 2 == 0)
			new_process(argv[i + here_doc + 2], &pipe2, &pipe1, envp);
		else
			new_process_bis(argv[i + here_doc + 2], &pipe2, &pipe1, envp);
		i++;
	}
	close_pipe(pipe1[1], pipe2[1]);
	wait_process_children(i);
	write_in_file(argv[argc - 1], &pipe1, &pipe2, here_doc, i);
	close_pipe(pipe1[0], pipe2[0]);
}
