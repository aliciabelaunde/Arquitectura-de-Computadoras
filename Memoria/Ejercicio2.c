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