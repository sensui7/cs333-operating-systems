#ifdef CS333_P5
#include "types.h"
#include "user.h"

int
main(int argc, char ** argv)
{
  if(argc != 3){
    printf(1, "Usage: chown <OWNER> <TARGET>\n");
    exit(); 
  }

  char *pathname = argv[2];
  int owner = atoi(argv[1]);
  int rc = chown(pathname, owner);

  switch(rc){
    case -1:
      printf(2, "Error: invalid pathname\n");
      exit();
    case -2:
      printf(2, "argint() failed to verify owner's address\n");
      exit();
    case -3:
      printf(2, "UID is not within inclusive range of 0 to 32767\n");
      exit();
  }

  exit();
}

#endif
