#ifdef CS333_P3P4
#include "types.h"
#include "user.h"

// Test if sleeping processes get promoted
void
testSleepPromote()
{
  int i, rc;
  int ppid;

  ppid = getpid();

  for(i = 0; i < 5; i++){
    fork();

    if(getpid() != ppid){
      // Change the 2nd argument for different tests
      rc = setpriority(getpid(), 7);
      
      if(rc == -1){
        printf(1, "setpriority failed\n");
      }

      sleep(5000);
      exit();
    }
  }

  if(getpid() == ppid){
    while (wait() != -1);
  }
}

// Test if running processes get promoted
void
testRunPromote()
{
  int i, j, rc;
  int ppid;

  ppid = getpid();

  for(i = 0; i < 5; ++i){
    fork();

    if(getpid() != ppid){
      // Change priority, or else error will occur for tests
      rc = setpriority(getpid(), 6);

      if(rc == -1){
        printf(1, "setpriority failed\n");
      }

      for(j = 0; j < 9999999999; ++j);
      exit();
    }
  }

  if(getpid() == ppid){
    while (wait() != -1);
  }
}

// Test to see if demotion affects running processes
// Also, this test can simply create processes, so it
// doesn't have to be only for testing the demotion.
void
testRunProcs()
{
  int i, j;
  int ppid;

  ppid = getpid();

  for(i = 0; i < 5; ++i){
    fork();

    if(getpid() != ppid){
      for(j = 0; j < 9999999999; ++j);
      exit();
    }
  }

  if(getpid() == ppid){
    while (wait() != -1);
  }
}

// Test to see if processes correctly have their budgets reset
// upon calling setpriority().
void
testBudgetReset()
{
  int i, j;
  int ppid;

  ppid = getpid();

  for(i = 0; i < 5; ++i){
    fork();

    if(getpid() != ppid){
      for(j = 0; j < 99999999; ++j);
      // Change the 2nd argument based on the param define
      int rc = setpriority(getpid(), 0);
      if(rc == -1){
        printf(1, "setpriority() failed\n");
	exit();
      }
      else{
        printf(1, "setpriority success!\n");
	sleep(1000);
      }

      for(j = 0; j < 9999999999; ++j);
      exit();
    }
  }

  if(getpid() == ppid){
    while (wait() != -1);
  }
}

// Check to see if setpriority() keeps the
// queues intact.
void
testPriorityPosition()
{
  int i, j;
  int ppid;

  ppid = getpid();

  for(i = 0; i < 5; ++i){
    fork();

    if(getpid() != ppid){
      for(j = 0; j < 9999999999; ++j){
        if(j == 9999999){
          // Change the 2nd argument for different tests
          int rc = setpriority(getpid(), 1);
          if(rc == -1){
            printf(1, "setpriority() failed\n");
	    exit();
          }
          else{
            printf(1, "setpriority success!\n");
	    sleep(1000);
          }
        }
      }
      exit();
    }
  }

  if(getpid() == ppid){
    while (wait() != -1);
  }
}

// Bounds testing for the setpriority() system call
void
testPriorityErrors()
{
  int rc;
  int pid;

  pid = getpid();

  // Test bad bounds for setting priority of this process
  rc = setpriority(pid, -1);
  (rc == -1) ? printf(1, "PASS : -1 is not a valid priority")
	     : printf(1, "FAIL : -1 was accepted priority");

  printf(1, "\n");

  rc = setpriority(pid, 8);
  (rc == -1) ? printf(1, "PASS : 8 is not a valid priority")
	     : printf(1, "FAIL : 8 was accepted priority");

  printf(1, "\n");

  rc = setpriority(-1, 1);
  (rc == -1) ? printf(1, "PASS : -1 is not a valid PID")
	     : printf(1, "FAIL : -1 was accepted PID");
  
  printf(1, "\n");

  rc = setpriority(32768, 1);
  (rc == -1) ? printf(1, "PASS : 32768 is not a valid PID")
	     : printf(1, "FAIL : 32768 was accepted PID"); 

  printf(1, "\n");

}

int
main()
{

  //testSleepPromote();
  //testRunPromote();
  //testRunProcs();
  testBudgetReset();
  //testPriorityPosition();
  //testPriorityErrors();
  exit();
}
#endif
