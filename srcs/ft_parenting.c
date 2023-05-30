/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parenting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:36 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/29 14:44:37 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	closeallfds(t_pipex *px)
{
	return (close(px->pd[0][0]) | close(px->pd[0][1]) |
			close(px->pd[1][0]) | close(px->pd[1][1]) |
			close(px->infd) | close(px->outfd));
}

void	child_firstborn(t_pipex *px, char *const *envp)
{
	t_cmd	*cmd;

	if (dup2(px->pd[0][1], STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
	if (dup2(px->infd, STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	if (closeallfds(px))
		exit(EXIT_FAILURE);
	cmd = ft_validatecmd(px->cmds[0], px->paths);
	if (cmd)
		execve(cmd->path, cmd->args, envp);
	ft_fprintf(STDERR_FILENO, "pipex: %s: %s\n", px->cmds[0], NO_CMD);
	free(cmd->path);
	free(cmd->args);
	free(cmd);
	exit(EXIT_FAILURE);
}

void	malcolm(t_pipex *px, int n, char *const *envp)
{
	t_cmd	*cmd;

	if (dup2(px->pd[n & 1][1], STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
	if (dup2(px->pd[(n - 1) & 1][0], STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	if (closeallfds(px))
		exit(EXIT_FAILURE);
	cmd = ft_validatecmd(px->cmds[n], px->paths);
	if (cmd)
		execve(cmd->path, cmd->args, envp);
	ft_fprintf(STDERR_FILENO, "pipex: %s: %s\n", px->cmds[n], NO_CMD);
	free(cmd->path);
	free(cmd->args);
	free(cmd);
	exit(EXIT_FAILURE);
}

void	child_last(t_pipex *px, char *const *envp)
{
	t_cmd	*cmd;

	if (dup2(px->outfd, STDOUT_FILENO) < 0)
		exit(EXIT_FAILURE);
	if (dup2(px->pd[(px->ncmds - 2) & 1][0], STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	if (closeallfds(px))
		exit(EXIT_FAILURE);
	cmd = ft_validatecmd(px->cmds[px->ncmds - 1], px->paths);
	if (cmd)
		execve(cmd->path, cmd->args, envp);
	ft_fprintf(STDERR_FILENO, "pipex: %s: %s\n", px->cmds[px->ncmds - 1], \
	NO_CMD);
	free(cmd->path);
	free(cmd->args);
	free(cmd);
	exit(EXIT_FAILURE);
}

int	parenting_is_hard(t_pipex *px, int i, int *pid, char *const *envp)
{
	*pid = fork();
	if (*pid < 0)
		return (EXIT_FAILURE);
	if (!*pid)
		malcolm(px, i, envp);
	if (close(px->pd[(i - 1) & 1][0]) | close(px->pd[(i - 1) & 1][1]))
		return (EXIT_FAILURE);
	if (pipe(px->pd[(i - 1) & 1]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
