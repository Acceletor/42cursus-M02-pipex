/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:18:31 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/04/07 17:31:13 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	open_file(char *file, int in_or_out)
{
	int	fd;

	if (in_or_out == 0)
		fd = open(file, O_RDONLY, 0644);
	if (in_or_out == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open file error\n");
		exit(1);
	}
	return (fd);
}

char	*get_env_path(char *name, char**env)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		key = ft_substr(env[i], 0, j);
		if (ft_strncmp(key, name, j) == 0)
		{
			free(key);
			return (env[i] + j + 1);
		}
		free(key);
		i++;
	}
	return (NULL);
}

void	free_sprited(char **sprited)
{
	int	i;

	i = 0;
	while (sprited[i])
	{
		free(sprited[i]);
		i++;
	}
	free(sprited);
}

char	*getpath(char *cmd, char **env)
{
	int		i;
	char	**allpath;
	char	*path_part;
	char	*exec;
	char	**s_cmd;

	i = 0;
	allpath = ft_split(get_env_path("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_sprited(s_cmd);
			return (exec);
		}
		free(exec);
		i++;
	}
	free_sprited(allpath);
	free_sprited(s_cmd);
	return (NULL);
}

void	exit_handler(int status)
{
	if (status == 1)
		ft_putstr_fd("./pipex infile cmd1 cmd2 outfile\n", 1);
	else if (status == -1)
	{
		perror("pipe failed\n");
		exit(EXIT_FAILURE);
	}
	else if (status == -2)
	{
		perror("fork failed\n");
		exit(EXIT_FAILURE);
	}
	exit(0);
}
