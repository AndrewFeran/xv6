// childrentester N: fork N children that spin forever. The parent exits.
#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int i, n, pid;
  volatile int x = 0;

  n = (argc > 1) ? atoi(argv[1]) : 3;
  printf(1, "childrentester: parent pid %d, forking %d children\n",
         getpid(), n);
  for(i = 0; i < n; i++){
    pid = fork();
    if(pid < 0){
      printf(1, "childrentester: fork failed\n");
      break;
    }
    if(pid == 0){
      printf(1, "child pid %d\n", getpid());
      for(;;)          // never return to the fork loop
        x++;
    }
  }
  exit();
}
