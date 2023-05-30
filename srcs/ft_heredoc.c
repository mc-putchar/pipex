/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:46:29 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/29 12:46:30 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	read_heredoc(t_pipex *px)
{
	char	*line;
	int		fd;
	size_t	len;

	len = ft_strlen(px->limiter);
	fd = open(HEREDOC, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (EXIT_FAILURE);
	while (1)
	{
		ft_printf("pipex heredoc> ");
		line = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(line, px->limiter, len))
			return (close(fd), free(line), EXIT_SUCCESS);
		if (write(fd, line, ft_strlen(line)) < 0)
			return (close(fd), unlink(HEREDOC), free(line), EXIT_FAILURE);
	}
}

t_pipex	*ft_heredoc(t_pipex *px, int ac, char **av)
{
	px->limiter = av[2];
	if (read_heredoc(px))
		return (free_paths(px->paths), free(px), NULL);
	px->infd = open(HEREDOC, O_RDONLY);
	px->outfd = open(av[ac - 1], O_APPEND | O_WRONLY);
	if (px->infd < 0 || px->outfd < 0)
		return (free_paths(px->paths), free(px), NULL);
	px->ncmds = ac - 4;
	px->cmds = av + 3;
	return (px);
}
