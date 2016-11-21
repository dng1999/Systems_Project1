#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

char **parse_input(char *input){
  char *mcmd[100]; //array of all commands
  int i = 0;
  while (input){
    mcmd[i] = strsep(&input, ";");
    i++;
  }
  return mcmd;
}

char **parse_cmd(char *cmdL){
  char *cmd[100]; //array of single command + args
  int i = 0;
  while (cmdL){
    cmd[i] = strsep(&cmdL," ");
    i++;
  }
  cmd[i] = NULL;
  return cmd;
}

int main(){
  char *input[100];
  fgets(input, sizeof(input), stdin);
  input[strlen(input)-1] = NULL;

  char **mcmd = parse_input(input);
  char *cmds[100];
  int i = 0;
  while(mcmd){
    cmds[i] = parse_cmd(mcmd[i]);
    i++;
  }
  /*
  i = 0;
  while(cmds[0][i]){
    printf("%s\n",cmds[0][i]);
    i++;
    }*/

  //execvp(cmds[0][0],cmds[0]);
  return 0;
}
