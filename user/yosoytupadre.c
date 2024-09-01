#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    // Obtener el PID del proceso padre
    int pid_padre = getppid();
    printf("El PID del proceso padre es: %d\n", pid_padre);

    // Definir el nivel del ancestro a buscar
    int nivel_ancestro = 2;
    int pid_ancestro = encontrar_ancestro(nivel_ancestro);

    // Mostrar el resultado
    if (pid_ancestro != -1) {
        printf("El PID del ancestro en el nivel %d es: %d\n", nivel_ancestro, pid_ancestro);
    } else {
        printf("No se encontró un ancestro en el nivel %d.\n", nivel_ancestro);
    }

    return 0;  // Finaliza el programa correctamente
}
