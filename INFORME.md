# Instalación de xv6: Diego Marin

**Preparación del Entorno**

* **Ubuntu como Base:** Procedemos a instalar Ubuntu mediante powershell de windows.

* **Herramientas Esenciales:** A través de Ubuntu, instalamos las siguientes herramientas clave:
    * **XV6:** El cual sera la base para trabajar las tareas de este ramo. 
    * **Toolchain de RISC-V:** Este conjunto de herramientas, que incluye el compilador GCC, nos permitirá construir xv6 para la arquitectura RISC-V.
    * **Git:** Git es fundamental para clonar el repositorio de xv6 desde GitHub y gestionar el control del proyecto.
    * **QEMU:** Este emulador de hardware nos permitirá ejecutar xv6 en un entorno virtualizado, simulando un sistema RISC-V en Windows.

**Obtención y Configuración del Código**

* **Clonación del Repositorio:** Utilizamos `git clone` para descargar una copia local del repositorio de xv6 desde GitHub.
* **Acceso al Directorio:** Navegamos al directorio `xv6` utilizando el comando `cd` para comenzar a trabajar con el código fuente.

**Compilación y Ejecución**

* **Compilación con QEMU:** Empleamos el comando `make qemu` para compilar xv6, asegurándonos de estar en el directorio de **XV6-RISCV**.
* **Verificación de QEMU:** Despues de un gran output `make qemu` se inicia satisfactoriamente en **Ubuntu**
* **Pruebas Básicas:** Dentro del entorno QEMU, ejecutamos comandos sencillos como `ls`, `echo "Hola mundo"` y `cat README` para verificar que xv6 se ha instalado y que todo está funcionando correctamente.

**Conclusión**

Siguiendo estos pasos, pude instalar y ejecutar xv6 en QEMU. Con ayuda de la inteligencia artificial y sobre todo foros de internet para poder corregir cualquier error que se presentara en la instalacion y ejecucion del xv6.
**Problemas y Soluciones:**

* **Incompatibilidad con **QEMU y TOOLCHAIN**:** Al momento de ejecutatar `xv6-riscv` en la consola de Ubuntu, se produjo un error bastante especifico que me costo demasiado encontrar la solucion, ya que la inteligencia artificial no fue para nada util para llegar a esta.
* ![image](https://github.com/user-attachments/assets/4497c441-f4c4-4ec3-bea9-c6fb69229560)
  Lo cual mediante un foro de internet, pude llegar a la solucion la cual fue actualizar el Qemu a su version 8.0.0, ya que la que yo habia instalado mediante tutoriales estaba bastante desactualizada.

  

**Confirmación de Funcionamiento:**
La instalación de **xv6** fue exitosa, superando los desafíos encontrados durante el proceso. El sistema operativo está funcionando correctamente en el entorno **QEMU**. Se puede apreciar haciendo comandos de prueba.

**1°PASO**
-Ingresar al directorio del `git clone` del **repositorio** que hicimos anteriormente
![Captura de pantalla (43)](https://github.com/user-attachments/assets/e3d855b2-4964-449a-aff8-7f77a6d5d38b)

**2°PASO**
-Ejecutamos `MAKE QEMU` para asegurarnos de esta todo en orden
![Captura de pantalla (43)](https://github.com/user-attachments/assets/f0b45044-ee90-4f3f-80d0-8a29eb1006b5)

**3°PASO** 
-Ponemos comandos de prueba tal como `echo ¨hola mundo¨`, `$ ls` y por ultimo `$ CAT README`


![Captura de pantalla (45)](https://github.com/user-attachments/assets/696a4efa-6a44-4c61-8ca2-742bf7ef3e29)
![Captura de pantalla (44)](https://github.com/user-attachments/assets/5bc0e589-a50a-4be2-974f-62e1da26f630)


