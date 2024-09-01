## TAREA I Diego Marin: Implementación de Llamada al Sistema `getppid()` y `getancestor()`

**Objetivo:**
Agregar una nueva llamada al sistema, `getppid()`, para permitir que los procesos obtengan el PID (Process ID) de su proceso padre.

**Pasos a Seguir:**

1. **Modificar `syscall.h`:**
   * **Agregar definición:**
     ```c
     #define SYS_getppid 22
     ```

2. **Modificar `syscall.c`:**
   * **Declaración externa:**
     ```c
     extern uint64 sys_getppid(void);
     ```
   * **Agregar a la tabla de despacho:**
     ```c
     [SYS_getppid] sys_getppid,
     ```

3. **Modificar `sysproc.c`:**
   * **Implementar la función:**
     ```c
     uint64
     sys_getppid(void)
     {
         struct proc *p = myproc();
         return p->parent ? p->parent->pid : 0;
     }
     ```

4. **Modificar `user.h`:**
   * **Declaración para el espacio de usuario:**
     ```c
     int getppid(void);
     ```

5. **Modificar `usys.pl`:**
   * **Agregar a la tabla de generación de código:**
     ```perl
     print OUT <<EOF;
     SYS_getppid,
     EOF
     ```

6. **Modificar `yosoytupadre.c`:**
   * **Ejemplo de uso:**
     ```c
     int ppid = getppid();
     printf("El ProcessID del proceso padre es: %d\n", ppid);
     ```

7. **Modificar `Makefile`:**
   * **Actualizar reglas:** Ajustar las reglas de compilación para incluir los nuevos archivos y dependencias.

