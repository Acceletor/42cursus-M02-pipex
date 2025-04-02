#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h> //pipe() fork() dup2() execve() access()
# include <stdlib.h> //malloc() free()
# include <fcntl.h> //file control options (flags for open()) O_RDONLY O_WRONLY
# include <stdio.h> //perror()
# include <sys/types.h> //pid_t - return by fork() id
# include <sys/wait.h> //wait() waitpid()
# include <sys/stat.h> // File status and permission-related stuff 0644, permission: rw-r--r--






#endif