#ifdef CS333_P2

#include "types.h"
#include "user.h"

static void
testNumProcs(int processes){
  int i, rc, actual = processes;

  switch(actual){
    case 1:
      actual = 3;
      break;
    case 14:
      actual = 16;
      break;
    case 62:
      actual = 64;
      break;
    case 72:
      actual = 72;
  }

  printf(1, "RUNNING TEST WITH %d PROCESSES\n", actual);

  for(i = 0; i < processes; ++i){
    if((rc = fork()) == 0){
      char * myargs[1];
      myargs[0] = "sh";
      exec(myargs[0], &myargs[0]);
    }
  }

}

int
main(int argc, char **argv){
  //testNumProcs(1);
  //testNumProcs(14);
  //testNumProcs(62);
  testNumProcs(72);
  exit();
}
#endif
