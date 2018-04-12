#ifdef CS333_P2 

#include "types.h"
#include "user.h"

int
main(int argc, char **argv){
  uint uid, gid, ppid;
  int errCode = 0;

  // Testing if getting the IDs work
  printf(1, "PROCESS INFO\n");

  uid = getuid();
  printf(1,"User ID of process: %d\n", uid);

  gid = getgid();
  printf(1, "Group ID of process: %d\n", gid);

  ppid = getppid();
  printf(1, "Parent process ID of process: %d\n\n", ppid);

  printf(1, "TEST FOR SETTING UID/GID BOUNDS\n");

  // Testing if setting the IDs work (bounds etc.)

  errCode = setuid(-1);
  if (errCode == -1) 
    printf(1, "UID set to negative value -> rejected -> [SUCCESS]\n");
  else
    printf(1, "UID set to negative value -> accepted -> [FAILURE]\n");
  uid = getuid();
  printf(1,"User ID of process: %d\n", uid);

  errCode = setuid(32768);
  if (errCode == -1) 
    printf(1, "UID set to greater value than 32768 -> rejected -> [SUCCESS]\n");
  else
    printf(1, "UID set to greater value than 32768 -> accepted -> [FAILURE]\n");
  uid = getuid();
  printf(1,"User ID of process: %d\n", uid);

  errCode = setgid(-1);
  if (errCode == -1) 
    printf(1, "GID set to negative value -> rejected -> [SUCCESS]\n");
  else
    printf(1, "GID set to negative value -> accepted -> [FAILURE]\n");
  gid = getgid();
  printf(1,"Group ID of process: %d\n", gid);

  errCode = setgid(32768);
  if (errCode == -1) 
    printf(1, "GID set to greater value than 32768 -> rejected -> [SUCCESS]\n");
  else
    printf(1, "GID set to greater value than 32768 -> accepted -> [FAILURE]\n");
  gid = getgid();
  printf(1,"Group ID of process: %d\n", gid);

  exit();
}

#endif
