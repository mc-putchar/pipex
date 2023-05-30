/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:31:56 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/29 12:31:58 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char *const *envp)
{
	t_pipex	*px;

	if (ac < 5)
		return (ft_fprintf(STDERR_FILENO, "Usage: %s %s\n", av[0], USAGE), 1);
	px = init_pipex(ac, av, envp);
	if (!px)
		return (ft_fprintf(STDERR_FILENO, "%s: %s\n", av[0], \
		strerror(errno)), EXIT_FAILURE);
	if (pipex(px, envp))
		return (ft_fprintf(STDERR_FILENO, "%s: %s\n", av[0], \
		strerror(errno)), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
