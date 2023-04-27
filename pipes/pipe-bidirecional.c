#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(void)
{
  int pipe1[2], pipe2[2];
  pid_t   pid1, pid2, pid3;

  if (pipe(pipe1) == -1) {
    perror("pipe");
    exit(1);
  }
  
  if (pipe(pipe2) == -1) {
    perror("pipe");
    exit(1);
  }

  if ((pid1 = fork()) == -1 )
    exit(1);
  if (pid1 == 0) {
    close(pipe1[1]); // Fechar a extremidade de escrita do primeiro pipe
    close(pipe2[0]); // Fechar a extremidade de leitura do segundo pipe
    
    char buffer[100];
    read(pipe1[0], buffer, sizeof(buffer)); // Ler a mensagem do pai
    printf("Filho recebeu a mensagem do pai: %s\n", buffer);
    
    char mensagem[] = "Mensagem do filho para o pai";
    write(pipe2[1], mensagem, sizeof(mensagem)); // Escrever a mensagem para o pai
    printf("Filho enviou a mensagem para o pai: %s\n", mensagem);
    
    close(pipe1[0]); // Fechar a extremidade de leitura do primeiro pipe
    close(pipe2[1]); // Fechar a extremidade de escrita do segundo pipe
  } else {
    close(pipe1[0]); // Fechar a extremidade de leitura do primeiro pipe
    close(pipe2[1]); // Fechar a extremidade de escrita do segundo pipe
    
    char mensagem1[] = "Mensagem do pai para o filho";
    write(pipe1[1], mensagem1, sizeof(mensagem1)); // Escrever a mensagem para o filho
    printf("Pai enviou a mensagem para o filho: %s\n", mensagem1);
    
    char buffer[100];
    read(pipe2[0], buffer, sizeof(buffer)); // Ler a mensagem do filho
    printf("Pai recebeu a mensagem do filho: %s\n", buffer);
    
    close(pipe1[1]); // Fechar a extremidade de escrita do primeiro pipe
    close(pipe2[0]); // Fechar a extremidade de leitura do segundo pipe}
  }
  return(0);
}

