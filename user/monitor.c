// monitor INTERVAL SAMPLES: every INTERVAL ticks, print one
// comma-separated line per in-use process (time,pid,tickets,ticks).
// The output pastes straight into Excel (Text to Columns, comma).
#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

struct pstat st;

int
main(int argc, char *argv[])
{
  int interval, samples, s, i, now;

  interval = 100;
  samples = 30;
  if(argc > 1)
    interval = atoi(argv[1]);
  if(argc > 2)
    samples = atoi(argv[2]);
  if(interval <= 0 || samples <= 0){
    printf(2, "usage: monitor interval samples\n");
    exit();
  }

  printf(1, "time,pid,tickets,ticks\n");
  for(s = 0; s < samples; s++){
    if(getpinfo(&st) < 0){
      printf(2, "monitor: getpinfo failed\n");
      exit();
    }
    now = uptime();
    for(i = 0; i < NPROC; i++){
      if(!st.inuse[i])
        continue;
      printf(1, "%d,%d,%d,%d\n", now, st.pid[i], st.tickets[i], st.ticks[i]);
    }
    if(s < samples - 1)
      sleep(interval);
  }
  exit();
}
