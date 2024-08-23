## Informe de Instalación de xv6

**Pasos Seguidos:**

1. **Clonación del Repositorio:** Se obtuvo el código fuente de xv6 desde GitHub utilizando `git clone`.
2. **Creación de Rama:** Se creó una nueva rama para mantener los cambios organizados.
3. **Instalación de Dependencias:** Se instalaron las herramientas necesarias, incluyendo QEMU y el compilador GCC.
4. **Compilación:** Se compiló el código fuente de xv6 para la arquitectura RISC-V.
5. **Ejecución en QEMU:** Se inició xv6 en un entorno emulado utilizando QEMU.
6. **Verificación:** Se ejecutaron comandos básicos en xv6 para confirmar su funcionamiento.

**Problemas y Soluciones:**

* **Incompatibilidad de Instrucciones:** Se encontraron instrucciones no soportadas en el código fuente. Se resolvió comentando las líneas problemáticas en el archivo `kernel/riscv.h`.
* **Error en `make clean`:** Se presentaron dificultades al limpiar los archivos de compilación. Se solucionó verificando permisos y cerrando programas que pudieran estar utilizando los archivos.

**Confirmación de Funcionamiento:**

* La compilación y ejecución de xv6 en QEMU se completaron sin errores.
* Se verificó la funcionalidad básica mediante la ejecución de comandos simples dentro del sistema operativo.

**Conclusión:**

La instalación de xv6 fue exitosa, superando los desafíos encontrados durante el proceso. El sistema operativo está funcionando correctamente en el entorno QEMU, listo para ser explorado y utilizado. 

**Recomendaciones:**

* Profundizar en el estudio de xv6 explorando sus funcionalidades y características.
* Consultar la documentación oficial para comprender mejor su arquitectura y funcionamiento interno
* Considerar la posibilidad de realizar modificaciones o extensiones al código fuente como parte de un proyecto de aprendizaje. 
