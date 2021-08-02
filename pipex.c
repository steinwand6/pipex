#include "pipex.h"

void	ft_puterror(char *site, int to_exit, char *prog_name)
{
	int	errno;

	if (errno == 14)
	{
		ft_putstr_fd(prog_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(site, 2);
		ft_putendl_fd(": command not found.", 2);
	}
	else if (errno)
		perror(site);
	if (to_exit)
		exit(errno);
}

void	ft_execve(char *cmd, char *paths[], char *prog_name)
{
	char	**split_cmd;
	char	*build_cmd;
	int	errno;

	errno = 0;
	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd)
		ft_puterror(prog_name, 1, prog_name);
	if (!paths)
		build_cmd = ft_strdup(split_cmd[0]);
	else
		build_cmd = assemble_excutable_command(split_cmd[0], paths);
	if (!build_cmd)
		ft_puterror(prog_name, 1, prog_name);
	execve(build_cmd, split_cmd, g_envp);
	ft_puterror(split_cmd[0], 0, prog_name);
	ft_free_all(split_cmd);
	exit(errno);
}

int	ft_exec_with_pipe(int in, char *cmd, char *paths[], char *prog_name)
{
	int	pid;
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		ft_puterror(prog_name, 1, prog_name);
	pid = fork();
	if (pid == -1)
		ft_puterror(prog_name, 1, prog_name);
	if (pid == 0)
	{
		if (in == -1)
			exit(1);
		if (dup2(in, 0) + dup2(pipefd[1], 1) < 0)
			ft_puterror(cmd, 1, prog_name);
		ft_execve(cmd, paths, prog_name);
	}
	if (close(pipefd[1]) == -1)
		ft_puterror(prog_name, 1, prog_name);
	if (in != -1 && close(in) == -1)
		ft_puterror(prog_name, 1, prog_name);
	return (pipefd[0]);
}

int    pipex(char *argv[], int in, int out)
{
	char	**paths;
	char	*prog_name;

	prog_name = argv[0];
	paths = ft_get_array_in_env(g_envp, "PATH=", ':');
	argv = argv + 2 + !(ft_strncmp(argv[1], "here_doc", 7));
	while (*(argv + 2))
	{
		in = ft_exec_with_pipe(in, *argv, paths, prog_name);
		argv++;
	}
	if (out != -1)
	{
		dup2(out, 1);
		dup2(in, 0);
		close(out);
		ft_execve(*argv, paths, prog_name);
		wait(0);
	}
	ft_free_all(paths);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	filefd[2];
	int	pipefd[2];

	g_envp = (char *const *)envp;
	if (argc < 5)
		exit(-1);
	if (ft_strncmp("here_doc", argv[1], 7))
	{
		filefd[0] = ft_openfile(argv[1], O_RDONLY, argv[0]);
		filefd[1] = ft_openfile(argv[argc - 1],
				  O_CREAT | O_TRUNC | O_WRONLY, argv[0]);
	}
	else
	{
		if (pipe(pipefd) == -1)
			ft_puterror(argv[0], 1, NULL);
		if (ft_read_heredoc(pipefd[1], argv[2]) == -1)
			ft_puterror(argv[0], 0, NULL);
		filefd[0] = pipefd[0];
		filefd[1] = ft_openfile(argv[argc - 1],
				      O_CREAT | O_APPEND | O_WRONLY, argv[0]);

	}
	return (pipex(argv, filefd[0], filefd[1]));
}
