// store: print a snapshot of every process using getpinfo().
// Run it twice; Delta = Ticks in snapshot 2 - Ticks in snapshot 1.
#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

struct pstat st;

int
main(int argc, char *argv[])
{
  int i;

  if(getpinfo(&st) < 0){
    printf(2, "store: getpinfo failed\n");
    exit();
  }
  printf(1, "time %d\n", uptime());
  printf(1, "PID  Size   Ticks  Tickets  Stride  Pass\n");
  for(i = 0; i < NPROC; i++){
    if(!st.inuse[i])
      continue;
    printf(1, "%d    %d  %d    %d       %d    %d\n", st.pid[i], st.size[i],
           st.ticks[i], st.tickets[i], st.stride[i], st.pass[i]);
  }
  exit();
}
