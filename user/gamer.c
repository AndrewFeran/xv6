// gamer: attack the stride scheduler with a stream of newborns.
// 30 times: fork a child, then sleep(20). Each child spins for
// 100 ticks and exits. The parent then waits for every child.
#include "types.h"
#include "stat.h"
#include "user.h"

#define NCHILD 30

int
main(int argc, char *argv[])
{
  int i, pid, start, made;
  volatile int x = 0;

  printf(1, "gamer: parent pid %d\n", getpid());
  made = 0;
  for(i = 0; i < NCHILD; i++){
    pid = fork();
    if(pid < 0){
      printf(1, "gamer: fork failed\n");
      break;
    }
    if(pid == 0){
      start = uptime();
      while(uptime() - start < 100)   // spin for 100 ticks
        x++;
      exit();                         // never return to the fork loop
    }
    made++;
    sleep(20);
  }

  // reap every child so no zombies are left
  for(i = 0; i < made; i++)
    wait();
  printf(1, "gamer: done, %d children\n", made);
  exit();
}
