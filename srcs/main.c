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

int	main(int ac, const char **av, char *const *envp)
{
	t_pipex	*px;
	int		err;

	if (ac < 5)
		return (error_handler(NULL, av[0], TOO_FEW_ARGS, NULL));
	errno = 0;
	px = malloc(sizeof(t_pipex));
	if (!px)
		return (error_handler(NULL, av[0], MALLOC_FAIL, NULL));
	errno = 0;
	err = init_pipex(ac, av, envp, px);
	if (err)
		return (error_handler(px, av[0], err, NULL));
	errno = 0;
	err = pipex(px, envp);
	if (err)
		return (error_handler(px, av[0], err, NULL));
	free_pipex(px);
	return (EXIT_SUCCESS);
}
