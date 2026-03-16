#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64
int main () {
  
  printf("\n###########################################");
  printf("\n########### BUBU (.)(.) BUBU ##############");
  printf("\n###########################################\n");
  char input[MAX_INPUT];
  char* args[MAX_ARGS];

  while (1) {
    printf("(.)(.) >");
    fflush(stdout);

    if(fgets(input, MAX_INPUT, stdin) == NULL) {
      perror("fgets failed, it is equal to NULL");
      continue;

    }
    
    input[strcspn(input, "\n")] = '\0';
  

    if(strcmp(input, "exit") == 0){
      printf("Thank you for using bubu shell all hail bubu (.)(.)");
      break;
    }

    char* token = strtok(input, " ");
    int i = 0;

    while (token != NULL && i < MAX_ARGS) {
      args[i++] = token;
      token = strtok(NULL, " ");
    }

    args[i] = NULL;

    if(strcmp(args[0], "cd") == 0){
      if(args[1] == NULL) {
        perror("cd is missing args");
      } else if (chdir(args[1]) != 0 ) {
        perror("cd failed args[1] == 0");
      }
      continue;
    }

    pid_t pid = fork();

    if (pid == 0) {
      execvp(args[0], args);
      perror("execvp failed");
      exit(EXIT_FAILURE);

    } else if (pid > 0 ) {
      int status;
      waitpid(pid, &status, 0);
      printf("Exit status: %d \n", status);
    } else {
      perror("for failed maybe");
    }

  }
  return 0;
}
