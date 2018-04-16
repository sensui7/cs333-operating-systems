#ifdef CS333_P2
#include "types.h"
#include "user.h"

// OSTEP has an example of using fork() & exec()
// fork() Creates a process
// exec(filename, **argv) Load a file and execute it
// pg. 9 of xv6-book-rev8.pdf

static void
printTime(int ticks){
  printf(1, "ran in %d.%d%d%d seconds\n", (ticks / 1000), (ticks % 1000) / 100, (ticks % 100) / 10, (ticks % 10) / 1);
}

// using fork() and exec() allows for a "recursive" strategy
// to print out one or more commands with time
// e.g. time time echo "abc" -> time echo "abc" -> echo "abc"
// "abc"
// ran in ... seconds
// ran in ... seconds

int
main(int argc, char **argv)
{
  /*
  if (argc < 2){
    printf(1, "(null) ran in 0.000 seconds\n");
    exit();
  }
  */

  // use the uptime() system call to 
  // access global kernel variable "ticks"
  uint start = uptime(), end = 0, delta = 0;
  int rc = fork();
 
  // fork failure, so exit
  if (rc < 0){
    printf(1, "fork failed\n");
    exit();
  }
  // it's the child, pid is 0
  else if(rc == 0){
    exec(argv[1], &argv[1]);
    //printf(1, "ran in 0.000 seconds\n");
    //printf(1, "Error: invalid command or command doesn't exist\n");
  }
  else{
    wait(); // parent waits for the child
    end = uptime();
    delta = end - start;

    // print time in seconds, accurate to the milliseconds
    printTime(delta);
  }

  exit();
}
#endif
