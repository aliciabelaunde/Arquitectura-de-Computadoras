#include <stdio.h>

int main() {
    int arreglo[] = {10, 20, 30, 40, 50};
    int longitud = sizeof(arreglo) / sizeof(arreglo[0]);
    int suma = 0;

    // Bloque de ensamblador en línea (GCC / x86-64)
    __asm__ (
        "mov ecx, %[len]\n\t"        // ecx = contador del bucle (longitud)
        "mov rsi, 0\n\t"            // rsi = índice i (0, 1, 2, ...)
        "xor eax, eax\n\t"          // eax = 0 (acumulador para la suma)

        "bucle_suma:\n\t"
        "add eax, dword ptr [%[arr] + rsi*4]\n\t" // suma += arreglo[i]
        "inc rsi\n\t"               // i++
        "loop bucle_suma\n\t"       // decrementa ecx y repite si ecx != 0

        "mov %[res], eax\n\t"       // guarda el resultado en la variable 'suma'
        : [res] "=r" (suma)         // Salida: variable 'suma' de C
        : [arr] "r" (arreglo),      // Entradas: puntero al arreglo
          [len] "r" (longitud)      // y longitud
        : "eax", "ecx", "rsi"       // Registros modificados
    );

    printf("La suma del arreglo es: %d\n", suma);

    return 0;
}