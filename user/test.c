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