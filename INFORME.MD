# Tarea 2 Diego Marin

## Desarrollo de la Tarea 2

### Modificación de la estructura del proceso

1. **Modificaciones al archivo llamado `proc.h`**:

    - Se añadieron las lineas *int priority* y  *int boost* en la parte de la linea de codigo `struct proc{}` tal que asi:
      ```c
      int priority;
      int boost;
      ```


### Inicializar la prioridad de cada proceso en 0 y agregar un campo de boost a la estructura de proceso.

1. **Modificaciones al archivo llamado `proc.c`**:
    
    - Añadimos la prioridad de cada proceso en 0 y agregamos el campo de boost = 1 dentro de la linea de codigo `allocproc(void)`:
      ```c
      p->priority = 0;
      p->boost = 1;
      ```


### Implementacion de la lógica: Prioridad += Boost.

1. **Modificaciones a archivo `proc.c`**:
    
    - Se añadieron las siguientes líneas dentro de `scheduler(void)`, específicamente al principio de `if(p->state == RUNNABLE){}`:
      ```c
      // Implementamos la lógica solicitada: Prioridad += Boost.
      p->priority += p->boost;

      // Luego, si la prioridad alcanza 9, cambiar boost a -1
      if(p->priority >= 9) {
        p->boost = -1;
      }

      // y por ultimo, si la prioridad alcanza 0, cambiar boost a 1
      if(p->priority <= 0) {
        p->boost = 1;
      }

      ```


### Creamos el programa de prueba `testpriority.c`

1. **Creación archivo de prueba `testpriority.c`**:
    
    - Primero que todo, se crea el programa `testpriority.c` dentro de `user`.

2. **Incorporación a `Makefile`**:

    - Añadimos la linea `$U/_testpriority\` al final de la sección `UPROGS` del Makefile, de este modo se incluye el programa en la compilacion de `xv6`.

3. **Creando la funcion en el archivo de prueba `testpriority.c`**:

    - La función que se codificó dentro del archivo es la siguiente:
      ```c
        #include "kernel/types.h"
        #include "user/user.h"

        void
        fork_processes(int n)
         
        {
        for(int i = 0; i < n; i++) {// Inicia un bucle for que se ejecuta n veces.
            int pid = fork(); // Crea un nuevo proceso hijo usando la llamada al sistema fork().
            if(pid == 0) {
            sleep(i * 10);
            printf("Ejecutando proceso %d con pid %d\n", i + 1, getpid()); // Imprime el número de proceso y su PID.
            sleep(10);
            exit(0);
            }
        }

        // Se espera a que todos los hijos finalicen
        for(int i = 0; i < n; i++) {
            wait(0);
        }
        }

        int
        main()
        {
        printf("Inicializando prueba de prioridades...\n");// Imprime un mensaje indicando el inicio de la prueba.
        fork_processes(20); // Llama a la función fork_processes para crear 20 procesos hijos.
        exit(0); // Termina el proceso principal.
        }

    ```


### Pruebas de la funcion

1. **Ejecución del programa de prueba `testpriority`**:


## Conclusiones y problemas
