#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int
main(int argc, char *argv[])
{   int ppid = getppid();
    printf("PPid: %d\n", ppid);
    exit(1);
}git