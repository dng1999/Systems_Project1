#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

char *parse_line(char *cmdL){
  char *cmd[512];
  int i = 0;
  while (cmdL){
    cmd[i] = strsep(&cmdL, ";");
    i++;
  }
  return &cmd;
}

char *parse_cmd(char *cmdL){
  char *cmd[512]; //array of single command + args
  int i = 0;
  while (cmdL){
    cmd[i] = strsep(&cmdL," ");
    i++;
  }
  return &cmd;
}

int main(){
  char input[512];
  char *iP = input;

  fgets(input, sizeof(input), stdin);
  input[strlen(input)-1] = 0;

  printf("input: %s\n",input);

  char *lines = parse_cmd(input); 
  int i = 0;
  while(lines[i]){
    printf("%s",lines[i]);
    i++;
  }
  return 0;
}
