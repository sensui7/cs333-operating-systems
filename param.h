#define NPROC        64  // maximum number of processes
#define KSTACKSIZE 4096  // size of per-process kernel stack
#define NCPU          8  // maximum number of CPUs
#define NOFILE       16  // open files per process
#define NFILE       100  // open files per system
#define NINODE       50  // maximum number of active i-nodes
#define NDEV         10  // maximum major device number
#define ROOTDEV       1  // device number of file system root disk
#define MAXARG       32  // max exec arguments
#define MAXOPBLOCKS  10  // max # of blocks any FS op writes
#define LOGSIZE      (MAXOPBLOCKS*3)  // max data blocks in on-disk log
#define NBUF         (MAXOPBLOCKS*3)  // size of disk block cache
// #define FSSIZE       1000  // size of file system in blocks
#define FSSIZE       2000  // size of file system in blocks  // CS333 requires a larger FS.
#define DEF_UID       0   // default uid for the first process
#define DEF_GID       0   // default gid for the first process
#define MAXPRIO       7   // maximum number of priority queues for MLFQ
#define TICKS_TO_PROMOTE     680   // number of ticks for priority promotion
#define BUDGET        360   // number of ticks a process can use in the CPU before demotion
// DEFAULT_UID is the default value for (both the first process and) files
// created by the mkfs when the file system is created
#define DEFAULT_UID   0
// DEFAULT_GID is the default value for (both the first process and) files
// created by the mkfs when the file system is created
#define DEFAULT_GID   0
// DEFAULT MODE is the default value for the mode, which is interpreted
// as a 12-bit binary vector
#define DEFAULT_MODE  0755
