# Instalación de xv6: Diego Marin

**Preparación del Entorno**

* **Ubuntu como Base:** Procedemos a instalar Ubuntu mediante powershell de windows.

* **Herramientas Esenciales:** A través de Ubuntu, instalamos las siguientes herramientas clave:
    * **Toolchain de RISC-V:** Este conjunto de herramientas, que incluye el compilador GCC, nos permitirá construir xv6 para la arquitectura RISC-V.
    * **Git:** Git es fundamental para clonar el repositorio de xv6 desde GitHub y gestionar el control de versiones del proyecto.
    * **QEMU:** Este emulador de hardware nos permitirá ejecutar xv6 en un entorno virtualizado, simulando un sistema RISC-V.

**Obtención y Configuración del Código**

* **Clonación del Repositorio:** Utilizamos `git clone` para descargar una copia local del repositorio de xv6 desde GitHub.
* **Acceso al Directorio:** Navegamos al directorio `xv6` utilizando el comando `cd` para comenzar a trabajar con el código fuente.

**Compilación y Ejecución**

* **Compilación con QEMU:** Empleamos el comando `make qemu` para compilar xv6, asegurándonos de especificar el `TOOLPREFIX` adecuado para la toolchain de RISC-V.
* **Verificación de QEMU:** Ejecutamos `make qemu` nuevamente para confirmar que QEMU está instalado y configurado correctamente.
* **Pruebas Básicas:** Dentro del entorno QEMU, ejecutamos comandos sencillos como `ls`, `echo "Hola mundo"` y `cat README` para verificar que xv6 se ha instalado y está funcionando como se espera.

**Conclusión**

Siguiendo estos pasos, pude instalar y ejecutar xv6 en QEMU. Con ayuda de la inteligencia artificial para poder corregir cualquier error que se presentara en la instalacion y ejecucion del xv6.
**Problemas y Soluciones:**

* **Incompatibilidad de Instrucciones:** Se encontraron instrucciones no soportadas en el código fuente. Se resolvió comentando las líneas problemáticas en el archivo `kernel/riscv.h`.
* **Incompatibilidad con la version de Qemu** Se tuvo un problema en compatibilidad entre versiones de Qemu ya que mi ubuntu estaba desactualizado en ese aspecto. Por medio de Chatgpt se logro llegar a la solución instalando la versión adecuada y logrando asi su funcionamiento.

**Confirmación de Funcionamiento:**
La instalación de xv6 fue exitosa, superando los desafíos encontrados durante el proceso. El sistema operativo está funcionando correctamente en el entorno QEMU. Se puede apreciar haciendo comandos de prueba.
Fotos:
![Captura de pantalla (25)](https://github.com/user-attachments/assets/39cb43ea-0628-470f-9f89-dd129d6036b2)
![Captura de pantalla (24)](https://github.com/user-attachments/assets/1151173e-0161-48ca-83e5-40ffe1c834b3)
![Captura de pantalla (26)](https://github.com/user-attachments/assets/92d38998-ff89-4b7f-99ef-753fbced0980)




