#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int getancestor(int n) {
    if (n < 0) {
        // Nivel de ancestro inválido
        return -1;
    }

    int pid = getpid();
    for (int i = 0; i < n; ++i) {
        pid = getppid();
        if (pid == 1) { // Si llegamos al proceso init, no hay más ancestros
            return -1;
        }
    }
    return pid;
}

int main(void) {
    int n = 2; // Valor según ancestro que se quiera obtener
    int ancestor_pid = getancestor(n);

    if (ancestor_pid != -1) {
        printf("El ProcessID del ancestro %d es: %d\n", n, ancestor_pid);
    } else {
        printf("No se encontró un ancestro en el nivel %d.\n", n);
    }

    exit(0);
}