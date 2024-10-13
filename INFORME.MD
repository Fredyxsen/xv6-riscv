# Tarea 2: Implementación de Prioridades en xv6 - Diego Marín

## Desarrollo de la Tarea 2

### Modificación de la estructura del proceso

1. **Modificaciones al archivo `proc.h`:**

    Se añadieron las líneas `int priority;` y `int boost;` en la estructura `struct proc`:

    ```c
    struct proc {
      // ... otros campos ...
      int priority;
      int boost;
    };
    ```

### Inicializar la prioridad y agregar el campo boost

1. **Modificaciones al archivo `proc.c`:**

    Se inicializa la prioridad de cada proceso en 0 y se agrega el campo `boost = 1` dentro de la función `allocproc()`:

    ```c
    static struct proc*
    allocproc(void)
    {
      // ... otro código ...
      p->priority = 0;
      p->boost = 1;
      // ... otro código ...
    }
    ```

### Implementación de la lógica: Prioridad += Boost

1. **Modificaciones al archivo `proc.c`:**

    Se implementó la lógica de ajuste de prioridad dentro de la función `scheduler()`:

    ```c
    void
    scheduler(void)
    {
      // ... otro código ...
      p->priority += p->boost;

      // Ajustar boost según la prioridad
      if (p->priority >= 9) {
        p->boost = -1;
      } else if (p->priority <= 0) {
        p->boost = 1;
      }
      // ... otro código ...
    }
    ```

### Creación del programa de prueba `testpriority.c`

1. **Creación del archivo `testpriority.c`:**

    Se creó el programa `testpriority.c` dentro del directorio `user`.

2. **Incorporación a `Makefile`:**

    Se añadió la línea `$U/_testpriority\` al final de la sección `UPROGS` del `Makefile` para incluir el programa en la compilación de xv6.

3. **Implementación de la función en `testpriority.c`:**

    ```c
    #include "kernel/types.h"
    #include "user/user.h"

    void
    fork_processes(int n)
    {
      for (int i = 0; i < n; i++) {
        int pid = fork();
        if (pid == 0) {
          sleep(i * 10);
          printf("Ejecutando proceso %d con pid %d\n", i + 1, getpid());
          sleep(10);
          exit(0);
        }
      }

      // Esperar a que todos los hijos finalicen
      for (int i = 0; i < n; i++) {
        wait(0);
      }
    }

    int
    main()
    {
      printf("Inicializando prueba de prioridades...\n");
      fork_processes(20);
      exit(0);
    }
    ```

### Pruebas de la función

1. **Ejecución del programa de prueba `testpriority`:**
    * **Compilamos XV6 en el branch de la tarea 2, ademas de usar el comando `ls` para ver si la llamada del sistema esta disponible y fue ingresada correctamente :**
    ![Captura de pantalla (108)](https://github.com/Fredyxsen/xv6-riscvz/blob/Diego_Marin_T1/Captura%20de%20pantalla%20(108).png)

## Conclusiones y problemas

* hola
