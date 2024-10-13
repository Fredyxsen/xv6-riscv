# Tarea 2 Diego Marín

## Desarrollo de la Tarea 2

### Modificación de la estructura del proceso

1. **Modificaciones al archivo `proc.h`:**

    Se añadieron las líneas `int priority;`, la cual sera la encargada de almacenar la prioridad de cada proceso y `int boost;`, el cual nos servira para implementar el campo de boost. Todo esto se añade en la estructura `struct proc`:

    ```c
    struct proc {
      // ... otros campos ...
      int priority;
      int boost;
    };
    ```

### Inicializar la prioridad y agregar el campo boost

1. **Modificaciones al archivo `proc.c`:**

    En este archivo se encuentra la función allocproc(), que se encarga de crear e inicializar nuevas estructuras de proceso. Para que cada proceso tenga una prioridad inicial, debemos modificar esta función para asignar un valor al campo priority de la nueva estructura de proceso.
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

    Se implementó la lógica de ajuste de prioridad dentro de la función `scheduler()` ya que esta parte del codigo se encarga de decidir que proceso ejecutar en cada momento. Es por esto que lo modificamos para implementar la logica de las prioridades y de este modo se tenga en consideracion el campo `priority`(añadido en el `proc.h`) al seleccionar el siguiente proceso a ejecutar. Añadimos por ultimo las condiciones solicitadas, como por ejemplo si  la prioridad alcanza 9, cambiar el boost a -1 o si la prioridad llega a 0, cambiar el boost a 1.

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
    fork_processes(int n) // Define una función llamada fork_processes que recibe un entero n como argumento
    {
      for (int i = 0; i < n; i++) { // Inicia un bucle for que se ejecuta n veces.
        int pid = fork(); // Crea un nuevo proceso hijo usando la llamada al sistema fork().
        if (pid == 0) { // Si pid es 0, significa que este es el proceso hijo.
          sleep(i * 10);
          printf("Ejecutando proceso %d con pid %d\n", i + 1, getpid()); // Imprime el número de proceso y su PID.
          sleep(10);
          exit(0);
        }
      }

      // Esperar a que todos los hijos finalicen
      for (int i = 0; i < n; i++) {
        wait(0); // Espera a que cualquier hijo termine.  El argumento 0 indica que no se necesita información de estado del hijo
      }
    }

    int
    main()
    {
      printf("Inicializando prueba de prioridades...\n"); // Imprime un mensaje indicando el inicio de la prueba.
      fork_processes(20); // Llama a la función fork_processes para crear 20 procesos hijos.
      exit(0); // Termina el proceso principal.
    }
    ```

### Pruebas de la función

1. **Ejecución del programa de prueba `testpriority`:**
    * **Compilamos XV6 en el branch de la tarea 2, ademas de usar el comando `ls` para ver si la llamada del sistema esta disponible y fue ingresada correctamente :**
    ![Captura de pantalla (108)](https://github.com/Fredyxsen/xv6-riscvz/blob/Diego_Marin_T2/Captura%20de%20pantalla%20(108).png)
    * **Ejecutamos la llamada de sistema `testpriority`:**
    ![Captura de pantalla (109)](https://github.com/Fredyxsen/xv6-riscvz/blob/Diego_Marin_T2/Captura%20de%20pantalla%20(109).png)
    ![Captura de pantalla (110)](https://github.com/Fredyxsen/xv6-riscvz/blob/Diego_Marin_T2/Captura%20de%20pantalla%20(110).png)

    Como se puede apreciar, todo funciona correctamente y el output es el esperado.
    
    
    
## Conclusiones y problemas

* Esta tarea fue bastante desafiante ya que fue necesario en su momento comprender bien lo que se hizo en la tarea numero 1 para poder seguir avanzando en esta misma, ya que como podemos ver se ocupan las `llamadas al sistema` y la modificacion de archivos como fue en el caso del `proc`, tanto `proc.h` como `proc.c`.
Por lo que uno de los grandes problemas que destacaré, fue el retomar y reintegrarse a este tema del xv6, ya que al hacer una tarea luego por la falta de practica se me olvidan los temas que he aprendido y tengo que volver a repasarlos nuevamente y eso quita bastante tiempo y es poco eficiente, pero una vez retomado todo este tema fue bastante fluido el desarrollo y todo los problemas presentados durante la tarea fueron temas sencillos que se me fueron por la falta de practica como dije anteriormente.
