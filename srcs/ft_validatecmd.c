/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validatecmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 00:52:34 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/27 00:53:41 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_cmd	*check_path(t_cmd *cmd, const char *path)
{
	cmd->path = ft_strjoin(path, cmd->args[0]);
	if (!cmd->path)
		return (NULL);
	if (!access(cmd->path, X_OK))
		return (cmd);
	free(cmd->path);
	cmd->path = NULL;
	return (NULL);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->path)
		free(cmd->path);
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	free(cmd);
}

t_cmd	*ft_validatecmd(const char *bin, char **paths)
{
	int		i;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = ft_split_blocks(bin, ' ', "\"\'");
	if (!cmd->args)
		return (NULL);
	if ((cmd->args[0][0] == '/' || cmd->args[0][0] == '.') &&
		check_path(cmd, ""))
		return (cmd);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
		if (check_path(cmd, paths[i++]))
			return (cmd);
	return (NULL);
}
