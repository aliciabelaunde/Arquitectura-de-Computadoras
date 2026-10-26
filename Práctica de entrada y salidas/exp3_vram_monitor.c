#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

uint8_t g_ram[256];

void inicializar_vram(void) {
    for (int i = 0xF0; i <= 0xFF; i++) {
        g_ram[i] = 0x20; /* Espacio en blanco */
    }
}

bool vram_escribir(uint8_t fila, uint8_t col, char c) {
    if (fila >= 4 || col >= 4) {
        return false;
    }
    uint8_t dir = 0xF0 + (fila * 4) + col; /* Dirección VRAM */
    g_ram[dir] = (uint8_t)c;
    return true;
}

void vram_scroll_arriba(void) {
    for (int f = 0; f < 3; f++) {
        for (int c = 0; c < 4; c++) {
            g_ram[0xF0 + (f * 4) + c] = g_ram[0xF0 + ((f + 1) * 4) + c];
        }
    }
    for (int c = 0; c < 4; c++) {
        g_ram[0xF0 + (3 * 4) + c] = 0x20;
    }
}

void imprimir_vram(void) {
    printf("----- VRAM 4x4 -----\n");
    for (int f = 0; f < 4; f++) {
        for (int c = 0; c < 4; c++) {
            printf("[%c]", (char)g_ram[0xF0 + (f * 4) + c]);
        }
        printf("\n");
    }
    printf("--------------------\n");
}

int main(void) {
    inicializar_vram();

    printf("--- Experimento 3: VRAM y Scroll ---\n");
    vram_escribir(0, 0, '1'); vram_escribir(0, 1, '2');
    vram_escribir(1, 0, '3'); vram_escribir(1, 1, '4');
    vram_escribir(2, 0, '5'); vram_escribir(2, 1, '6');
    vram_escribir(3, 0, '7'); vram_escribir(3, 1, '8');

    printf("Estado inicial:\n");
    imprimir_vram();

    printf("Aplicando scroll hacia arriba...\n");
    vram_scroll_arriba();
    imprimir_vram();

    return 0;
}