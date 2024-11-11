## Tarea 3: Protección de Memoria en xv6 - Implementación de mprotect y munprotect

### Introducción

En este trabajo, se implementaron las funciones del sistema operativo `mprotect` y `munprotect` en el sistema xv6. Estas funciones permiten modificar los permisos de acceso a una región de memoria de un proceso, lo que es fundamental para garantizar la seguridad y la integridad de los datos.

### Objetivos

* **Implementar** las funciones del sistema `mprotect` y `munprotect` en xv6.
* **Modificar** la tabla de páginas para reflejar los cambios de permisos.
* **Verificar** la correcta funcionalidad de las funciones implementadas a través de pruebas unitarias.

### Diseño e Implementación

#### 1. Declaración de las funciones del sistema
* **syscall.h:** Se agregaron las constantes `SYS_mprotect` y `SYS_munprotect` para identificar las nuevas llamadas al sistema.
* ```c
    #define SYS_mprotect 22  //nuevas llamadas
    #define SYS_munprotect 23 //nuevas llamadas
    ```
* **user.h:** Se declararon los prototipos de las funciones `mprotect` y `munprotect` en el espacio de usuario.

#### 2. Implementación de las funciones del sistema en syscall.c
* **sys_mprotect y sys_munprotect:** Estas funciones extraen los argumentos de la llamada al sistema (dirección inicial y tamaño de la región) y validan su corrección. Luego, delegan la tarea de modificar los permisos a las funciones `mprotect` y `munprotect` correspondientes en el espacio del kernel.

#### 3. Implementación de mprotect y munprotect en proc.c
* **mprotect:**
    * **Iteración sobre las páginas:** Recorre cada página dentro del rango especificado.
    * **Obtención de la entrada de la tabla de páginas:** Utiliza la función `walk` para obtener la entrada de la tabla de páginas correspondiente a cada dirección virtual.
    * **Modificación de permisos:** Desactiva el bit `PTE_W` en la entrada de la tabla de páginas para marcar la página como de solo lectura.
    * **Refresco de la TLB:** Llama a `sfence_vma` para invalidar las entradas de la TLB correspondientes a las páginas modificadas.
* **munprotect:**
    * **Lógica similar a mprotect:** Itera sobre las páginas, obtiene las entradas de la tabla de páginas y restaura el bit `PTE_W` para permitir la escritura.

#### 4. Modificación de la tabla de páginas
La modificación de los permisos se realiza directamente sobre la entrada de la tabla de páginas. Al desactivar o activar el bit `PTE_W`, se indica al hardware si se permite o no la escritura en la página correspondiente. El refresco de la TLB es esencial para asegurar que los cambios en la tabla de páginas se reflejen en la traducción de direcciones.

### Pruebas
Se creó un programa de prueba, `mprotect_test.c`, para verificar el correcto funcionamiento de las funciones implementadas. Este programa intenta escribir en una región de memoria protegida como de solo lectura y verifica que se genere una excepción.

### Justificación de los cambios
* **Iteración sobre las páginas:** Es necesario recorrer cada página dentro del rango especificado para modificar los permisos de todas ellas.
* **Obtención de la entrada de la tabla de páginas:** La función `walk` permite acceder a la estructura de la tabla de páginas y modificar los permisos a nivel de página individual.
* **Modificación del bit PTE_W:** Este bit controla el permiso de escritura en una página. Al desactivarlo, se prohíbe la escritura.
* **Refresco de la TLB:** La TLB almacena una caché de las traducciones de direcciones. Al modificar la tabla de páginas, es necesario invalidar las entradas de la TLB correspondientes para asegurar que se utilicen las nuevas traducciones.

### Conclusiones
La implementación de las funciones `mprotect` y `munprotect` en xv6 proporciona una forma de controlar los permisos de acceso a la memoria a nivel de página. Esta funcionalidad es fundamental para la seguridad y la integridad de los datos, ya que permite proteger regiones de memoria críticas contra accesos no autorizados.

**[Incluir aquí cualquier diagrama o figura que ayude a visualizar la implementación]**

**[Añadir secciones adicionales si es necesario, como por ejemplo, consideraciones de rendimiento o posibles extensiones]**

**Ejemplos concretos:**

Imagina una aplicación que maneja datos sensibles, como contraseñas o información financiera. Al utilizar `mprotect`, puedes marcar la región de memoria que almacena estos datos como de solo lectura, evitando que otros procesos puedan modificarlos accidentalmente o de forma maliciosa.

**Consideraciones de seguridad:**

* **Ataques de desbordamiento de búfer:** `mprotect` puede ayudar a mitigar los efectos de estos ataques al proteger las zonas de memoria adyacentes a los búferes.
* **Escalada de privilegios:** Al limitar los permisos de escritura en ciertas regiones de memoria, se dificulta que un atacante pueda modificar el estado del sistema para obtener privilegios más altos.

**Optimizaciones:**

* **Búsqueda binaria:** Para mejorar la eficiencia de la búsqueda de la entrada de la tabla de páginas, se puede utilizar una búsqueda binaria en lugar de una búsqueda lineal.

**Importante:** Adaptar este informe a tu estilo de escritura y a los requisitos específicos de tu tarea.
