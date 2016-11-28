#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

struct cmdLine parse_cmd(char *cmdL);
struct cmdArr parse_line(char *cmdL);
void run_cmd(struct cmdLine cmdL);

struct cmdLine{
  char *cmd[512];
};

struct cmdArr{
  struct cmdLine arr[512];
};

int main(){
  char input[512];
  char *iP = input;

  fgets(input, sizeof(input), stdin);
  input[strlen(input)-1] = NULL;

  printf("input: %s\n",input);

  struct cmdArr lines = parse_line(input);

  int i = 0;
  for(i;lines.arr[i].cmd[0];i++){
    int f = fork();
    wait();
    printf("%d: %d\n",i,f);
    if (f==0){
      execvp(lines.arr[i].cmd[0],lines.arr[i].cmd);
    }
  }
  return 0;
}

//--------------------------------

struct cmdArr parse_line(char *cmdL){
  struct cmdArr multi;
  int i = 0;
  while (cmdL){
    multi.arr[i] = parse_cmd(strsep(&cmdL, ";"));
    i++;
  }
  struct cmdLine nil;
  nil.cmd[0] = NULL;
  multi.arr[i] = nil;
  return multi;
}

struct cmdLine parse_cmd(char *cmdL){
  struct cmdLine single; //array of single command + args
  int i = 0;
  while (cmdL){
    single.cmd[i] = strsep(&cmdL," ");
    i++;
   }
   single.cmd[i] = NULL;
  return single;
}

void run_cmd(struct cmdLine cmdL){
  char *redir;
  
}
