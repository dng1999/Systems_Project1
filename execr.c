#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

void execRedirO(char **cmd){ // cmd > file
  printf("execRedirO\n");
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
    else if (strcmp(cmd[i],">") == 0){
      signPassed = 1;
    }
    else {
      file = cmd[i];
    }
    i++;
  }
  int filed = open(file, "O_RDWR");
  dup2(filed,STDOUT_FILENO);
  close(filed);
  execvp(command[0],command);
}
void execRedirI(char **cmd){
  printf("execRedirI\n");
  
}

void execPipe(char **cmd){
  printf("execPipe\n");
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
    char *special;
    if (f==0){
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
      
      if (strcmp(special,">") == 0){
	execRedirO(cmd);
      }
      else if (strcmp(special,"<") == 0){
	execRedirI(cmd);
      }
      else if (strcmp(special,"|") == 0){
	execPipe(cmd);
      }
      //put special commands under here
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
