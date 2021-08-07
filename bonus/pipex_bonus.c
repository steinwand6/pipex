/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishigak <tishigak@student.42toky...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 20:06:57 by tishigak          #+#    #+#             */
/*   Updated: 2021/08/07 14:24:56 by tishigak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_check_status(int status, char *name)
{
	int	errno;

	if (status != -1)
		return (status);
	else if (errno)
		perror(name);
	exit(-1);
}

void	ft_execve(t_pi *px_info, int i)
{
	char		**split_cmd;
	char		*build_cmd;
	extern char	**environ;

	errno = 0;
	split_cmd = ft_split(px_info->cmds[i], ' ');
	if (!split_cmd)
		ft_check_status(-1, px_info->prog_name);
	build_cmd = assemble_excutable_command(split_cmd[0], px_info->paths);
	if (!build_cmd)
	{
		ft_putstr_fd(px_info->prog_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(split_cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(-1);
	}
	execve(build_cmd, split_cmd, environ);
	ft_free_all(split_cmd);
	ft_check_status(-1, split_cmd[0]);
}

void	ft_exec_with_pipe(t_pi *px_info, int in, int *pipefd, int i)
{
	int	pid;

	pid = ft_check_status(fork(), NULL);
	if (pid == 0)
	{
		ft_check_status(close(pipefd[0]), px_info->prog_name);
		if (in != -1)
		{
			ft_check_status(dup2(in, 0), px_info->prog_name);
			ft_check_status(close(in), px_info->prog_name);
		}
		if (i + 1 != px_info->num_of_cmds || pipefd[1] != -1)
		{
			ft_check_status(dup2(pipefd[1], 1), px_info->prog_name);
			ft_check_status(close(pipefd[1]), px_info->prog_name);
		}
		if (in == -1 || pipefd[1] == -1)
			exit(-1);
		ft_execve(px_info, i);
	}
	if (in != -1)
		ft_check_status(close(in), px_info->prog_name);
	ft_check_status(close(pipefd[1]), px_info->prog_name);
}

int	pipex(t_pi *px_info)
{
	int	pipefd[2];
	int	i;
	int	in;

	i = 0;
	in = px_info->in;
	while (i < px_info->num_of_cmds)
	{
		ft_check_status(pipe(pipefd), px_info->prog_name);
		if (i + 1 == px_info->num_of_cmds)
		{
			close(pipefd[1]);
			pipefd[1] = px_info->out;
		}
		ft_exec_with_pipe(px_info, in, pipefd, i);
		in = pipefd[0];
		i++;
	}
	if (pipefd[0] != -1)
		ft_check_status(close(pipefd[0]), px_info->prog_name);
	while (i-- > 0)
		wait(NULL);
	ft_free_all(px_info->paths);
	return (0);
}

int	main(int argc, char *argv[])
{
	int		pipefd[2];
	t_pi	px_info;

	if (argc < 5)
		exit(-1);
	ft_check_status(init_info(argc, argv, &px_info), argv[0]);
	if (px_info.is_hd_mode)
	{
		ft_check_status(pipe(pipefd), px_info.prog_name);
		ft_check_status(ft_read_heredoc(&px_info, pipefd[1]), argv[0]);
		px_info.in = pipefd[0];
		px_info.out = ft_openfile(px_info.outfile,
				      O_CREAT | O_APPEND | O_WRONLY, argv[0]);
	}
	else
	{
		px_info.in = ft_openfile(argv[1], O_RDONLY, argv[0]);
		px_info.out = ft_openfile(argv[argc - 1],
				O_CREAT | O_TRUNC | O_WRONLY, argv[0]);
	}
	return (pipex(&px_info));
}
