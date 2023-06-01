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
# define NO_CMD "command not found"
# define NO_ENVP 0 // change to 1 to refuse to run without envp
# define MALLOC_FAIL 42
# define OPEN_FAIL 2
# define CLOSE_FAIL 3
# define FORK_FAIL 4
# define PIPE_FAIL 5
# define DUP_FAIL 6
# define EXECVE_FAIL 7
# define WRITE_FAIL 8
# define READ_FAIL 9
# define TOO_FEW_ARGS 10
# define WAIT_FAIL 11
# define ARGS_FAIL 12
# define HEREDOC ".temp_pipex_heredoc_file"

typedef struct s_cmd
{
	char	**args;
	char	*path;
}	t_cmd;

typedef struct s_pipex
{
	char const	*this;
	int			ncmds;
	int			infd;
	int			outfd;
	int			pd[2][2];
	char const	**cmds;
	char const	*limiter;
	char		**paths;
}	t_pipex;

int		error_handler(t_pipex *px, char const *name, int err, void const *arg);

void	free_pipex(t_pipex *px);
int		init_pipex(int ac, const char **av, char *const *envp, t_pipex *px);
int		pipex(t_pipex *px, char *const *envp);

int		parenting_is_hard(t_pipex *px, int *pid, int i, char *const *envp);
void	child_firstborn(t_pipex *px, char *const *envp);
void	malcolm(t_pipex *px, int n, char *const *envp);
void	child_last(t_pipex *px, char *const *envp);
int		closeallfds(t_pipex *px);

int		ft_getpaths(char *const *envp, char ***ppaths);
void	free_paths(char **paths);

t_cmd	*ft_validatecmd(const char *bin, char **paths);
void	free_cmd(t_cmd *cmd);

int		ft_heredoc(t_pipex *px, int ac, const char **av);

#endif
