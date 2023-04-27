#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(void)
{
  int     fd[2], nbytes;
  pid_t   pid1, pid2, pid3;

  if (pipe(fd) == -1) {
    perror("pipe");
    exit(1);
  };
  
  if((pid1= fork()) == -1)
  {
    perror("fork");
    exit(1);
  }
  if(pid1 == 0)
  {
    /* Child process closes up input side of pipe */
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
		execl("/bin/ls", "ls", "-la", NULL);

    exit(0);
  }
  
  if((pid2= fork()) == -1)
  {
    perror("fork2");
    exit(1);
  }
  if(pid2 == 0)
  {
    /* Child process closes up input side of pipe */
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
		execl("/bin/sort", "sort", NULL);

    exit(0);
  }

  if((pid3= fork()) == -1)
  {
    perror("fork3");
    exit(1);
  }
  if(pid3 == 0)
  {
    /* Child process closes up input side of pipe */
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
		execl("/bin/wc", "wc", "-l", NULL);
    exit(0);
  }

  close(fd[0]);
  close(fd[1]);
  waitpid(pid1, NULL, 0);
  waitpid(pid2, NULL, 0);
  waitpid(pid3, NULL, 0);

  return(0);
}
