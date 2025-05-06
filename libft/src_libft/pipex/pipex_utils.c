/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:57:26 by mhanarte          #+#    #+#             */
/*   Updated: 2025/03/25 14:43:57 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pip_error(char *s)
{
	ft_putstr_fd(s, STDERR_FILENO);
	exit(1);
}

void	close_pipe(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

void	do_pip(int (*p)[2])
{
	close_pipe((*p)[0], (*p)[1]);
	pipe((*p));
}

void	wait_process_children(int i)
{
	int	status;

	while (i > 0)
	{
		waitpid(-1, &status, 0);
		i--;
	}
}

void	check_arg(int ac, char **envp)
{
	if (ac < 5)
		pip_error("wrong number of argument\n");
	if (!envp || !envp[0])
		pip_error("Failure, empty envp\n");
}
