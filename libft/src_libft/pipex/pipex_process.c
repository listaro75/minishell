/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:02:19 by mhanarte          #+#    #+#             */
/*   Updated: 2025/04/24 16:06:50 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_paths_bis(char **envp)
{
	char	*path;
	char	**paths;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	path = envp[i] + 5;
	paths = ft_split(path, ':');
	return (paths);
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	paths = get_paths_bis(envp);
	cmd = ft_strjoin("/", cmd);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(cmd);
			ft_free_tab(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free(cmd);
	ft_free_tab(paths);
	return (NULL);
}

void	execute_command(char *cmd, int fd_in, int fd_out, char **envp)
{
	char	**cmds;
	char	*path;

	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
	cmds = ft_split(cmd, ' ');
	path = get_path(cmds[0], envp);
	if (!path)
	{
		ft_putstr_fd("pipex: command not found: ", STDERR_FILENO);
		ft_putstr_fd(cmds[0], STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		free(path);
		ft_free_tab(cmds);
		exit(127);
	}
	execve(path, cmds, envp);
	free(path);
	ft_free_tab(cmds);
	exit(127);
}

void	new_process(char *cmd, int (*p1)[2], int (*p2)[2], char **env)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		pip_error("Error when forking (1).");
	if (pid == 0)
	{
		close_pipe((*p1)[1], (*p2)[0]);
		execute_command(cmd, (*p1)[0], (*p2)[1], env);
		exit(127);
	}
	else
		do_pip(p1);
}

void	new_process_bis(char *cmd, int (*p1)[2], int (*p2)[2], char **env)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		pip_error("Error when forking (1).");
	if (pid == 0)
	{
		close_pipe((*p2)[1], (*p1)[0]);
		execute_command(cmd, (*p2)[0], (*p1)[1], env);
		exit(127);
	}
	else
		do_pip(p2);
}
