#ifdef CS333_P2
#include "types.h"
#include "user.h"
#include "uproc.h"

static void
printTime(int ticks){
  printf(1, "%d.%d%d%d\t", (ticks / 1000), (ticks % 1000) / 100, (ticks % 100) / 10, (ticks % 10) / 1);
}

int
main(void)
{
  int max = 16, procs = 0;
  struct uproc* table = malloc(max * sizeof(struct uproc));

  if(!table){
    printf(2, "Malloc failed for process table allocation\n");
    exit();
  }

  procs = getprocs(max, table);

  if(procs > 0){
    printf(1, "PID\tName\tUID\tGID\tPPID\tElapsed\tCPU\tState\tSize\n");
    
    for(int i = 0; i < procs; ++i, table++){
      printf(1, "%d\t", table->pid);  
      printf(1, "%s\t", table->name);  
      printf(1, "%d\t", table->uid);  
      printf(1, "%d\t", table->gid);  
      printf(1, "%d\t", table->ppid);
      printTime(table->elapsed_ticks);
      printTime(table->CPU_total_ticks);
      printf(1, "%s\t", table->state);
      printf(1, "%d\t\n", table->size);
    }

    free(table);
  }
  else{
    printf(2, "Error: getprocs did not work correctly.\n");
  }
  exit();
}
#endif
