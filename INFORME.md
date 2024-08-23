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
* **Incompatibilidad con la version de Qemu** Se tuvo un problema en compatibilidad entre versiones de Qemu ya que mi ubuntu estaba desactualizado en ese aspecto. Por medio de Chatgpt se logro llegar a la solución instalando la versión adecuada y logrando asi su funcionamiento.

**Confirmación de Funcionamiento:**

* La compilación y ejecución de xv6 en QEMU se completaron sin errores.
* Se verificó la funcionalidad básica mediante la ejecución de comandos simples dentro del sistema operativo.

La instalación de xv6 fue exitosa, superando los desafíos encontrados durante el proceso. El sistema operativo está funcionando correctamente en el entorno QEMU. Se puede apreciar haciendo comandos de prueba.
Fotos:
![Captura de pantalla (25)](https://github.com/user-attachments/assets/39cb43ea-0628-470f-9f89-dd129d6036b2)
![Captura de pantalla (24)](https://github.com/user-attachments/assets/1151173e-0161-48ca-83e5-40ffe1c834b3)
![Captura de pantalla (26)](https://github.com/user-attachments/assets/92d38998-ff89-4b7f-99ef-753fbced0980)




