/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:24:48 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/27 01:11:28 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipexin(int pfd[2], t_pipex *px, int cmdn, char *const *envp)
{
	t_cmd	*cmd;

	if (dup2(pfd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (close(pfd[0]) || close(pfd[1]))
		exit(EXIT_FAILURE);
	if (dup2(px->infd, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(px->infd);
	cmd = ft_validatecmd(px->cmds[cmdn], px->paths);
	if (cmd)
		execve(cmd->path, cmd->args, envp);
	ft_fprintf(STDERR_FILENO, "pipex: %s: %s\n", \
	"Command not found", px->cmds[cmdn]);
	exit(EXIT_FAILURE);
}

void	pipexout(int pfd[2], t_pipex *px, int cmdn, char *const *envp)
{
	t_cmd	*cmd;

	if (dup2(pfd[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (close(pfd[0]) || close(pfd[1]))
		exit(EXIT_FAILURE);
	if (dup2(px->outfd, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(px->outfd);
	cmd = ft_validatecmd(px->cmds[cmdn], px->paths);
	if (cmd)
		execve(cmd->path, cmd->args, envp);
	ft_fprintf(STDERR_FILENO, "pipex: %s: %s\n", \
	"Command not found", px->cmds[cmdn]);
	exit(EXIT_FAILURE);
}

int	pipex(t_pipex *px, char *const *envp)
{
	int		pfd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(pfd))
		return (-1);
	pid1 = fork();
	if (pid1 == -1)
		return (-1);
	if (!pid1)
		pipexin(pfd, px, 0, envp);
	pid2 = fork();
	if (pid2 == -1)
		return (-1);
	if (!pid2)
		pipexout(pfd, px, 1, envp);
	if (close(pfd[0]) || close(pfd[1]))
		return (-1);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (0);
}

int	main(int ac, char **av, char *const *envp)
{
	t_pipex	*px;

	if (ac < 5)
		return (ft_fprintf(STDERR_FILENO, "Usage: %s %s\n", av[0], USAGE), 1);
	px = malloc(sizeof(t_pipex));
	if (!px)
		return (ft_fprintf(STDERR_FILENO, "%s: %s\n", av[0], strerror(errno)));
	px->infd = open(av[1], O_RDONLY);
	if (px->infd == -1)
		return (ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", \
		av[0], strerror(errno), av[1]), EXIT_FAILURE);
	px->outfd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->outfd == -1)
		return (ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", \
		av[0], strerror(errno), av[ac - 1]), EXIT_FAILURE);
	px->paths = ft_getpaths(envp);
	if (!px->paths)
		return (free(px), ft_fprintf(STDERR_FILENO, "%s: %s\n", \
		av[0], strerror(errno)), EXIT_FAILURE);
	px->ncmds = ac - 3;
	px->cmds = av + 2;
	if (pipex(px, envp))
		return (close(px->infd), close(px->outfd), free(px->paths), free(px), \
		ft_fprintf(STDERR_FILENO, "%s: %s\n", av[0], strerror(errno)), 1);
	return (close(px->infd), close(px->outfd), free(px->paths), free(px), 0);
}

