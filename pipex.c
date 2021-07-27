#include "pipex.h"

void	ft_execve(char *cmd, char *paths[], char *envp[])
{
	char	**split_cmd;
	char	*build_cmd;

	errno = 0;
	split_cmd = ft_split(cmd, ' ');
	if (!paths)
		build_cmd = ft_strdup(split_cmd[0]);
	else
		build_cmd = assemble_excutable_command(split_cmd[0], paths);
	execve(build_cmd, split_cmd, envp);
	perror(split_cmd[0]);
	ft_free_all(split_cmd);
	exit(-1);
}

void	ft_exec_with_pipe(int in, char *cmd, char *paths[], char *envp[])
{
	int	pid;
	int	pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		if (pid == 0 && in == -1)
			exit(1);
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		ft_execve(cmd, paths, envp);
	}
	close(pipefd[1]);
	dup2(pipefd[0], 0);
	waitpid(pid, NULL, 0);
}

void	pipex(char *argv[], char *envp[], int in, int out)
{
	char	**paths;

	paths = ft_get_array_in_env(envp, "PATH=", ':');
	argv = argv + 2;
	while (*(argv + 2))
	{
		ft_exec_with_pipe(in, *argv, paths, envp);
		argv++;
		in = 0;
	}
	if (out != -1)
	{
		dup2(out, 1);
		ft_execve(*argv, paths, envp);
	}
	ft_free_all(paths);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	infile;
	int	outfile;

	if (argc < 5)
		exit(-1);
	infile = ft_openfile(argv[1], O_RDONLY, argv[0]);
	outfile = ft_openfile(argv[argc - 1],
			      O_CREAT | O_TRUNC | O_WRONLY, argv[0]);
	dup2(infile, 0);
	close(infile);
	pipex(argv, envp, infile, outfile);
}
