## TAREA I Diego Marin: Implementación de Llamada al Sistema `getppid()` y `getancestor()`

**Objetivo:**
# Agregar la nueva llamada al sistema `getppid()` en xv6

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
   ` $U/_yosoytupadre\`

