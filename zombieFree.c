#ifdef CS333_P3P4
#include "types.h"
#include "user.h"

// Test if processes that are already in the ready list are scheduled
// before processes added afterwards 
void 
checkRoundRobin()
{
  int childTable[3], childNum = 0, temp = 0;
  int ppid = getpid();

  // Create 3 processes to test that scheduler
  // enforces round-robin scheduling
  while (childNum < 3){
    childTable[childNum] = fork();

    // Make scheduler alternate processes
    // between RUNNABLE and RUNNING
    if (ppid != getpid()){
	while (++temp < 99999999999999999);
    }

    ++childNum;
  }

  // After the alternations, kill and wait
  // the forked processes in the first original parent
  if (ppid == getpid())
  {
    sleep(3000);
    for (int i = 0; i < 3; ++i, sleep(3000)){
       kill(childTable[i]);
       wait();
     } 

    exit();
  }
}

// Test that the kill shell command causes
// a process to transition to ZOMBIE and then UNUSED states.
// Wait is then used to notify the parent process so that
// these children are deallocated, and transfers to UNUSED.
void
checkKillCommand()
{
  int totalChildren = 0;
  int childTable[62];
  int ppid = getpid();
  int temp = 0;

  while (totalChildren < 62){
    childTable[totalChildren] = fork();
    ++totalChildren;
    if(getpid() != ppid){
      while (++temp < 99999999999);
    }
  }

  if (getpid() == ppid){
    sleep(2000);
    printf(1, "Total # of children created: %d\n", totalChildren);
    for (int i = 0; i < totalChildren; ++i, sleep(10)){
      kill(childTable[i]);
      wait();
      printf(1, "(checkKillCommand) : %d has moved from zombie list to the unused list\n", i);
    }
    exit();
  }
}

// Test that the exit shell command causes
// a process to allow itself for termination, which
// moves it to the ZOMBIE list.
void
checkExitCommand()
{
  int totalChildren = 0;
  int ppid = getpid();
  int temp = 0;
  int waitRC = 0;

  while (totalChildren < 62){
    fork();
    ++totalChildren;
    if(getpid() != ppid){
      while (++temp < 99999999);
      exit();
    }
  }

  if (getpid() == ppid){
    sleep(2000);
    printf(1, "Total # of children created: %d\n", totalChildren);
    while ((waitRC = wait()) != -1){
      printf(1, "(checkExitCommand) : %d has moved from zombie list to the unused list\n", waitRC);
    }
    exit();
  }
}

// Test to see if sleep list
// is correctly updated when a process
// sleeps and is woken up.
void
checkSleeper()
{
  int temp = 0;
  sleep(5000);
  while (++temp < 99999999999999999);
  exit();
}

int
main(void)
{
  //checkSleeper();
  //checkRoundRobin();
  //checkKillCommand();
  checkExitCommand();
}
#endif
