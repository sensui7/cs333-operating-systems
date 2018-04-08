#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "uproc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      return -1;
    }
    sleep(&ticks, (struct spinlock *)0);
  }
  return 0;
}

// return how many clock tick interrupts have occurred
// since start. 
int
sys_uptime(void){
  uint xticks;
  
  xticks = ticks;
  return xticks;
}

// Turn off the computer
int
sys_halt(void){
  cprintf("Shutting down ...\n");
  outw( 0x604, 0x0 | 0x2000);
  return 0;
}

// show current date
#ifdef CS333_P1
int
sys_date(void){
  struct rtcdate *d;
  
  if(argptr(0, (void*)&d, sizeof(struct rtcdate)) < 0)
    return -1;

  cmostime(d);
  return 0;
}
#endif

#ifdef CS333_P2
uint
sys_getgid(void){
  return proc -> gid;
}

uint
sys_getppid(void){
  // return pid of 1 if it's the first process
  if(proc->pid == 1)
  {
    return 1;
  }

  // return the parent process if otherwise
  return proc -> parent -> pid;
}

uint
sys_getuid(void){
  return proc -> uid;
}

// for setgid & setuid, need to use argint to verify that
// the pointer by the user is a pointer of the user part
// of the addy space
// argint fetches the n'th 32-bit system call argument
// fetchint writes addy value from user memory to *ip
// fetchint returns if the address is valid in the user space

int 
sys_setgid(void){
  int gid;
  int verifyGIDAddy = argint(0, &gid);
 
  // check if pointer by user is correct part of its addy space 
  if(verifyGIDAddy == -1){
    return -1;
  }

  // update the gid if it's valid
  if(gid > 0 && gid < 32767){
    proc -> gid = gid;
    return 0;
  }

  return -1;
}

int
sys_setuid(void){
  int uid;
  int verifyUIDAddy = argint(0, &uid);

  // check if pointer by user is correct part of its addy space 
  if(verifyUIDAddy == -1){
    return -1;
  }

  // update the gid if it's valid
  if(uid > 0 && uid < 32767){
    proc -> uid = uid;
    return 0;
  }

  return -1;
}

int
sys_getprocs(void){
  int max;
  struct uproc * table;
  int verifyMaxAddy = argint(0, &max);
  int verifyTableAddy = argptr(1, (void*) &table, sizeof(*table));

  if(verifyMaxAddy < 0 || verifyTableAddy < 0){
    return -1;
  }
 
  return getprocs(max, table); 
}

#endif
