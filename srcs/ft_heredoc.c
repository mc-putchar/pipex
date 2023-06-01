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

// ft_strncmp is really limited by len, nothing bad can happen here, right?
static int	read_heredoc(t_pipex *px)
{
	char	*line;
	int		fd;
	size_t	len;

	len = ft_strlen(px->limiter);
	fd = open(HEREDOC, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (error_handler(px, px->this, OPEN_FAIL, HEREDOC));
	while (1)
	{
		ft_printf("pipex heredoc> ");
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (close(fd), READ_FAIL);
		if (!ft_strncmp(line, px->limiter, len))
			return (close(fd), free(line), EXIT_SUCCESS);
		if (write(fd, line, ft_strlen(line)) < 0)
			return (close(fd), free(line), WRITE_FAIL);
		free(line);
	}
}

int	ft_heredoc(t_pipex *px, int ac, const char **av)
{
	int	err;

	px->limiter = av[2];
	err = read_heredoc(px);
	if (err)
		return (error_handler(px, px->this, err, HEREDOC));
	px->infd = open(HEREDOC, O_RDONLY);
	if (px->infd < 0)
		return (error_handler(px, px->this, OPEN_FAIL, HEREDOC));
	px->outfd = open(av[ac - 1], O_APPEND | O_WRONLY);
	if (px->outfd < 0)
		return (error_handler(px, px->this, OPEN_FAIL, av[ac - 1]));
	px->ncmds = ac - 4;
	px->cmds = av + 3;
	return (EXIT_SUCCESS);
}
