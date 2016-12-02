#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

void execCommand(char **cmd){
  printf("execCommand\n");
  if (strcmp(cmd[0],"exit") == 0){
    exit(0);
  }
  else if (strcmp(cmd[0],"cd") == 0){
    chdir(cmd[1]);
  }
  else {
    int f = fork();
    if (f==0){
      printf("running %s...\n",cmd[0]);
      execvp(cmd[0],cmd);
    }
    else {
      int status;
      wait(&status);
    }
  }
}

void execInput(char ***input){
  printf("execInput\n");
  int i = 0;
  while (input[i]){
    execCommand(input[i]);
    i++;
  }
}
