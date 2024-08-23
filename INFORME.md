# Informe de Instalación de xv6

**Pasos Seguidos:**

1. **Clonar el Repositorio:**
   * Se utilizó el siguiente comando para clonar el repositorio de xv6-riscv desde GitHub:
     ```bash
     git clone [https://github.com/Fredyxsen/xv6-riscvs.git](https://github.com/Fredyxsen/xv6-riscvs.git)
     ```

2. **Crear una Nueva Rama:**
   * Se creó una nueva rama en el repositorio local para realizar los cambios necesarios:
     ```bash
     git checkout -b mi_rama_xv6 
     ```

3. **Instalar Dependencias:**
   * Se instalaron las dependencias necesarias para compilar y ejecutar xv6 en Ubuntu:
     ```bash
     sudo apt install qemu build-essential gcc 
     ```

4. **Compilar xv6:**
   * Se compiló el código fuente de xv6 utilizando el Makefile y especificando el prefijo de herramientas adecuado:
     ```bash
     make qemu TOOLPREFIX=riscv64-linux-gnu-
     ```

5. **Ejecutar xv6:**
   * Se ejecutó xv6 en QEMU sin interfaz gráfica:
     ```bash
     make qemu-nox TOOLPREFIX=riscv64-linux-gnu-
     ```

6. **Verificar la Instalación:**
   * Se probaron comandos básicos dentro de xv6 en QEMU para confirmar su correcto funcionamiento:
     ```
     ls
     echo "Hola xv6"
     cat README 
     ```

**Problemas Encontrados y Soluciones:**

* **Error de compilación relacionado con CSRs no soportados:**
   * El archivo `kernel/riscv.h` hacía referencia a instrucciones `menvcfg` y `stimecmp` no disponibles en la configuración de RISC-V utilizada.
   * **Solución:** Se comentaron las líneas problemáticas en `kernel/riscv.h` para evitar el uso de estas instrucciones.
   * **Impacto:** Es posible que algunas funcionalidades de xv6 se vean afectadas debido a la desactivación de estas instrucciones.

* **Error al ejecutar `make clean`:**
   * El comando `make clean` no funcionaba correctamente, posiblemente debido a problemas de permisos o archivos abiertos en otros programas.
   * **Solución:** Se verificaron y ajustaron los permisos de archivos y directorios, y se aseguraron de que ningún otro programa estuviera utilizando los archivos que `make clean` intentaba eliminar.

**Confirmación de que xv6 está funcionando correctamente:**

* La ejecución exitosa de `make qemu-nox` sin errores de compilación indica que xv6 se compiló correctamente para la configuración de RISC-V utilizada.
* La capacidad de ejecutar comandos básicos como `ls`, `echo` y `cat` dentro de QEMU confirma que xv6 se está ejecutando y respondiendo a comandos.

**Conclusión:**

Se ha instalado y ejecutado con éxito el sistema operativo xv6 en un entorno QEMU utilizando Ubuntu. Se solucionaron problemas relacionados con la compatibilidad de instrucciones y la limpieza de archivos de compilación. La ejecución de comandos básicos dentro de xv6 confirma su correcto funcionamiento.

**Recomendaciones:**

* Explorar más a fondo las funcionalidades de xv6 ejecutando otros comandos y programas.
* Consultar la documentación de xv6 para obtener más información sobre su arquitectura y cómo interactuar con él.
* Considerar la posibilidad de realizar modificaciones o extensiones a xv6 como parte de un proyecto de aprendizaje o investigación.

**Nota:** Este informe asume que se ha utilizado el repositorio `https://github.com/Fredyxsen/xv6-riscvs.git` y que se ha trabajado en un entorno Ubuntu en Windows. Los pasos y soluciones pueden variar ligeramente dependiendo del repositorio específico y del sistema operativo utilizado. 