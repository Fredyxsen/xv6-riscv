## TAREA 4 Diego Marin

En este trabajo, se implementaron las funciones del sistema operativo `chmod` en el sistema **xv6**. Esta funcionalidad permite modificar los permisos de acceso a un archivo o directorio, lo cual es crucial para garantizar la seguridad del sistema.

## Modificación de permisos e implementación de la llamada de sistema `chmod()`

1. **Modificar `syscall.h`:**
   * **Agregar definición:** En este archivo se definió el identificador de la nueva llamada al sistema `chmod`:
     ```c
     #define SYS_chmod 22
     ```

2. **Modificar `user.h`:**
   * **Declaración externa:** Se agregó la declaración de `chmod` para permitir que los programas de usuario puedan utilizar esta llamada al sistema.
     ```c
     int chmod(const char*, int);
     ```

3. **Modificar `syscall.c`:**
   * **Referenciar la función:** Se añadió una entrada para `sys_chmod` en la tabla de llamadas al sistema.
     ```c
     extern uint64 sys_chmod(void);
     [SYS_chmod] sys_chmod,
     ```

4. **Modificar `sysfile.c`:** 
   * **Implementación:** Se añadió la función `sys_chmod`, que aplica la lógica para cambiar los permisos de un archivo.
     ```c
     uint64 sys_chmod(void) {
         char path[MAXPATH];
         int mode;
         struct inode *ip;

         if (argint(1, &mode) < 0 || argstr(0, path, MAXPATH) < 0)
             return -1;

         begin_op();
         if ((ip = namei(path)) == 0) {
             end_op();
             return -1;
         }

         ilock(ip);
         if (ip->perm == 5) {  // Si es inmutable
             iunlockput(ip);
             end_op();
             return -1;
         }

         ip->perm = mode;
         iupdate(ip);
         iunlockput(ip);
         end_op();

         return 0;
     }
     ```

5. **Modificar `usys.pl`:**
   * **Entrada en la tabla:** Este archivo genera el código necesario para que los programas de usuario invoquen la llamada al sistema.
     ```c
     entry("chmod");
     ```

6. **Modificar `Makefile`:**
   * **Incluir pruebas:** Se añadió el archivo de pruebas a la lista de programas del usuario.
     ```c
     $U/_test\
     ```

7. **Modificar `file.h`:**
   * **Añadir el campo `perm`:** Se agregó un campo en la estructura `inode` para almacenar los permisos.
     ```c
     int perm;  // Permisos del archivo
     ```

8. **Modificar `fs.h`:**
   * **Persistencia de permisos:** Se añadió un campo `perm` en la estructura del disco para que los permisos sean almacenados.
     ```c
     int perm;  // Permisos del inodo
     ```

---

## Pruebas Realizadas

1. **Objetivo:** Verificar que la syscall `chmod` funcione correctamente cambiando los permisos de archivos.
2. **Método:** Se creó un archivo de prueba (`test.c`) que realiza lo siguiente:
   - Crear un archivo con permisos iniciales de lectura/escritura.
   - Cambiar los permisos a solo lectura, lectura/escritura, e inmutable.
   - Validar los comportamientos esperados:
     - Archivos inmutables no pueden ser modificados.
     - Archivos con permisos de solo lectura no pueden abrirse en modo escritura.
3. **Código de prueba:**
   ```c
   print_result(chmod(filename, 1), "Cambiar permisos a solo lectura (1)");
   print_result(chmod(filename, 3), "Cambiar permisos a lectura y escritura (3)");
   print_result(chmod(filename, 5), "Cambiar permisos a inmutable (5)");
