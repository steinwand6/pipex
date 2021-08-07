/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishigak <tishigak@student.42toky...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 21:23:57 by tishigak          #+#    #+#             */
/*   Updated: 2021/08/07 12:33:42 by tishigak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/wait.h>

typedef struct s_pipexinfo
{
	int			in;
	int			out;
	int			num_of_cmds;
	int			is_hd_mode;
	char		**paths;
	char		**cmds;
	char		*prog_name;
	char		*infile;
	char		*outfile;
	char		*limit;
}				t_pi;

int		init_info(int argc, char *argv[], t_pi *px_info);
int		ft_check_status(int status, char *name);
int		ft_read_heredoc(t_pi *px_info, int fd);
int		pipex(t_pi *px_info);
char	*ft_free_all(char **ptr);
int		ft_openfile(char *filename, int oflag, char *prog_name);
char	*ft_get_el_in_env(char *const *envp, char *key);
char	**ft_get_array_in_env(char *const *envp, char *key, char sep);
char	*assemble_excutable_command(char *cmd, char *paths[]);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *src);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	**ft_split(char const *str, char c);
void	ft_puterror(char *site, int to_exit, char *prog_name);
int		ft_gnl_split(char **strage, char **line);
char	*ft_gnl_strchr(const char *s, int c);

#endif
