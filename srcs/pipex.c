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

t_pipex	*init_pipex(int ac, char **av, char *const *envp)
{
	t_pipex	*px;

	px = malloc(sizeof(t_pipex));
	if (!px)
		return (NULL);
	px->paths = ft_getpaths(envp);
	if (!px->paths)
		return (free(px), NULL);
	if (pipe(px->pd[0]) == -1 || pipe(px->pd[1]) == -1)
		return (free_paths(px->paths), free(px), NULL);
	if (!ft_strncmp(av[1], "here_doc", 9))
		return (ft_heredoc(px, ac, av));
	px->limiter = NULL;
	px->infd = open(av[1], O_RDONLY);
	if (px->infd < 0)
		return (free_paths(px->paths), free(px), NULL);
	px->outfd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (px->outfd < 0)
		return (free_paths(px->paths), free(px), NULL);
	px->ncmds = ac - 3;
	px->cmds = av + 2;
	return (px);
}

int	pipex(t_pipex *px, char *const *envp)
{
	int	i;
	int	*pids;

	i = 0;
	pids = malloc(sizeof(int) * px->ncmds);
	if (!pids)
		return (free_paths(px->paths), free(px), EXIT_FAILURE);
	pids[i] = fork();
	if (pids[i] < 0)
		return (free_paths(px->paths), free(px), free(pids), EXIT_FAILURE);
	if (!pids[i])
		child_firstborn(px, envp);
	while (++i < px->ncmds - 1)
		if (parenting_is_hard(px, i, &pids[i], envp))
			return (free_paths(px->paths), free(px), free(pids), EXIT_FAILURE);
	pids[i] = fork();
	if (pids[i] < 0)
		return (free_paths(px->paths), free(px), free(pids), EXIT_FAILURE);
	if (!pids[i])
		child_last(px, envp);
	if (closeallfds(px))
		return (free_paths(px->paths), free(px), free(pids), EXIT_FAILURE);
	waitpid(pids[i], NULL, 0);
	return (free_paths(px->paths), free(px), free(pids), EXIT_SUCCESS);
}
