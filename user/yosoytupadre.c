#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
    int ppid = getppid();
    printf("El ID de proceso del proceso padre es: %d\n", ppid);

    int n = 3; // Valor indicado según el ancestro que se quiera ver
    int ancestor_pid = getancestor(n);
    if (ancestor_pid != -1)
        printf("El ID de proceso del ancestro numero %d es: %d\n", n, ancestor_pid);
    else
        printf("No se encontró un ancestro en el nivel %d.\n", n);

    exit(0);
}
