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

void	free_pipex(t_pipex *px)
{
	if (!px)
		return ;
	if (px->limiter)
	{
		unlink(HEREDOC);
		px->limiter = NULL;
	}
	if (px->paths)
		free_paths(px->paths);
	free(px);
}

int	init_pipex(int ac, const char **av, char *const *envp, t_pipex *px)
{
	if (!px)
		return (MALLOC_FAIL);
	px->this = av[0];
	px->paths = NULL;
	if (ft_getpaths(envp, &px->paths))
		return (MALLOC_FAIL);
	if (pipe(px->pd[0]) == -1 || pipe(px->pd[1]) == -1)
		return (free_pipex(px), PIPE_FAIL);
	if (!av[1] || av[1][0] == '<' || av[1][0] == '-' ||
	!ft_strncmp(av[1], "here-doc", 9) || !ft_strncmp(av[1], "heredoc", 8) ||
	!ft_strncmp(av[1], "heredoc", 8) || !ft_strncmp(av[1], "here_doc", 9))
		return (ft_heredoc(px, ac, av));
	px->limiter = NULL;
	px->infd = open(av[1], O_RDONLY);
	if (px->infd < 0)
		return (error_handler(px, av[0], OPEN_FAIL, av[1]));
	px->outfd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (px->outfd < 0)
		return (error_handler(px, av[0], OPEN_FAIL, av[ac - 1]));
	px->ncmds = ac - 3;
	px->cmds = av + 2;
	return (EXIT_SUCCESS);
}

int	pipex(t_pipex *px, char *const *envp)
{
	int	i;
	int	*pids;
	int	err;
	int	status;

	i = 0;
	pids = malloc(sizeof(int) * px->ncmds);
	if (!pids)
		return (MALLOC_FAIL);
	err = parenting_is_hard(px, pids, i, envp);
	if (err)
		return (free(pids), err);
	if (closeallfds(px))
		return (free(pids), CLOSE_FAIL);
	while (i++ <= px->ncmds)
	{
		if (waitpid(pids[px->ncmds - i], &status, 0)
			&& WIFEXITED(status) && WEXITSTATUS(status))
		{
			free(pids);
			error_handler(px, px->this, WEXITSTATUS(status), NULL);
		}
	}
	return (free(pids), EXIT_SUCCESS);
}
