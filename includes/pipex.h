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
# include "get_next_line.h"

# define USAGE "[file1 | here_doc LIMITER] cmd1 cmd2 ... cmdN file2"
# define NO_CMD "Command not found"
# define HEREDOC ".temp_pipex_heredoc_file"

typedef struct s_cmd
{
	char	**args;
	char	*path;
}	t_cmd;

typedef struct s_pipex
{
	int		infd;
	int		outfd;
	int		pd[2][2];
	int		ncmds;
	char	*limiter;
	char	**cmds;
	char	**paths;
}	t_pipex;

t_pipex	*init_pipex(int ac, char **av, char *const *envp);
int		pipex(t_pipex *px, char *const *envp);

int		parenting_is_hard(t_pipex *px, int i, int *pid, char *const *envp);
void	child_firstborn(t_pipex *px, char *const *envp);
void	malcolm(t_pipex *px, int n, char *const *envp);
void	child_last(t_pipex *px, char *const *envp);
int		closeallfds(t_pipex *px);

char	**ft_getpaths(char *const *envp);
void	free_paths(char **paths);

t_cmd	*ft_validatecmd(const char *bin, char **paths);
t_pipex	*ft_heredoc(t_pipex *px, int ac, char **av);

#endif
