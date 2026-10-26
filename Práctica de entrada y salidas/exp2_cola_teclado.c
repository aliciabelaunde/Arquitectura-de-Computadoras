#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define COLA_BASE_DIR 0x70
#define DIR_KB_HEAD   0x78
#define DIR_KB_TAIL   0x79
#define DIR_KB_COUNT  0x7A
#define COLA_CAPACIDAD 8

uint8_t g_ram[256];

void inicializar_ram(void) {
    g_ram[DIR_KB_HEAD] = 0;
    g_ram[DIR_KB_TAIL] = 0;
    g_ram[DIR_KB_COUNT] = 0;
}

bool cola_teclado_encolar(uint8_t ascii) {
    uint8_t tail = g_ram[DIR_KB_TAIL];
    uint8_t count = g_ram[DIR_KB_COUNT];

    if (count >= COLA_CAPACIDAD) {
        return false; /* BUFFER OVERFLOW */
    }

    g_ram[COLA_BASE_DIR + tail] = ascii;
    g_ram[DIR_KB_TAIL] = (tail + 1) % COLA_CAPACIDAD;
    g_ram[DIR_KB_COUNT] = count + 1;
    return true;
}

bool cola_teclado_desencolar(uint8_t *salida_ascii) {
    uint8_t head = g_ram[DIR_KB_HEAD];
    uint8_t count = g_ram[DIR_KB_COUNT];

    if (count == 0) {
        return false; /* COLA VACÍA */
    }

    *salida_ascii = g_ram[COLA_BASE_DIR + head];
    g_ram[DIR_KB_HEAD] = (head + 1) % COLA_CAPACIDAD;
    g_ram[DIR_KB_COUNT] = count - 1;
    return true;
}

int main(void) {
    inicializar_ram();
    uint8_t val;

    printf("--- Experimento 2: Cola FIFO ---\n");
    cola_teclado_encolar('H');
    cola_teclado_encolar('O');
    cola_teclado_encolar('L');
    cola_teclado_encolar('A');

    while (cola_teclado_desencolar(&val)) {
        printf("Desencolado: %c\n", (char)val);
    }

    return 0;
}