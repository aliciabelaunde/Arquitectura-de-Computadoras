// Practico en Comando
// Sumar un arreglo almacenado en RAM

#include <stdio.h>

int main() {
    // Declaración e inicialización del arreglo en memoria RAM
    int arreglo[] = {10, 20, 30, 40, 50};
    
    // Cálculo de la cantidad de elementos en el arreglo
    int longitud = sizeof(arreglo) / sizeof(arreglo[0]);
    
    // Variable acumuladora para almacenar la suma
    int suma = 0;

    // Recorrido del arreglo para sumar sus elementos
    for (int i = 0; i < longitud; i++) {
        suma += arreglo[i];
    }

    // Impresión del resultado
    printf("La suma del arreglo es: %d\n", suma);

    return 0;
}