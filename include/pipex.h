/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:18:38 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/04/07 18:01:59 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h> //pipe() fork() dup2() execve() access()
# include <stdlib.h> //malloc() free()
# include <fcntl.h> //file control options (flags for open()) O_RDONLY O_WRONLY
# include <stdio.h> //perror()
# include <sys/types.h> //pid_t - return by fork() id
# include <sys/wait.h> //wait() waitpid()
# include <sys/stat.h> // File status and permission-related stuff

//pipex
void	exec(char *cmd, char **env);
void	child(char **argv, int end[2], char **env);
void	parent(char **argv, int end[2], char **env);

// utils
int		open_file(char *file, int in_or_out);
char	*get_env_path(char *name, char**env);
void	free_splited(char **splited);
char	*getpath(char *cmd, char **env);
void	exit_handler(int status);

#endif