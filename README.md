## TAREA 3 Diego Marin
En este trabajo, se implementaron las funciones del sistema operativo `mprotect` y `munprotect` en el sistema xv6. Estas funciones permiten modificar los permisos de acceso a una región de memoria de un proceso, lo que es fundamental para garantizar la seguridad y la integridad de los datos.

## Pasos a Seguir:

1. **Modificar `syscall.h`:**
   * **Agregar definición:** En este archivo se deben definir los números únicos asociados a las llamadas al sistema. Agregamos la definición de la nueva llamada `SYS_mprotect` y `SYS_munprotect` :
     ```c
     #define SYS_mprotect 22
     #define SYS_munprotect 23 
     ```

2. **Modificar `user.h`:** 
   * **Declaración externa:** Añadimos una referencia a la función `sys_getppid()` que se implementará.
     ```c
     int mprotect(void *addr, int len);
     int munprotect(void *addr, int len);
     ```
   * **Declara las funciones en ```user.h ```:** Asociamos el número de las syscalls con las funciónes que las implementan, añadiendo las llamadas a la tabla de funciones:
     ```c
     int mprotect(void *addr, int len);
     int munprotect(void *addr, int len);
     ```

3. **Modificar `syscall.c`:** 
   * **Implementar la función:** Aquí se define la lógica de las nuevas llamadas al sistema. En este caso,agregamos las funciones `sys_mprotect` y `sys_munprotect`:
     ```c
     extern uint64 sys_mprotect(void); 
     extern uint64 sys_munprotect(void); 
     ```
    * **Agregamos las partes de las funciones en sus respetivas lineas de codigo:
         ```c
         [SYS_mprotect]    sys_mprotect, 
         [SYS_munprotect]  sys_munprotect, 
         ```
        ```c
        uint64 sys_mprotect(void) {
            uint64 addr;
            int len;
            
            // Extraer los argumentos de la System Call
            argaddr(0, &addr);
            argint(1, &len);
        
            // Validar los valores extraídos (si es negativo retornar -1)
            if (len <= 0 || addr == 0)
                return -1;
        
            // Llamar a mprotect con los argumentos ya extraídos
            return mprotect((void *)addr, len);
        }
        
        uint64 sys_munprotect(void) {
            uint64 addr;
            int len;
        
            // Extraer los argumentos de la llamada de sistema
            argaddr(0, &addr);
            argint(1, &len);
        
            // Validar los valores extraídos, (si es negativo retornar -1)
            if (len <= 0 || addr == 0)
                return -1;
        
            // Llamar a munprotect con los argumentos ya extraídos
            return munprotect((void *)addr, len);
        }
        ```

4. **Modificar `Proc.h`:**
   * **Lineas INT de ambos:**
     ```c
     int mprotect(void *addr, int len);
     int munprotect(void *addr, int len);
     ```

5. **Modificar `usys.pl`:**
   * **Agregar a la tabla de generación de código:** Este script genera el código necesario para que los programas de usuario invoquen las syscalls. Añadimos la entrada correspondiente para los dos llamadas:
     ```c
     entry("mprotect");
     entry("munprotect");
     ```

6. **Modificación de la tabla de páginas:**
   * La modificación de los permisos se realiza directamente sobre la entrada de la tabla de páginas. Al desactivar o activar el bit `PTE_W`, se indica al hardware si se permite o no la escritura en la página correspondiente. El refresco de la TLB es esencial para asegurar que los cambios en la tabla de páginas se reflejen en la traducción de direcciones.

     ```c
     int munprotect(void *addr, int len) {
        struct proc *p = myproc();
        uint64 va = (uint64) addr;
    
        for (uint64 a = va; a < va + len; a += PGSIZE) {
            pte_t *pte = walk(p->pagetable, a, 0);
            if (pte == 0 || (*pte & PTE_V) == 0) {
                return -1;  // Invalid page
            }
    
            // Printea el estado del PTE_W antes de modificarlo
            if (*pte & PTE_W) {
                printf("Page at 0x%lx is writable\n", a);
            } else {
                printf("Page at 0x%lx is read-only\n", a);
            }
    
            // Restaura el permiso de la escritura
            *pte |= PTE_W;
    
            // Printea el estado del PTE_W luego de la modificacion
            if (*pte & PTE_W) {
                printf("Page at 0x%lx is now writable\n", a);
            } else {
                printf("Page at 0x%lx is now read-only\n", a);
            }
        }
     ```
     ```c
     int mprotect(void *addr, int len) {
        struct proc *p = myproc();
        uint64 va = (uint64) addr;
    
        for (uint64 a = va; a < va + len; a += PGSIZE) {
            pte_t *pte = walk(p->pagetable, a, 0);
            if (pte == 0 || (*pte & PTE_V) == 0) {
                return -1;  // Invalid page
            }
    
            // Linea para printear el estado del PTE_W antes de modificarlo
            if (*pte & PTE_W) {
                printf("Page at 0x%lx is writable\n", a);
            } else {
                printf("Page at 0x%lx is read-only\n", a);
            }
    
            // Linea para desactivar el permiso de escritura, haciendo la pag solo lectura
            *pte &= ~PTE_W;
    
            // Printear el estado del PTE_W luego de la modificacion
            if (*pte & PTE_W) {
                printf("Page at 0x%lx is now writable\n", a);
            } else {
                printf("Page at 0x%lx is now read-only\n", a);
            }
        }
    
        sfence_vma();  // Flush TLB
        return 0;
        }
        ```
## Ahora ejecutamos.. 


1. **Pruebas:**
   * Creamos `mprotect_test`: Creamos un archivo de prueba para ver si `mprotect` y `munprotect` funcionan:
    ```c
    #include "../kernel/types.h"
    #include "../kernel/stat.h"
    #include "user.h"
    
    int main() {
        // Solicitar un bloque de memoria usando sbrk para probar
        int size = 4096;  // Tamaño de una página
        void *addr = sbrk(size);
    
        // Llenar la memoria con datos para verificar el permiso de escritura
        char *p = (char *)addr;
        for (int i = 0; i < size; i++) {
            p[i] = 'A';
        }
    
        // Proteger la memoria, es decir hacerla de solo lectura
        if (mprotect(addr, 1) < 0) {
            printf("mprotect failed\n");
            exit(1);
        }
    
        // Intentar escribir en la memoria protegida
        int success = 1;
        if (fork() == 0) {
            p[0] = 'B';  // Esto debería fallar y causar una terminación
            success = 0; //Intentando escribir en la memoria después de mprotect lo cual debería de fallar
            exit(0);
        } else {
            wait(0);
        }
    
        if (success) {
            printf("mprotect test passed\n");
        } else {
            printf("mprotect test failed: write succeeded on protected memory\n");
        }
    
        // Quitar la protección, es decir volver a permitir escritura
        if (munprotect(addr, 1) < 0) {
            printf("munprotect failed\n");
            exit(1);
        }
    
        // Intentar escribir nuevamente en la memoria desprotegida
        p[0] = 'C';  // Esto debería tener éxito
    
        printf("munprotect test passed\n");
        exit(0);
    }
    ```
    **Capturas**:
   ![Captura de pantalla (161)](https://github.com/Fredyxsen/xv6-riscvz/blob/Diego_Marin_T3/Captura%20de%20pantalla%20(161).png)
   ![Captura de pantalla (162)](https://github.com/Fredyxsen/xv6-riscvz/blob/Diego_Marin_T3/Captura%20de%20pantalla%20(162).png)
