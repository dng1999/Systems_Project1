#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(){
  
  char buf[512];
  char *args = buf;
  char *cmd;
  
  printf("Command: ");
  fgets(buf, sizeof(buf), stdin);
  buf[strlen(buf)-1] = NULL;
  
  //parse arguments
  char *arrgs[512];
  int i = 0;
  while (args){
    cmd = strsep(&args, " ");
    arrgs[i] = cmd;
    i++;
  }
  arrgs[i] = NULL;
  
  /*i = 0;
  while(arrgs[i]){
    printf("%s\n",arrgs[i]);
    i++;
    }*/

  execvp(arrgs[0], arrgs);
  return 0;
}
