# Comandos en Linux

## Procesador

### lscpu

El comando `lscpu` en Linux muestra la arquitectura de la CPU, número de núcleos, detalles de cachés y vulnerabilidades de hardware del sistema.

![alt text](<Screenshot 2026-08-17 113448.png>)

![alt text](<Screenshot 2026-08-17 113651.png>)


**Información General del Procesador**

* **Architecture (x86_64):** Arquitectura del procesador de 64 bits.
* **CPU op-mode(s) (32-bit, 64-bit):** Indica que la CPU puede ejecutar código tanto de 32 bits como de 64 bits.
* **Address sizes (39 bits physical, 48 bits virtual):** La cantidad de memoria RAM direccionable a nivel físico (hasta 512 GB) y a nivel virtual (hasta 256 TB).
* **Byte Order (Little Endian):** Orden en que se almacenan los bytes en memoria (los bytes menos significativos se guardan en las direcciones más bajas).
* **CPU(s) (1):** Número total de procesadores lógicos disponibles para la máquina virtual.
* **On-line CPU(s) list (0):** El identificador del núcleo que está actualmente activo (CPU ID 0).
* **Vendor ID (GenuineIntel):** Fabricante del procesador físico (Intel).
* **Model name (Intel(R) Core(TM) i3-10110U CPU @ 2.10GHz):** Modelo comercial del procesador y su frecuencia base (2.10 GHz).
* **CPU family (6) / Model (142) / Stepping (12):** Identificadores internos del fabricante que detallan la microarquitectura específica y la revisión del silicio del procesador.
* **Thread(s) per core (1):** Número de hilos por núcleo asignados a esta máquina virtual.
* **Core(s) per socket (1):** Número de núcleos físicos asignados por zócalo.
* **Socket(s) (1):** Número de zócalos (conectores físicos de procesador) expuestos a la maquina virtual.
* **BogoMIPS (5184.01):** Métrica simplificada del kernel de Linux para medir la velocidad de bucle del procesador.
* **Flags:** Conjunto de características y extensiones de instrucciones soportadas por la CPU (ej. `sse4_2`, `avx2`, `nx`, `hypervisor`).


**Virtualización y Memoria Caché**

* **Hypervisor vendor (KVM):** El hipervisor de virtualización subyacente detectado por la máquina virtual.
* **Virtualization type (full):** Indica soporte para virtualización completa basada en hardware.
* **L1d (32 KiB):** Caché de Nivel 1 para datos dedicada a esta CPU.
* **L1i (32 KiB):** Caché de Nivel 1 para instrucciones dedicada a esta CPU.
* **L2 (256 KiB):** Caché de Nivel 2, intermedia y más rápida que la L3.
* **L3 (4 MiB):** Caché de Nivel 3 compartida, de mayor capacidad pero mayor latencia.

**NUMA (Non-Uniform Memory Access)**

* **NUMA node(s) (1):** Indica que existe un único nodo de memoria no uniforme asignado.
* **NUMA node0 CPU(s) (0):** El núcleo 0 está asociado al nodo de memoria NUMA 0.


**Vulnerabilidades y Mitigaciones (Seguridad de Hardware)**

Muestra el estado de protección del procesador ante ataques conocidos basados en fallos de diseño de CPU:

* **Mitigation (Mitigado):** Se aplicaronparches de software/firmware para mitigar el riesgo (ej. *Spectre v1*, *Spectre v2*, *Retbleed*).
* **Not affected (No afectado):** El procesador o la máquina virtual no es vulnerable a ese ataque en particular (ej. *Meltdown*, *L1tf*, *Mds*, *Tsx async abort*).
* **Vulnerable / Unknown:** Algunas vulnerabilidades (como *Mmio stale data* o *Spec store bypass*) permanecen parcialmente expuestas debido a las restricciones de aislamiento del hipervisor o a la falta de microcódigo actualizado en el host.

## Buses y Almacenamiento

### lspci
El comando `lspci` lista todos los dispositivos conectados a los buses PCI (Peripheral Component Interconnect) de la placa base virtual simulada por VirtualBox.

![alt text](<Screenshot 2026-08-17 113849.png>)

**Estructura de la Dirección PCI**

Al inicio de cada línea aparece una nomenclatura numérica (por ejemplo, `00:02.0`):

* **00:** Número de bus PCI (todos están en el bus `00`).
* **02:** Número de dispositivo o ranura en dicho bus (en hexadecimal).
* **.0:** Número de función dentro del dispositivo (permite que un solo chip tenga varias funciones independientes).


**Desglose Dispositivo por Dispositivo**

`00:00.0 Host bridge: Intel Corporation 440FX - 82441FX PMC [Natoma] (rev 02)`
* **Definición:** Puente Norte (Northbridge) emulado.
* **Función:** Conecta el procesador principal (CPU) y la memoria RAM con el resto del bus PCI. El chipset Intel 440FX es un estándar genérico ampliamente usado en virtualización por su alta compatibilidad.


`00:01.0 ISA bridge: Intel Corporation 82371SB PIIX3 ISA [Natoma/Triton II]`
* **Definición:** Puente Sur (Southbridge) / Puente ISA emulado.
* **Función:** Conecta el bus PCI moderno con el bus ISA clásico (legacy) para dar soporte a componentes del sistema básico de bajo nivel como temporizadores, controladores de interrupciones (PIC) o puertos serie/paralelo.


`00:01.1 IDE interface: Intel Corporation 82371AB/EB/MB PIIX4 IDE (rev 01)`
* **Definición:** Controlador de disco IDE/PATA.
* **Función:** Es la interfaz secundaria para unidades de almacenamiento masivo. En VirtualBox se usa comúnmente para la unidad lectora virtual de CD/DVD (donde se montan las ISOs).


`00:02.0 VGA compatible controller: VMware SVGA II Adapter`
* **Definición:** Tarjeta gráfica o adaptador de pantalla virtual.
* **Función:** Encargada de renderizar la interfaz gráfica de usuario (pantalla de la máquina virtual). Aunque usas VirtualBox, emula el controlador genérico de VMware por compatibilidad de drivers de video.


**`00:03.0 Ethernet controller: Intel Corporation 82540EM Gigabit Ethernet Controller (rev 02)`**
* **Definición:** Tarjeta de red (NIC) para conexión a Internet o red local.
* **Función:** Emula el chip físico de red Intel PRO/1000 MT Desktop, lo que permite a la máquina virtual conectarse a la red del equipo anfitrión a velocidades de hasta 1 Gbps.


**`00:04.0 System peripheral: InnoTek Systemberatung GmbH VirtualBox Guest Service`**
* **Definición:** Periférico de sistema propio de VirtualBox (Guest Additions).
* **Función:** Es el canal de comunicación entre el sistema operativo invitado (Ubuntu) y el sistema operativo anfitrión. Permite funciones como portapapeles compartido, carpetas compartidas y ajuste automático de resolución de pantalla.


`00:05.0 Multimedia audio controller: Intel Corporation 82801AA AC'97 Audio Controller (rev 01)`
* **Definición:** Tarjeta de sonido emulada.
* **Función:** Controlador basado en el estándar AC'97 que procesa el audio entrante y saliente dentro de la máquina virtual.


`00:06.0 USB controller: Apple Inc. KeyLargo/Intrepid USB`
* **Definición:** Controlador USB 1.1 emulado.
* **Función:** Administra los puertos USB virtuales básicos de la máquina, comúnmente para la emulación de teclado, ratón o tabletas táctiles.


`00:07.0 Bridge: Intel Corporation 82371AB/EB/MB PIIX4 ACPI (rev 08)`
* **Definición:** Controlador de administración de energía (ACPI).
* **Función:** Gestiona el estado de energía de la máquina virtual (apagar el sistema por software, suspensión, reinicio y eventos de energía).


`00:0b.0 USB controller: Intel Corporation 82801FB/FBM/FR/FW/FRW (ICH6 Family) USB2 EHCI Controller`
* **Definición:** Controlador USB 2.0 (EHCI).
* **Función:** Proporciona soporte para dispositivos USB de mayor velocidad (alta velocidad/High-Speed USB 2.0) pasados desde el sistema host a la máquina virtual.


`00:0d.0 SATA controller: Intel Corporation 82801HM/HEM (ICH8M/ICH8M-E) SATA Controller [AHCI mode] (rev 02)`
* **Definición:** Controlador de almacenamiento SATA (AHCI).
* **Función:** Interfaz principal para el disco duro virtual (VDI/VMDK) donde está instalado el sistema operativo Ubuntu, permitiendo velocidades de transferencia de disco modernas.


### lsblk
El comando `lsblk` (List Block Devices) muestra información sobre los dispositivos de almacenamiento en bloque del sistema (discos duros, particiones, unidades ópticas y dispositivos virtuales de montaje).

![alt text](<Screenshot 2026-08-17 113954.png>)


**Explicación de las Columnas de la Encabezado**

* **NAME:** Nombre del dispositivo en el árbol del sistema (`/dev/...`).
* **MAJ:MIN:** Números de dispositivo mayor y menor (*Major:Minor*). El mayor identifica el tipo de controlador del kernel y el menor diferencia cada partición o volumen individual.
* **RM (Removable):** Indica si el dispositivo es extraíble (`1` para Sí, `0` para No).
* **SIZE:** Tamaño total de almacenamiento del dispositivo o partición.
* **RO (Read-Only):** Indica si el medio es de solo lectura (`1` para Sí, `0` para lectura y escritura).
* **TYPE:** Tipo de dispositivo de bloque (`disk` = disco físico/virtual, `part` = partición, `loop` = archivo montado como bloque, `rom` = CD/DVD).
* **MOUNTPOINTS:** Punto de montaje del sistema de archivos dentro de la jerarquía de directorios de Linux.

## Memoria y Sistema

### lsmem

El comando `lsmem` lista el estado de los bloques de memoria RAM física asignados al sistema operativo, detallando cómo los organiza el kernel de Linux.

![alt text](<Screenshot 2026-08-17 114220.png>)

**Columnas de la Tabla Principal**

* **RANGE:** Muestra el rango de direcciones de memoria física en formato hexadecimal (`0x0000000000000000 - 0x00000000bfffffff`), que abarca desde la dirección inicial $0$ hasta el límite asignado para completar los 3 GB.
* **SIZE (3G):** Cantidad de memoria contenida dentro de este rango específico (3 Gigabytes).
* **STATE (online):** Estado de la memoria. `online` significa que el kernel la reconoce, la ha activado y está completamente disponible para su uso.
* **REMOVABLE (yes):** Indica si el rango de memoria admite desconexión o extracción en caliente (*hot-unplug*). Al estar en un entorno virtualizado, los bloques pueden marcarse como removibles para la gestión dinámica de RAM.
* **BLOCK (0-23):** Identifica el rango numérico de los bloques de memoria asignados. Va del bloque $0$ al bloque $23$, lo que da un total de 24 bloques continuos ($24 \times 128\text{ MB} = 3072\text{ MB} = 3\text{ GB}$).


### sudo lshw

El comando `sudo lshw` (List Hardware) muestra una descripción detallada de toda la configuración de hardware de la máquina, organizada en una estructura jerárquica de árbol. Al ejecutarlo con `sudo`, obtiene acceso a la información completa de la BIOS/firmware y componentes que de otro modo estarían protegidos.

![alt text](<Screenshot 2026-08-17 114349.png>)

![alt text](<Screenshot 2026-08-17 114422.png>)

![alt text](<Screenshot 2026-08-17 124006.png>)

![alt text](<Screenshot 2026-08-17 124151.png>)

![alt text](<Screenshot 2026-08-17 124223.png>)

![alt text](<Screenshot 2026-08-17 124310.png>)

![alt text](<Screenshot 2026-08-17 124415.png>)

![alt text](<Screenshot 2026-08-17 124504.png>)

![alt text](<Screenshot 2026-08-17 124548.png>)

![alt text](<Screenshot 2026-08-17 124641.png>)

![alt text](<Screenshot 2026-08-17 124707.png>)

**Estructura General de Salida**

El comando organiza la información mediante niveles de sangría y nodos principales:

* **Node (Nodo):** Representa una sección o componente específico del sistema (ej. `*-core`, `*-memory`, `*-display`, `*-network`).
* **description:** Breve resumen del tipo de dispositivo.
* **product:** Modelo exacto o nombre comercial del componente.
* **vendor:** Empresa fabricante del dispositivo.
* **physical id:** Identificación del zócalo, bus o puerto físico donde está conectado.
* **bus info:** Dirección exacta de la barra de bus (PCI, USB, etc.) a la que está enlazado.
* **logical name:** Nombre con el que el sistema operativo identifica al dispositivo (ej. `eth0`, `sda`, `/dev/cdrom`).
* **version / serial:** Versión del firmware/revisión y número de serie único.
* **capacity / size:** Capacidad máxima soportada / capacidad actual configurada.
* **capabilities:** Funcionalidades avanzadas soportadas por el hardware (ej. `boot`, `pm`, `gigabit`).
* **configuration:** Parámetros operativos actuales (drivers cargados, IP, velocidad de reloj, estado, etc.).


**Nodos Principales que Desglosa el Comando**

* **`*-core` (Placa Base y Bus Principal):** Muestra el chasis virtual, placa madre emulada (ej. Oracle Corporation) y la versión de la BIOS virtual.
* **`*-firmware`:** Información sobre el firmware EFI/BIOS del sistema.
* **`*-cpu`:** Especificaciones completas del procesador (arquitectura, frecuencia, hilos y extensiones).
* **`*-memory`:** Detalle de los zócalos de memoria RAM, velocidad soportada y los módulos instalados.
* **`*-pci` / `*-ide` / `*-sata`:** Controladores de bus de comunicación del sistema.
* **`*-display`:** Adaptador gráfico, memoria de video asignada y controlador en uso (`driver=vboxvideo` o `vmwgfx`).
* **`*-network`:** Interfaces de red físicas y virtuales, mostrando direcciones MAC, estado del enlace (`link=yes`), velocidad configurada y dirección IP asignada.
* **`*-storage` / `*-disk`:** Discos duros, controladores AHCI/SATA y unidades ópticas con sus respectivos nombres lógicos (`/dev/sda`).