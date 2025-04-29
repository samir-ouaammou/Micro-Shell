#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

short   ft_print_error(char *str)
{
    while (*str)
        write (2, str++, 1);
    return (1);
}

short   ft_handle_cd(char **av, int i) 
{
    if (i != 2)
        return ft_print_error("Error cd: bad arguments\n");
    else if (chdir(av[1]) == -1)
    {
        ft_print_error("Error no such file or directory: ");
        ft_print_error(av[1]);
        ft_print_error("\n");
        return (1);
    }
    return 0;
}

char    *ft_strcat(char *dst, char *src)
{
    short   i;
    short   j;
    char    *res;

    res = malloc(strlen(dst) + strlen(src) + 1);
    if (!res)
        return (NULL);

    i = -1;
    while (dst[++i])
        res[i] = dst[i];

    j = -1;
    while (src[++j])
        res[i++] = src[j];

    res[i] = '\0';

    return (res);
}

short   ft_execute_command(char **av, char **env, int i) 
{
    int     fd[2];
    int     status;
    int     pid;
    int     has_pipe;

    has_pipe = 0;
    if (av[i] && !strcmp(av[i], "|"))
        has_pipe = 1;

    if (has_pipe && pipe(fd) == -1)
        return (ft_print_error("Error fatal\n"));

    pid = fork();
    if (!pid) 
    {
        av[i] = NULL;
        if (has_pipe && (dup2(fd[1], 1) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
            return (ft_print_error("Error fatal\n"));

        execve(ft_strcat("/bin/", *av), av, env);
        ft_print_error("Error Command Not Found: ");
        ft_print_error(*av);
        ft_print_error("\n");
        return (1);
    }

    waitpid(pid, &status, 0);

    if (has_pipe && (dup2(fd[0], 0) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
        return (ft_print_error("Error fatal\n"));

    return (WIFEXITED(status) && WEXITSTATUS(status));
}

int main(int ac, char **av, char **env)
{
    short   i;
    short   j;
    short   status;

    status = 0;
    i = 1;
    if (ac > 1)
    {
        while (av[i])
        {
            j = i;
            while (av[j] && strcmp(av[j], "|") && strcmp(av[j], ";"))
                j++;

            if (!strcmp(av[i], "cd"))
                status = ft_handle_cd(&av[i], j - i);

            else if (j > i)
                status = ft_execute_command(&av[i], env, j - i);

            if (av[j])
                j++;

            i = j;
        }
    }
    
    return (status);
}
