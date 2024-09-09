## TAREA I Diego Marin: Implementación de Llamada al Sistema `getppid()` y `getancestor()`
El objetivo es agregar una nueva llamada al sistema, `getppid()`, que permita a los procesos obtener el PID (Process ID) de su proceso padre.

## Pasos a Seguir:

1. **Modificar `syscall.h`:**
   * **Agregar definición:** En este archivo se deben definir los números únicos asociados a las llamadas al sistema. Agregamos la definición de la nueva llamada `getppid`:
     ```c
     #define SYS_getppid 22
     ```

2. **Modificar `syscall.c`:** 
   * **Declaración externa:** Añadimos una referencia a la función `sys_getppid()` que se implementará.
     ```c
     extern uint64 sys_getppid(void);
     ```
   * **Agregar a la tabla de despacho:** Asociamos el número de la syscall con la función que la implementa, añadiendo la llamada a la tabla de funciones:
     ```c
     [SYS_getppid] sys_getppid,
     ```

3. **Modificar `sysproc.c`:** 
   * **Implementar la función:** Aquí se define la lógica de la nueva llamada al sistema. En este caso, obtenemos el proceso actual y devolvemos el PID de su proceso padre:
     ```c
     uint64
     sys_getppid(void)
     {
         struct proc *p = myproc();
         return p->parent ? p->parent->pid : 0;
     }
     ```

4. **Modificar `user.h`:**
   * **Declaración para el espacio de usuario:** Para que los programas de usuario puedan usar la syscall, agregamos una declaración en el archivo `user.h`:
     ```c
     int getppid(void);
     ```

5. **Modificar `usys.pl`:**
   * **Agregar a la tabla de generación de código:** Este script genera el código necesario para que los programas de usuario invoquen la syscall. Añadimos la entrada correspondiente para `getppid()`:
     ```c
     entry("getppid");
     ```

6. **Modificar `yosoytupadre.c`:**
   * **Ejemplo de uso:** Creamos un archivo de prueba llamado `yosoytupadre.c` para verificar la correcta implementación de la nueva llamada al sistema. En este archivo, el proceso obtiene y muestra el PID de su proceso padre:
     ```c
     int ppid = getppid();
     printf("El ID de proceso del proceso padre es: %d\n", ppid);
     ```

7. **Modificar `Makefile`:**
   * **Actualizar reglas:** Asegurarse de que los archivos nuevos o modificados sean compilados correctamente.
    ```c
    $U/_yosoytupadre\
    ```
## Ahora añadimos : `getancestor()`

## Pasos a Seguir:

1. **Modificar `syscall.h`:**
   * **Agregar definición:** En este archivo se deben definir los números únicos asociados a las llamadas al sistema. Agregamos la definición de la nueva llamada `getancestor()`:
     ```c
     #define SYS_getancestor() 23
     ```
2. **Modificar `syscall.c`:** 
   * **Declaración externa:** Al igual que con la otra llamada añadimos una referencia a la función `getancestor()` que se implementará.
     ```c
     extern uint64 sys_getancestor(void);
     ```
   * **Agregar a la tabla de despacho:** Asociamos el número de la syscall con la función que la implementa, añadiendo la llamada a la tabla de funciones:
     ```c
     [SYS_getancestor] sys_getancestor,
     ```
3. **Modificar `sysproc.c`:** 
   * **Implementar la función:** Aquí se define la lógica de la nueva llamada al sistema. En este caso, retorna el ancestro indicado en el parámetro y devuelve -1 si ya no hay mas ancestros:
     ```c
             uint64
        sys_getancestor(void)
        {
          int n;
          argint(0, &n);
          if(n < 0)
            return -1;
        
          struct proc *p = myproc();
          for(int i = 0; i < n; i++){
            if(p->parent)
              p = p->parent;
            else
              return -1; // No hay más ancestros
          }
          return p->pid;
        }
     ```
4. **Modificar `user.h`:**
   * **Declaración para el espacio de usuario:** Para que los programas de usuario puedan usar la syscall, agregamos una declaración en el archivo `user.h`:
     ```c
     int getancestor(int);
     ```
5. **Modificar `usys.pl`:**
   * **Agregar a la tabla de generación de código:** Este script genera el código necesario para que los programas de usuario invoquen la syscall. Añadimos la entrada correspondiente para `getppid()`:
     ```c
     entry("getancestor");
     ```
6. **Modificar `yosoytupadre.c`:**
   * **Ejemplo de uso:** Complementamos el archivo de prueba llamado `yosoytupadre.c` para verificar la correcta implementación de la nueva llamada al sistema:
     ```c
     int n = 2; // Valor indicado según el ancestro que se quiera ver
     int ancestor_pid = getancestor(n);
     if (ancestor_pid != -1)
         printf("El ID de proceso del ancestro numero %d es: %d\n", n, ancestor_pid);
     else
         printf("No se encontró un ancestro en el nivel %d.\n", n);

     exit(0);
     ```
