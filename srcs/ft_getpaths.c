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

/*
** Returns an array of strings containing the paths from the PATH environment
** variable with '/' appended. The array must be freed by the caller.
** @param envp: the environment variables
** @return: an array of strings containing the paths from the PATH environment
*/
char	**ft_getpaths(char *const *envp)
{
	char	*path;
	char	**paths;
	int		i;

	path = NULL;
	i = 0;
	while (!path && *envp)
		path = ft_strnstr(*envp++, "PATH=", 5);
	if (path)
		paths = ft_split(path + 5, ':');
	if (!path || !paths)
		return (NULL);
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		free(paths[i]);
		if (!path)
		{
			while (i--)
				free(paths[i]);
			return (free(paths), NULL);
		}
		paths[i++] = path;
	}
	return (paths);
}
