/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:27:35 by mhanarte          #+#    #+#             */
/*   Updated: 2025/04/24 16:09:25 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"

void	pipex(int argc, char **argv, char **envp);

// process
void	new_process(char *cmd, int (*p1)[2], int (*p2)[2], char **env);
void	new_process_bis(char *cmd, int (*p1)[2], int (*p2)[2], char **env);
void	execute_command(char *cmd, int fd_in, int fd_out, char **envp);
char	*get_path(char *cmd, char **envp);

// input
int		check_here_doc(char **argv, int (*p)[2]);
void	here_doc_mode(char *limiter, int fd_out);
void	write_in_file(char *file, int (*pipe1)[2], int (*pipe2)[2], int hd,
			int i);
int		check_outfile(char *outfile, int hd);
int		check_infile(char *infile, int (*p)[2], int hd);

// utils
void	close_pipe(int fd1, int fd2);
void	do_pip(int (*p)[2]);
void	wait_process_children(int i);
void	pip_error(char *s);
void	check_arg(int ac, char **envp);

#endif