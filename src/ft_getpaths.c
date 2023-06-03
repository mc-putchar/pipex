/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpaths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:16:01 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/27 00:50:19 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_getpaths(char *const *envp, char ***ppaths)
{
	char	**paths;
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	if (!envp)
		return (NO_ENVP);
	while (!path && *envp)
		path = ft_strnstr(*envp++, "PATH=", 5);
	if (!path)
		return (1);
	paths = ft_split(path + 5, ':');
	if (!paths)
		return (1);
	while (paths[i] && paths[i][ft_strlen(paths[i]) - 1] != '/')
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
			return (free_paths(paths), 1);
		free(paths[i]);
		paths[i++] = path;
	}
	*ppaths = paths;
	return (0);
}

void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}
