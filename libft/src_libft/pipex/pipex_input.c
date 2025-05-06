/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:18:47 by mhanarte          #+#    #+#             */
/*   Updated: 2025/04/24 16:04:35 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_infile(char *infile, int (*p)[2], int hd)
{
	int	fd;

	if (hd)
		return (0);
	fd = open(infile, O_RDWR);
	if (fd >= 0)
	{
		close((*p)[0]);
		(*p)[0] = fd;
		return (0);
	}
	else if (access(infile, F_OK) == 0 && access(infile, R_OK) == -1)
	{
		ft_putstr_fd("zsh: permission denied: ", 2);
		ft_putstr_fd(infile, 2);
		ft_putchar_fd('\n', 2);
	}
	else
	{
		ft_putstr_fd("zsh: no such file or directory: ", 2);
		ft_putstr_fd(infile, 2);
		ft_putchar_fd('\n', 2);
	}
	return (1);
}

int	check_here_doc(char **argv, int (*p)[2])
{
	if ((ft_strncmp(argv[1], "here_doc", 8)) == 0 && (ft_strlen(argv[1]) == 8))
	{
		here_doc_mode(argv[2], (*p)[1]);
		return (1);
	}
	return (0);
}

void	here_doc_mode(char *limiter, int fd_out)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		ft_printf("pipe heredoc> ", NULL, 1);
		line = get_next_line(0);
		if (!line)
			pip_error("STOOOp\n");
		tmp = ft_strtrim(line, "\n");
		if (ft_strcmp(tmp, limiter) == 0
			&& (ft_strlen(tmp) == ft_strlen(limiter)))
		{
			free(line);
			free(tmp);
			break ;
		}
		ft_putstr_fd(line, fd_out);
		free(line);
		free(tmp);
	}
	close(fd_out);
}

void	write_in_file(char *file, int (*pipe1)[2], int (*pipe2)[2], int hd,
		int i)
{
	int		fd_in;
	int		fd_out;
	char	buff[1];
	int		byte;

	if (i % 2 == 0)
		fd_in = (*pipe2[0]);
	else
		fd_in = (*pipe1[0]);
	if (hd)
		fd_out = open(file, O_RDWR | O_CREAT | O_APPEND, 00777);
	else
		fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 00777);
	if (fd_out < 0 || fd_in < 0)
		return ;
	byte = read(fd_in, &buff, sizeof(buff));
	while (byte > 0)
	{
		write(fd_out, &buff, byte);
		byte = read(fd_in, &buff, sizeof(buff));
	}
	close_pipe(fd_out, fd_in);
}

int	check_outfile(char *outfile, int hd)
{
	int	fd;

	if (access(outfile, F_OK) == 0)
	{
		if (access(outfile, W_OK) == -1)
		{
			ft_putstr_fd("zsh: permission denied: ", 2);
			ft_putstr_fd(outfile, 2);
			ft_putchar_fd('\n', 2);
			return (1);
		}
	}
	if (!hd)
	{
		fd = open(outfile, O_WRONLY | O_TRUNC);
		if (fd >= 0)
			close(fd);
	}
	return (0);
}
