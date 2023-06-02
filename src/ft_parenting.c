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
	return (close(px->pd[0][0]) || close(px->pd[0][1]) ||
			close(px->pd[1][0]) || close(px->pd[1][1]));
}

void	child_firstborn(t_pipex *px, char *const *envp, int *pid)
{
	t_cmd	*cmd;

	free(pid);
	px->infd = open(px->infile, O_RDONLY);
	if (px->infd < 0)
		error_handler(px, px->this, OPEN_FAIL, px->infile);
	if (dup2(px->pd[0][1], STDOUT_FILENO) < 0)
		exit(DUP_FAIL);
	if (dup2(px->infd, STDIN_FILENO) < 0)
		exit(DUP_FAIL);
	if (closeallfds(px) || close(px->infd))
		exit(CLOSE_FAIL);
	cmd = ft_validatecmd(px->cmds[0], px->paths);
	if (cmd)
		execve(cmd->path, cmd->args, envp);
	ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", px->this, px->cmds[0], NO_CMD);
	free_cmd(cmd);
	free_pipex(px);
	exit(EXECVE_FAIL);
}

void	malcolm(t_pipex *px, int n, char *const *envp, int *pid)
{
	t_cmd	*cmd;

	free(pid);
	if (dup2(px->pd[n & 1][1], STDOUT_FILENO) < 0)
		exit(DUP_FAIL);
	if (dup2(px->pd[(n - 1) & 1][0], STDIN_FILENO) < 0)
		exit(DUP_FAIL);
	if (closeallfds(px))
		exit(CLOSE_FAIL);
	cmd = ft_validatecmd(px->cmds[n], px->paths);
	if (cmd)
		execve(cmd->path, cmd->args, envp);
	ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", px->this, px->cmds[n], NO_CMD);
	free_cmd(cmd);
	free_pipex(px);
	exit(EXECVE_FAIL);
}

void	child_last(t_pipex *px, char *const *envp, int *pid)
{
	t_cmd	*cmd;

	free(pid);
	if (!ft_strncmp(px->infile, HEREDOC, ft_strlen(HEREDOC)))
		px->outfd = open(px->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		px->outfd = open(px->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->outfd < 0)
		error_handler(px, px->this, OPEN_FAIL, px->outfile);
	if (dup2(px->outfd, STDOUT_FILENO) < 0)
		exit(DUP_FAIL);
	if (dup2(px->pd[px->ncmds & 1][0], STDIN_FILENO) < 0)
		exit(DUP_FAIL);
	if (closeallfds(px) || close(px->outfd))
		exit(CLOSE_FAIL);
	cmd = ft_validatecmd(px->cmds[px->ncmds - 1], px->paths);
	if (cmd)
		execve(cmd->path, cmd->args, envp);
	ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", px->this, \
	px->cmds[px->ncmds - 1], NO_CMD);
	free_cmd(cmd);
	error_handler(px, px->this, EXECVE_FAIL, NULL);
	free_pipex(px);
	exit(EXECVE_FAIL);
}

int	parenting_is_hard(t_pipex *px, int *pid, int i, char *const *envp)
{
	pid[i] = fork();
	if (pid[i] < 0)
		return (FORK_FAIL);
	if (!pid[i])
		child_firstborn(px, envp, pid);
	while (++i < px->ncmds - 1)
	{	
		pid[i] = fork();
		if (pid[i] < 0)
			return (FORK_FAIL);
		if (!pid[i])
			malcolm(px, i, envp, pid);
		if (close(px->pd[(i - 1) & 1][0]) || close(px->pd[(i - 1) & 1][1]))
			return (CLOSE_FAIL);
		if (pipe(px->pd[(i - 1) & 1]))
			return (PIPE_FAIL);
	}	
	pid[i] = fork();
	if (pid[i] < 0)
		return (FORK_FAIL);
	if (!pid[i])
		child_last(px, envp, pid);
	return (EXIT_SUCCESS);
}
