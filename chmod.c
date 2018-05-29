#ifdef CS333_P5
#include "types.h"
#include "user.h"

// Validate user input for the mode
static int
checkIfOctal(int num)
{
  if(!num){
    return 0; // success value
  }
  else if(num < 0){ // Check if negative integer
    return -1;
  }

  int rem = 0;
  int badFlag = 0; // Check if there's more than 4 digits

  while(num != 0){
    rem = num % 10;
    num /= 10;
    if((rem > 7 && rem <= 9) || badFlag > 3){
      return -1; // Not an octal input!
    }
    ++badFlag;
  }

  return 0;
}

int
main(int argc, char **argv)
{
  if(argc != 3){
    printf(1, "Usage: chmod <MODE> <TARGET>\n");
    exit();
  }

  // Handle if the input is an octal number
  if(checkIfOctal(atoi(argv[1])) != 0){
    printf(2, "Error: MODE is not an OCTAL input OR has more than 4 digits\n");	
    exit();
  }

  char *pathname = argv[2]; // Target is pathname 
  int mode = atoo(argv[1]); // Convert octal "owner" input to decimal
  
  int rc = chmod(pathname, mode);

  switch(rc){
    case -1: // Pathname doesn't exist in the FS
      printf(2, "Error: invalid pathname\n");	
      exit();
    case -2: // Argument passing in went wrong
      printf(2, "argint() failed for verifying mode's address\n");	
      exit();
    case -3: // Octal input is too high
      printf(2, "Mode is not within inclusive octal bounds 0000 to 1777\n");	
      exit();
  }

  exit();
}

#endif
