#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main() {
    // Obtenemos el PID del proceso padre
    int proceso_padre = getppid();
    printf("El ID del proceso padre es: %d\n", proceso_padre);

    // Buscamos el ancestro en el segundo nivel
    int nivel_ancestro = 2;
    int id_ancestro = encontrar_ancestro(nivel_ancestro);

    // Imprimimos el resultado
    if (id_ancestro != -1) {
        printf("El ancestro en el nivel %d es: %d\n", nivel_ancestro, id_ancestro);
    } else {
        printf("No se encontró un ancestro en el nivel %d.\n", nivel_ancestro);
    }

    return 0;  // Equivalente a exit(0)
}