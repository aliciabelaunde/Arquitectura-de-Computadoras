#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t address_bus;
    uint8_t data_bus;
    bool io_read;
    bool mem_read;
} SystemBuses;

typedef struct {
    uint8_t reg_status;
    uint8_t reg_data;
} TecladoHardware;

SystemBuses g_bus;
TecladoHardware g_teclado;

void tick_controlador_teclado(SystemBuses *bus, TecladoHardware *kb) {
    if (bus->io_read) {
        if (bus->address_bus == 0x01) {
            bus->data_bus = kb->reg_status;
        } else if (bus->address_bus == 0x02) {
            bus->data_bus = kb->reg_data;
            kb->reg_status = 0; /* Handshake automático */
        }
    }
}

uint8_t cpu_instruccion_in(uint8_t puerto) {
    g_bus.address_bus = puerto;
    g_bus.io_read = true;
    g_bus.mem_read = false;

    tick_controlador_teclado(&g_bus, &g_teclado);

    uint8_t dato = g_bus.data_bus;
    g_bus.io_read = false;
    return dato;
}

int main(void) {
    /* Simulación de llegada de un dato por el puerto de teclado */
    g_teclado.reg_status = 1;
    g_teclado.reg_data = 'A';

    printf("--- Experimento 1: Lectura por Puerto ---\n");
    printf("Estado inicial - Status: %d\n", cpu_instruccion_in(0x01));
    printf("Dato leído: %c\n", (char)cpu_instruccion_in(0x02));
    printf("Estado tras lectura (Handshake): %d\n", cpu_instruccion_in(0x01));

    return 0;
}