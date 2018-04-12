#ifdef CS333_P2
#include "types.h"
#include "user.h"
#include "uproc.h"

static void
printTime(int ticks){
  int firstDigit = ticks / 1000;
  int decDigits = ticks - (firstDigit * 1000);

  if(decDigits < 100 && decDigits >= 10){ 
      printf(1, "%d.0%d\t", ticks / 1000, decDigits);
  }
  else if(decDigits < 10){ 
      printf(1, "%d.00%d\t", ticks / 1000, decDigits);
  }
  else{ 
      printf(1, "%d.%d\t", ticks / 1000, decDigits);
  }
}

int
main(void)
{
  int max = 4, procs = 0;
  struct uproc* table = malloc(max * sizeof(struct uproc));
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
