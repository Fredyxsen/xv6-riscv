## TAREA 4 Diego Marin

En este trabajo, se implementaron las funciones del sistema operativo `chmod` en el sistema **xv6**. Esta funcionalidad permite modificar los permisos de acceso a un archivo o directorio, lo cual es crucial para garantizar la seguridad del sistema.

## ¿Qué es `chmod` y por qué es importante?

`chmod` (change mode) es un comando utilizado para cambiar los permisos de acceso de un archivo o directorio. Estos permisos definen quién puede leer, escribir o ejecutar un archivo. En sistemas operativos como Unix y sus derivados, `chmod` es fundamental para:

1. **Controlar el acceso:** Permite restringir o habilitar el acceso a ciertos usuarios, asegurando que los archivos sensibles no puedan ser manipulados sin autorización.
2. **Proteger la integridad de los datos:** Archivos importantes pueden configurarse como inmutables para prevenir modificaciones accidentales o malintencionadas.
3. **Fomentar la colaboración segura:** Permite gestionar permisos específicos para usuarios o grupos, facilitando el trabajo colaborativo sin comprometer la seguridad.

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
   #include "kernel/types.h"
    #include "kernel/stat.h"
    #include "user/user.h"
    #include "kernel/fs.h"
    #include "kernel/fcntl.h"
    
    void print_result(int result, char *message) {
      if (result < 0) {
        printf("Error: %s\n", message);
      } else {
        printf("Success: %s\n", message);
      }
    }
    
    int main() {
      char *filename = "testfile.txt";
      int fd;
    
      //Creamos un archivo con los permisos para poder hacer lectura y escritura.
      fd = open(filename, O_CREATE | O_RDWR);
      
      if (fd < 0) {
        printf("Error: no se pudo crear el archivo.\n");
        exit(1);
      }
      printf("Archivo %s creado con éxito.\n", filename);
    
      // Escribir en el archivo.
      if (write(fd, "Chocolate", 11) != 11) {
        printf("Error: no se pudo escribir en el archivo.\n");
        exit(1);
      }
      printf("Se escribió en el archivo.\n");
    
      close(fd);
    
      //Cambiar los permisos a solo modo de lectura.
      print_result(chmod(filename, 1), "Cambiar permisos a solo lectura (1)");
    
      fd = open(filename, O_WRONLY);
      if (fd >= 0) {
        printf("Error: Archivo abierto en modo escritura con permisos de solo lectura.\n");
        close(fd);
        exit(1);
      } else {
        printf("Archivo no se pudo abrir en modo escritura.\n");
      }
    
      // Paso 3: Cambiar los permisos a lectura y tambien escritura.
      print_result(chmod(filename, 3), "Cambiar permisos a lectura y escritura (3)");
    
      fd = open(filename, O_RDWR);
      if (fd < 0) {
        printf("Error: No se pudo abrir el archivo en modo lectura y escritura.\n");
        exit(1);
      }
      if (write(fd, "Prueba final\n", 13) != 13) {
        printf("Error: No se pudo escribir en el archivo después de restaurar los permisos.\n");
        close(fd);
        exit(1);
      }
      printf("Se escribió en el archivo después de restaurar los permisos.\n");
      close(fd);
    
      // Paso 4: Cambiar permisos a inmutable
      print_result(chmod(filename, 5), "Cambiar permisos a inmutable (5)");
    
      fd = open(filename, O_WRONLY);
      if (fd >= 0) {
        printf("Error: Archivo abierto en modo escritura con permisos inmutables.\n");
        close(fd);
        exit(1);
      } else {
        printf("Archivo no se pudo abrir en modo escritura.\n");
      }
    
      // Intentar cambiar permisos de inmutable a lectura y escritura (debe fallar).
      int chmod_result = chmod(filename, 3);
      if (chmod_result == 0) {
        printf("Error: Se cambiaron los permisos de un archivo inmutable.\n");
        exit(1);
      } else {
        printf("Los permisos de un archivo inmutable no fue posible cambiarlos.\n");
      }
    
      printf("Todas las pruebas pasaron con éxito.\n");
      exit(0);
    }
    ```
**Capturas**:
   ![Captura de pantalla (187)](https://github.com/Fredyxsen/xv6-riscvz/blob/Diego_Marin_T4/images/Captura%20de%20pantalla%20(187).png)
   ![Captura de pantalla (188)](https://github.com/Fredyxsen/xv6-riscvz/blob/Diego_Marin_T4/images/Captura%20de%20pantalla%20(188).png)

## Conclusion y problemas:
La implementación de la syscall chmod en el sistema operativo xv6 representa un avance significativo en términos de funcionalidad y seguridad. Este cambio permite manejar permisos de acceso de manera más granular, lo que es esencial en cualquier sistema operativo moderno. Durante el desarrollo, logramos integrar de manera efectiva nuevos campos en las estructuras de inodos y ajustes en las llamadas al sistema para soportar esta funcionalidad.

Gracias a las pruebas realizadas, se validó que los permisos configurados, como solo lectura e inmutable, funcionan correctamente y cumplen con los objetivos planteados. Este trabajo destaca la importancia de controlar el acceso a los archivos para proteger la integridad de los datos y facilitar un entorno seguro para los usuarios.

En el proceso de implementacion no hubieron ningun tipo de dificultades y se pudo llevar a cabo la realizacion final de esta tarea.
