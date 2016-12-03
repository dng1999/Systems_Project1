#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include "execr.h"

void execRedirO(char **cmd){ // cmd > file
  printf("execRedirO\n");
  char **command = (char **)calloc(10,10);
  char *file;
  
  int ci = 0;
  int i = 0;
  int signPassed = 0;
  while(cmd[i]){
    if (!signPassed){
      command[ci] = cmd[i];
      ci++;
    }
    else if (strcmp(cmd[i],">") == 0){
      signPassed = 1;
    }
    else {
      file = cmd[i];
    }
    i++;
  }
  int filed = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
  dup2(filed,STDOUT_FILENO);
  close(filed);
  execvp(command[0],command);
}

void execRedirI(char **cmd){ // cmd < file
  printf("execRedirI\n");
  char **command;
  char *file;
  
  int ci = 0;
  int i = 0;
  int signPassed = 0;
  while(cmd[i]){
    if (!signPassed){
      command[ci] = cmd[i];
      ci++;
    }
    else if (strcmp(cmd[i],"<") == 0){
      signPassed = 1;
    }
    else {
      file = cmd[i];
    }
    i++;
  }
  int filed = open(file, O_RDONLY, 0644);
  dup2(filed,STDIN_FILENO);
  close(filed);
  execvp(command[0],command);
}

void execPipe(char **cmd){
  printf("execPipe\n");
  char **command1;
  char **command2;

  int ci = 0;
  int fi = 0;
  int i = 0;
  int signPassed = 0;
  while(cmd[i]){
    if (!signPassed){
      command1[ci] = cmd[i];
      ci++;
    }
    else if (strcmp(cmd[i],"|") == 0){
      signPassed = 1;
    }
    else {
      command2[fi] = cmd[i];
      fi++;
    }
    i++;
  }
  int out = dup(STDOUT_FILENO);
  int in = dup(STDIN_FILENO);
  int fd[2];
  pipe(fd);
  int f = fork();
  int status;
  if (f == 0){
    dup2(fd[0],STDOUT_FILENO);
    close(fd[0]);
    execvp(command1[0],command1);
  }
  else{
    wait(&status);
    dup2(fd[1],STDIN_FILENO);
    close(fd[1]);
    execvp(command2[2],command2);
  }
}

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
    char *special = "null";
    if (f==0){
      printf("forked\n");
      int i = 0;
      while (cmd[i]){
	if (strcmp(cmd[i],">") == 0){
	  special = ">";
	}
	else if (strcmp(cmd[i],"<") == 0){
	  special = "<";
	}
	else if (strcmp(cmd[i],"|") == 0){
	  special = "|";
	}
	i++;
      }
      
      printf("running specials\n");
      if (strcmp(special,">") == 0){
	execRedirO(cmd);
      }
      else if (strcmp(special,"<") == 0){
	execRedirI(cmd);
      }
      else if (strcmp(special,"|") == 0){
	execPipe(cmd);
      }
      else{
	printf("running %s...\n",cmd[0]);
	execvp(cmd[0],cmd);
      }
    }
    else {
      printf("waiting...\n");
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
