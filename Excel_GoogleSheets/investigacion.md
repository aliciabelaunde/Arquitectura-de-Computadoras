# Investigación: Simulación de Lanzamiento de Dados y Probabilidad (Método de Montecarlo) en Excel / Google Sheets

## 1. Introducción

La simulación de procesos aleatorios permite evaluar eventos de la vida real mediante modelos matemáticos. Un ejemplo sencillo y práctico en hojas de cálculo es la simulación del **lanzamiento de dos dados** para calcular la probabilidad empírica de obtener una suma específica (por ejemplo, sumar 7) comparada con su probabilidad teórica.

## 2. Marco Teórico

Al lanzar dos dados de 6 caras, existen $36$ combinaciones posibles ($6 \times 6$). La probabilidad teórica de obtener una suma determinada se calcula dividiendo el número de combinaciones favorables entre las 36 totales.

* **Suma de 7 (Caso más probable):** Ocurre con 6 combinaciones: (1,6), (2,5), (3,4), (4,3), (5,2), (6,1).

$$\text{Probabilidad Teórica} = \frac{6}{36} = 16.67\%$$



Mediante el **Método de Montecarlo**, se simulan miles de lanzamientos aleatorios. Según la Ley de los Grandes Números, a mayor cantidad de simulación de tiradas, la frecuencia relativa obtenida en la hoja de cálculo se acercará más al $16.67\%$.

## 3. Guía Paso a Paso para Construir la Simulación

### Estructura de la Hoja de Trabajo

Diseña una tabla con las siguientes columnas desde la celda **A1**:

| Celda/Columna | Encabezado | Fómula a ingresar | Descripción |
| --- | --- | --- | --- |
| **Columna A** | `N° Tirada` | Ingrese números del `1` al `1000` | Representa cada experimento individual. |
| **Columna B** | `Dado 1` | `=ALEATORIO.ENTRE(1; 6)` | Genera un valor entero aleatorio entre 1 y 6. |
| **Columna C** | `Dado 2` | `=ALEATORIO.ENTRE(1; 6)` | Genera el valor del segundo dado. |
| **Columna D** | `Suma` | `=B2 + C2` | Arrastre la fórmula hacia abajo hasta la fila 1001. |


## 4. Análisis de Resultados y Fórmulas

En una sección separada de la hoja (por ejemplo, en las celdas **F1:G4**), crea el panel de resultados:

* **Total de Simulaciones:**
`=CONTAR(D2:D1001)` *(Resultado: 1000)*
* **Veces que salió el 7:**
`=CONTAR.SI(D2:D1001; 7)`
* **Probabilidad Empírica (Simulada):**
`=CONTAR.SI(D2:D1001; 7) / CONTAR(D2:D1001)` *(Cambiar formato de celda a Porcentaje)*
* **Probabilidad Teórica:**
`=6/36` *(Formato de porcentaje: 16.67%)*

## 5. Conclusiones de la Investigación

1. **Funcionalidad:** Las funciones `=ALEATORIO.ENTRE()` convierten a Excel y Google Sheets en herramientas de modelado probabilístico accesibles sin necesidad de programar en código avanzado.
2. **Resultado del Experimento:** Al presionar la tecla `F9` (en Excel) o editar cualquier celda (en Google Sheets), la simulación recalculará automáticamente las 1,000 tiradas, mostrando cómo la probabilidad simulada fluctúa siempre alrededor del valor teórico ($16.67\%$).
