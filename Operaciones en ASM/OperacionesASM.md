# Compilación y Ejecución en Ubuntu

## 1. Código Fuente en C (`practica2_asm.c`)

El siguiente código en C implementa ensamblador en línea (`__asm__` / `asm`) en sintaxis AT&T para llenar un arreglo en memoria interactuando directamente con los registros de la CPU.

```c
#include <stdio.h>
#define TAMANO 5

int main(void) {
    int arreglo[TAMANO] = {0}; // Inicializado en ceros

    asm (
        "movl $0, %%ecx\\n\\t"          // %ecx = contador del bucle (i = 0)
        "mi_bucle:\\n\\t"               // Inicio de la etiqueta del bucle
        "cmpl %1, %%ecx\\n\\t"          // Compara 'i' (%ecx) con TAMANO (%1)
        "jge fin_bucle\\n\\t"           // Si i >= TAMANO, sal del bucle (Jump if Greater or Equal)
        
        // Asignación: arreglo[i] = (i + 1) * 10
        "movl %%ecx, %%eax\\n\\t"       // %eax = i
        "addl $1, %%eax\\n\\t"          // %eax = i + 1
        "imull $10, %%eax\\n\\t"        // %eax = (i + 1) * 10
        
        // Guardar valor en la memoria: base + (índice * tamaño_elemento)
        "movl %%eax, (%0, %%rcx, 4)\\n\\t" // arreglo[i] = %eax
        "incl %%ecx\\n\\t"              // i++ (incrementa contador)
        "jmp mi_bucle\\n\\t"            // Salta de vuelta al inicio del bucle
        "fin_bucle:\\n\\t"
        : // No hay operandos de salida (modificamos la memoria directamente)
        : "r" (arreglo), "r" (TAMANO) // %0 = dirección base del arreglo, %1 = número de elementos
        : "%rax", "%rcx", "memory"   // Registros modificados + avisa modificación de memoria
    );

    // Verificación e impresión de los valores
    printf("Contenido del arreglo:\\n");
    for (int i = 0; i < TAMANO; i++) {
        printf("arreglo[%d] = %d\\n", i, arreglo[i]);
    }

    return 0;
}

```

## 2. Requisitos Previos en Ubuntu

Tener instaladas las herramientas esenciales de desarrollo (`build-essential` incluye `gcc` y `make`).

Abrir la terminal (`Ctrl + Alt + T`) y ejecutar:

```bash
sudo apt update
sudo apt install build-essential -y

```

## 3. Crear el Archivo de C

Usar cualquier editor de texto por terminal como `nano` o `gedit`:

```bash
nano practica2_asm.c

```

Pegar el código anterior dentro del archivo, guardar (`Ctrl + O`, presionar `Enter`) y salir (`Ctrl + X`).


## 4. Compilación del Programa

Compilar  el archivo `.c` usando **GCC**:

```bash
gcc -Wall -O0 practica2_asm.c -o practica2_asm

```

* `-Wall`: Muestra todas las advertencias (warnings).
* `-O0`: Desactiva las optimizaciones del compilador para asegurar que el código ensamblador se ejecute exactamente como se escribió.
* `-o practica2_asm`: Especifica el nombre del ejecutable generado.

## 5. Ejecución del Programa

Ejecutar el programa compilado desde la terminal:

```bash
./practica2_asm

```

### Salida esperada en la terminal:

```text
Contenido del arreglo:
arreglo[0] = 10
arreglo[1] = 20
arreglo[2] = 30
arreglo[3] = 40
arreglo[4] = 50

```

## 6. Análisis e Inspección del Ensamblador Generado

```bash
gcc -S -masm=att practica2_asm.c -o practica2_asm.s

```

Ver el contenido del archivo generado `.s`:

```bash
cat practica2_asm.s

```

Esto permite analizar la interacción directa entre C, las instrucciones ensamblador (`movl`, `addl`, `imull`, `cmpl`, `jge`) y los registros x86_64 (`%eax`, `%ecx`, `%rcx`).
"""