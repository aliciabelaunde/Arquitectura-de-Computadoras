# Ejercicio 1

## 1. Código Fuente en C (`Ejercicio2.c`)

```c

#include <stdio.h>

int main() {
    int arreglo[] = {10, 20, 30, 40, 50};
    int longitud = sizeof(arreglo) / sizeof(arreglo[0]);
    int suma = 0;

    // Bloque de ensamblador en línea (GCC / x86-64 en sintaxis Intel)
    __asm__ (
        ".intel_syntax noprefix\n\t"        // Activa la sintaxis Intel
        "mov ecx, %[len]\n\t"               // ecx = longitud
        "mov rsi, 0\n\t"                    // rsi = índice i
        "xor eax, eax\n\t"                  // eax = 0

        "bucle_suma:\n\t"
        "add eax, dword ptr [%[arr] + rsi*4]\n\t" // suma += arreglo[i]
        "inc rsi\n\t"                       // i++
        "loop bucle_suma\n\t"               // decrementa ecx y repite si ecx != 0

        "mov %[res], eax\n\t"               // guarda el resultado en 'suma'
        ".att_syntax prefix\n\t"            // Restaura la sintaxis AT&T por seguridad
        : [res] "=r" (suma)
        : [arr] "r" (arreglo),
          [len] "r" (longitud)
        : "eax", "ecx", "rsi", "cc"
    );

    printf("La suma del arreglo es: %d\n", suma);

    return 0;
}

```

## 2. Crear el Archivo de C

Usar cualquier editor de texto por terminal como `nano` o `gedit`:

```bash
nano Ejercicio2.c

```

Pegar el código anterior dentro del archivo, guardar (`Ctrl + O`, presionar `Enter`) y salir (`Ctrl + X`).


## 4. Compilación del Programa

Compilar  el archivo `.c` usando **GCC**:

```bash
gcc Ejercicio2.c -o Ejercicio2

```

## 5. Ejecución del Programa

Ejecutar el programa compilado desde la terminal:

```bash
./Ejercicio2

```

### Salida esperada en la terminal:

```text
La suma del arreglo es: 150
```
![alt text](image-1.png)