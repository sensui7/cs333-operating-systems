#include "syscall.h"
#include "traps.h"

#define SYSCALL(name) \
  .globl name; \
  name: \
    movl $SYS_ ## name, %eax; \
    int $T_SYSCALL; \
    ret

SYSCALL(fork)
SYSCALL(exit)
SYSCALL(wait)
SYSCALL(pipe)
SYSCALL(read)
SYSCALL(write)
SYSCALL(close)
SYSCALL(kill)
SYSCALL(exec)
SYSCALL(open)
SYSCALL(mknod)
SYSCALL(unlink)
SYSCALL(fstat)
SYSCALL(link)
SYSCALL(mkdir)
SYSCALL(chdir)
SYSCALL(dup)
SYSCALL(getpid)
SYSCALL(sbrk)
SYSCALL(sleep)
SYSCALL(uptime)
SYSCALL(halt)
// Project 1: user-side stub for system call (macro)
SYSCALL(date)
// Project 2: user-side stub for system calls
SYSCALL(getgid)
SYSCALL(getppid)
SYSCALL(getuid)
SYSCALL(setgid)
SYSCALL(setuid)
SYSCALL(getprocs)
// Project 4: user-side stub for system call
SYSCALL(setpriority)
// Project 5: user-side stub for system calls
SYSCALL(chmod)
SYSCALL(chown)
SYSCALL(chgrp)
