/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 04:41:38 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/01 04:41:40 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	error_handler(t_pipex *px, char const *name, int err, void const *arg)
{
	int	exitcode;

	exitcode = EXIT_FAILURE;
	if ((err == OPEN_FAIL || err == WRITE_FAIL || err == READ_FAIL) && arg)
		ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", name, (char *)arg, \
		strerror(errno));
	else if (err == TOO_FEW_ARGS)
		ft_printf("Usage: %s %s\n", name, USAGE);
	else if (err == CMD_FAIL)
	{
		exitcode = 127;
		ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", name, NO_CMD, (char *)arg);
	}
	else if (err > EXECVE_FAIL)
		exitcode = 2;
	else if (err && errno)
		ft_fprintf(STDERR_FILENO, "%s: %s\n", name, strerror(errno));
	if (px)
		free_pipex(px);
	exit(exitcode);
}
