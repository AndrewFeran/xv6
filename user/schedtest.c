// schedtest T1 T2 ...: fork one spinning child per argument.
// Each child sets its tickets to its argument. The parent exits.
#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int i, n, pid;
  volatile int x = 0;

  printf(1, "schedtest: parent pid %d\n", getpid());
  for(i = 1; i < argc; i++){
    pid = fork();
    if(pid < 0){
      printf(1, "schedtest: fork failed\n");
      break;
    }
    if(pid == 0){
      n = atoi(argv[i]);
      if(settickets(n) < 0){
        printf(1, "schedtest: settickets(%d) failed\n", n);
        exit();
      }
      printf(1, "child pid %d tickets %d\n", getpid(), n);
      for(;;)          // never return to the fork loop
        x++;
    }
  }
  exit();
}
