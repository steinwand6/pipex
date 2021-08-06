/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishigak </var/mail/tishigak>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 22:09:03 by tishigak          #+#    #+#             */
/*   Updated: 2021/08/05 22:11:44 by tishigak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_info(int argc, char *argv[], t_pi *px_info)
{
	extern char	**environ;

	px_info->is_hd_mode = !ft_strncmp(argv[1], "here_doc", 8);
	px_info->num_of_cmds = argc - 3 - px_info->is_hd_mode;
	px_info->prog_name = argv[0];
	if (px_info->is_hd_mode)
	{
		px_info->infile = NULL;
		px_info->limit = argv[2];
	}
	else
		px_info->infile = argv[1];
	px_info->outfile = argv[argc - 1];
	px_info->paths = ft_get_array_in_env(environ, "PATH=", ':');
	px_info->cmds = argv + 2 + px_info->is_hd_mode;
	if (!px_info->paths)
		return (-1);
	return (0);
}
