#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"

void	ft_execve(char *cmd, char *paths[], char *envp[]);
char	*ft_free_all(char **ptr);
int		ft_openfile(char *filename, int oflag, char *progname);
char	*ft_get_el_in_env(char *envp[], char *key);
char	**ft_get_array_in_env(char *envp[], char *key, char sep);
char	*assemble_excutable_command(char *cmd, char *paths[]);
void	ft_exec_with_pipe(int in, char *cmd, char *paths[], char *envp[]);
void	pipex(char *argv[], char *envp[], int in, int out);

#endif
