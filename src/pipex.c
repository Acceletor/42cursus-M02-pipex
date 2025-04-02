#include "../include/pipex.h"

int open_file(char *file, int in_or_out)
{
    int fd;
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

char *get_env_path(char *name, char**env)
{
    int i;
    int j;
    char *key;

    i = 0;
    while (env[i])
    {
        j = 0;
        while(env[i][j] && env[i][j] != '=')
            j++;
        key = ft_substr(env[i],0, j);
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

void free_sprited(char **sprited)
{
    int i;

    i = 0;
    while (sprited[i])
    {
       free(sprited[i]);
        i++;
    }
    free(sprited);
}

char *getpath(char *cmd, char **env)
{
    int i;
    char **allpath;
    char *path_part;
    char *exec;
    char **s_cmd;

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

void exec(char *cmd, char **env)
{
    char **s_cmd;
    char *path;

    s_cmd = ft_split(cmd, ' ');
    path = getpath(cmd, env);
    if (!path || execve(path, s_cmd, env) == -1)
    {
        ft_putstr_fd("Command not found: ", 1);
        ft_putendl_fd(s_cmd[0], 1);
        free_sprited(s_cmd);
        exit (0);
    }
}

void child(char **argv, int end[2], char **env)
{
    int fd;

    fd = open_file(argv[1], 0);
    dup2(fd, 0);
    dup2(end[1], 1);
    close(end[0]);
    exec(argv[2], env);
}

void parent(char **argv, int end[2], char **env)
{
    int fd;
    fd = open_file(argv[4], 1);
    dup2(end[0], 0);
    dup2(fd,1);
    close(end[1]);
    exec(argv[3], env);

}

void exit_handler(int status)
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


int main(int argc, char **argv, char **env)
{
    int end[2];
    pid_t pid;

    if (argc != 5)
        exit_handler(1);
    if(pipe(end) == -1)
        exit_handler(-1);
    pid = fork();
    if(pid < 0)
        exit_handler(-2);
    else if (pid == 0)
        child(argv, end, env);
    else
        // waitpid(pid, NULL, 0);
        parent(argv, end, env);
    return(0);
}