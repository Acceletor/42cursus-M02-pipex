/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:18:28 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/04/07 18:07:49 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	if (!cmd || cmd[0] == 0)
	{
		ft_putstr_fd("Command not found: \n", 1);
		exit (1);
	}
	s_cmd = ft_split(cmd, ' ');
	path = getpath(cmd, env);
	if (!path || execve(path, s_cmd, env) == -1)
	{
		ft_putstr_fd("Command not found: ", 1);
		ft_putendl_fd(s_cmd[0], 1);
		free_splited(s_cmd);
		exit (1);
	}
}

void	child(char **argv, int end[2], char **env)
{
	int	fd;

	fd = open_file(argv[1], 0);
	dup2(fd, 0);
	dup2(end[1], 1);
	close(end[0]);
	exec(argv[2], env);
}

void	parent(char **argv, int end[2], char **env)
{
	int	fd;

	fd = open_file(argv[4], 1);
	dup2(end[0], 0);
	dup2(fd, 1);
	close(end[1]);
	exec(argv[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int		end[2];
	pid_t	pid;

	if (argc != 5)
		exit_handler(1);
	if (pipe(end) == -1)
		exit_handler(-1);
	pid = fork();
	if (pid < 0)
		exit_handler(-2);
	else if (pid == 0)
		child(argv, end, env);
	else
	{
		waitpid(pid, NULL, 0);
		parent(argv, end, env);
	}
	return (0);
}
