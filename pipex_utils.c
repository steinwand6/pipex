#include "pipex.h"

char	*ft_free_all(char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i])
	{
		ptr[i] = NULL;
		free(ptr[i++]);
	}
	free(ptr);
	return (NULL);
}

int	ft_openfile(char *filename, int oflag, char *progname)
{
	int	fd;

	errno = 0;
	if (oflag | O_CREAT)
		fd = open(filename, oflag, 0644);
	else
		fd = open(filename, oflag);
	if (fd == -1)
	{
		ft_putstr_fd(progname, 2);
		ft_putstr_fd(": ", 2);
		perror(filename);
	}
	return (open(filename, oflag));
}

char	*ft_get_el_in_env(char *envp[], char *key)
{
	int	start;
	int	i;

	i = 0;
	start = -1;
	while (envp[i])
	{
		start = ft_strncmp(envp[i], key, ft_strlen(key));
		if (!start)
			break ;
		i++;
	}
	if (start)
		return (0);
	return (ft_strdup(envp[i] + start));
}

char	**ft_get_array_in_env(char *envp[], char *key, char sep)
{
	char	*str;
	char	**array;

	str = ft_get_el_in_env(envp, key);
	if (!str)
		return (NULL);
	array = ft_split(str, sep);
	free(str);
	return (array);
}

char	*assemble_excutable_command(char *cmd, char *paths[])
{
	char	*tmp;
	char	*result;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		result = ft_strjoin(tmp, cmd);
		if (!result)
		{
			free(tmp);
			return (NULL);
		}
		if (access(result, X_OK) == 0)
			return (result);
		free(result);
		i++;
	}
	return (NULL);
}
