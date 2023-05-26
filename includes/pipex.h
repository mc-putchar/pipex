/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:25:40 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/27 00:53:27 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef DEBUG
#  define DEBUG 0
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include "ft_printf.h"

# define USAGE "[file1 | here_doc LIMITER] cmd1 cmd2 ... cmdN file2"

typedef struct s_cmd
{
	char	**args;
	char	*path;
}	t_cmd;

typedef struct s_pipex
{
	int		infd;
	int		outfd;
	int		ncmds;
	char	**cmds;
	char	**paths;
}	t_pipex;

char	**ft_getpaths(char *const *envp);
t_cmd	*ft_validatecmd(const char *bin, char **paths);

#endif
