#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define COLA_BASE_DIR 0x70
#define DIR_KB_HEAD   0x78
#define DIR_KB_TAIL   0x79
#define DIR_KB_COUNT  0x7A
#define COLA_CAPACIDAD 8

typedef struct {
    uint8_t ram[256];
    uint8_t cursor_vram;
} TerminalPC;

TerminalPC g_pc;

void inicializar_sistema(void) {
    g_pc.cursor_vram = 0xF0;
    g_pc.ram[DIR_KB_HEAD] = 0;
    g_pc.ram[DIR_KB_TAIL] = 0;
    g_pc.ram[DIR_KB_COUNT] = 0;

    for (int i = 0xF0; i <= 0xFF; i++) {
        g_pc.ram[i] = 0x20;
    }
}

bool cola_teclado_encolar(uint8_t ascii) {
    uint8_t tail = g_pc.ram[DIR_KB_TAIL];
    uint8_t count = g_pc.ram[DIR_KB_COUNT];

    if (count >= COLA_CAPACIDAD) return false;

    g_pc.ram[COLA_BASE_DIR + tail] = ascii;
    g_pc.ram[DIR_KB_TAIL] = (tail + 1) % COLA_CAPACIDAD;
    g_pc.ram[DIR_KB_COUNT] = count + 1;
    return true;
}

bool cola_teclado_desencolar(uint8_t *salida_ascii) {
    uint8_t head = g_pc.ram[DIR_KB_HEAD];
    uint8_t count = g_pc.ram[DIR_KB_COUNT];

    if (count == 0) return false;

    *salida_ascii = g_pc.ram[COLA_BASE_DIR + head];
    g_pc.ram[DIR_KB_HEAD] = (head + 1) % COLA_CAPACIDAD;
    g_pc.ram[DIR_KB_COUNT] = count - 1;
    return true;
}

void monitor_actualizar_pantalla(void) {
    printf("\n[Pantalla VRAM (0xF0-0xFF)]\n");
    for (int i = 0xF0; i <= 0xFF; i++) {
        printf("%c", (char)g_pc.ram[i]);
        if ((i - 0xF0 + 1) % 4 == 0) printf("\n");
    }
}

bool terminal_procesar_siguiente_tecla(void) {
    uint8_t tecla;
    if (!cola_teclado_desencolar(&tecla)) return false;

    if (tecla == 0x08 || tecla == 0x7F) { /* BACKSPACE */
        if (g_pc.cursor_vram > 0xF0) {
            g_pc.cursor_vram--;
            g_pc.ram[g_pc.cursor_vram] = 0x20; /* Borra carácter */
        }
    } else if (tecla >= 32 && tecla <= 126) {
        if (g_pc.cursor_vram <= 0xFF) {
            g_pc.ram[g_pc.cursor_vram] = tecla;
            g_pc.cursor_vram++;
        }
    }
    monitor_actualizar_pantalla();
    return true;
}

int main(void) {
    inicializar_sistema();

    printf("--- Reto Integrador: Terminal ---\n");

    /* Simulación de entrada por teclado */
    cola_teclado_encolar('C');
    cola_teclado_encolar('A');
    cola_teclado_encolar('S');
    cola_teclado_encolar('A');
    cola_teclado_encolar(0x08); /* Simulación de Backspace */

    while (terminal_procesar_siguiente_tecla());

    return 0;
}