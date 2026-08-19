# Práctica: Sistemas Numéricos y Aritmética Binaria

- **Materia:** Arquitectura de Computadoras — Ingeniería de Software
- **Estudiante:** Maria Alicia Belaunde Villagomez
- **Entorno:** Ubuntu Linux (partes de script/verificación)

 
## Nivel 1 — Conversión de bases
 
### 1.1. Convierte los siguientes números decimales a binario: 45, 128, 255, 1000 
| Decimal | Binario |
|---|---:|
| `45` | 101101 |
| `128` | 10000000 |
| `255` | 11111111 |
| `1000` | 1111101000 |

### 1.2. Convierte los siguientes números binarios a decimal: 1011, 10110110, 11111111, 100000000 
| Binario | Descomposición  | Decimal |
|---|---|---:|
| `10111` | 8+2+1 | `11` |
| `10110110`  | 128 + 32 + 16 + 4 + 2 | `182` |
| `11111111`  | 128+64+32+16+8+4+2+1 | `255` |
| `100000000` | 2⁸ | `256` |

### 1.3. Convierte a hexadecimal los siguientes números binarios: 10101100, 111100001111, 1010101010101010

```
Decimal     Hexadecimal
   0             0
   1             1
   2             2
   3             3
   4             4
   5             5
   6             6
   7             7
   8             8
   9             9
  10             A
  11             B
  12             C
  13             D
  14             E
  15             F
  ```

| Binario | Agrupado (4 bits) | Hex |
|---------|-------------------|-----|
| `10101100`         | `1010` `1100`               | `AC` |
| `111100001111`     | `1111` `0000` `1111`        | `F0F` |
| `1010101010101010` | `1010` `1010` `1010` `1010` | `AAAA` |

### 1.4. Convierte de octal a decimal: 17, 254, 777 
| Octal | Cálculo | Decimal |
|-------|---------|--------:|
| `17`  | 1·8 + 7 | 15 |
| `254` | 2·64 + 5·8 + 4 | 172 |
| `777` | 7·64 + 7·8 + 7 | 511 |


## Nivel 2 — Aritmética binaria básica 
 
### 2.1. Realiza las siguientes sumas binarias (muestra el acarreo): 1011 + 0110 , 11101 + 01011 

**Reglas principales:**
```
0 + 0 = 0
0 + 1 = 1
1 + 0 = 1
1 + 1 = 10  ← escribes 0 y llevas 1
1 + 1 + 1 = 11 ← escribes 1 y llevas 1
```

**1011 + 0110** (11 + 6 = 17)
```
  acarreos: 1 1 1

            1 0 1 1
          + 0 1 1 0
          ---------
          1 0 0 0 1   = 17
```
**11101 + 01011** (29 + 11 = 40)
```
  acarreos: 1 1 1 1  
  
            1 1 1 0 1
          + 0 1 0 1 1
          ------------
          1 0 1 0 0 0
```

### 2.2. Realiza las siguientes restas binarias usando préstamo (borrow): 1100 - 0101, 10000 - 00111 

**Las reglas básicas son:**
```
0 - 0 = 0
1 - 0 = 1
1 - 1 = 0
0 - 1 = no se puede → pedimos prestado
```

Cuando tenemos 0 - 1, pedimos 1 a la columna de la izquierda:

**1100 − 0101** (12 − 5 = 7)
```

          1 1 0 0
        - 0 1 0 1
        ---------
          0 1 1 1   = 7
```

**10000 − 00111** (16 − 7 = 9)
```
          1 0 0 0 0
        - 0 0 1 1 1
        -----------
          0 1 0 0 1   = 9
```

### 2.3. Multiplica en binario: 1011 × 0101

**1011 × 0101** (11 × 5 = 55)
```
              1 0 1 1
            × 0 1 0 1
            ---------
              1 0 1 1     (× 1, bit 0)
            0 0 0 0       (× 0, bit 1)
          1 0 1 1         (× 1, bit 2)
        0 0 0 0           (× 0, bit 3)
        ---------------
          1 1 0 1 1 1     = 55
```
## Nivel 3 — Complemento a dos 

### 3.1. Representa los siguientes números decimales en complemento a dos usando 8 bits: -45, -1, -128, 27 
Receta para negativos: escribir el positivo en binario → **invertir** todos los bits → **sumar 1**.

Esto quiere decir invertir: 
```
0 → 1
1 → 0
```

| Decimal | Procedimiento | C2 (8 bits) |
|--------:|---------------|-------------|
| −45  | 45 = `00101101` → invertir `11010010` → +1 | `11010011` |
| −1   | 1 = `00000001` → invertir `11111110` → +1 | `11111111` |
| −128 | caso límite (el más negativo representable) | `10000000` |
| 27   | positivo, conversión directa | `00011011` |

```
Con 8 bits, el rango es:

-128 → +127

Por lo tanto, -128 es el número negativo más pequeño que podemos representar.

Los números positivos simplemente se representan en binario normal, rellenando hasta 8 bits.
```

### 3.2. Dado el número en complemento a dos de 8 bits 11010110, indica su valor decimal. 

```
  11010110
  ↑
  1 -> si el primer bit es 1 quiere decir que es negativo
```

Invertimos:
  **00101001**

Y sumamos un 1:
  ```
      00101001
    + 00000001
    -----------
      00101010
```
```
  0   0   1   0  1  0  1  0
  ↑   ↑   ↑   ↑  ↑  ↑  ↑  ↑  
128  64  32  16  8  4  2  1
```
32+8+2 = 42

Por lo tanto el valor es **−42**.

### 3.3. Realiza la resta 45 - 60 usando complemento a dos con registros de 8 bits, y verifica el resultado.

Se calcula como 45 + (−60):
 
- 45 = `00101101`
- −60: 60 = `00111100` → invertir `11000011` → +1 = `11000100`

```
    0 0 1 0 1 1 0 1     (  45)
  + 1 1 0 0 0 1 0 0     ( −60)
  -----------------
    1 1 1 1 0 0 0 1
```
 
Resultado `11110001`. Como el bit de signo es 1, es negativo:
invertir + 1 → `00001111` = 15 → valor = **−15**.
 
Verificación: 45 − 60 = −15. 

## Nivel 4 — Desbordamiento (overflow) y banderas 

### 4.1. Determina si ocurre overflow al sumar, en complemento a dos de 8 bits: 01111111 + 00000001 10000000 + 11111111 

El rango que podemos representar es:

**-128 hasta +127**

La regla importante es:

```
Hay overflow cuando el resultado matemático necesita un número que no puede representarse con los bits disponibles.
```

**01111111 + 00000001** (127 + 1)
```
    0 1 1 1 1 1 1 1     ( 127, positivo)
  + 0 0 0 0 0 0 0 1     (   1, positivo)
  -----------------
    1 0 0 0 0 0 0 0     (−128, negativo)
```
Pero matemáticamente:

```127 + 1 = 128```

Dos positivos → resultado negativo. **SÍ hay overflow.** 
 
**10000000 + 11111111** (−128 + (−1))
```
    1 0 0 0 0 0 0 0     (−128, negativo)
  + 1 1 1 1 1 1 1 1     (  −1, negativo)
  -----------------
  1 0 1 1 1 1 1 1 1 --> Tenemos un 1 extra a la izquierda. En 8 bits lo descartamos:
    └ resultado 8 bits: 0 1 1 1 1 1 1 1 (127, positivo), carry out = 1
```

```Pero esperábamos -129.```

Dos negativos → resultado positivo. **SÍ hay overflow.** 

### 4.2. Explica, con tus propias palabras, la diferencia entre carry (acarreo) y overflow en una suma con signo, y da un ejemplo de cada caso usando registros de 4 bits.

**Carry (acarreo)**
El carry ocurre cuando una suma genera un bit adicional que sale por la izquierda del registro.

Por ejemplo, usando registros de 4 bits:
```
  1111
+ 0001
------
1 0000
```

El resultado necesita 5 bits:

```
1 0000
↑
carry
```

Como el registro solamente tiene 4 bits, nos quedamos con:

```0000```

Y tenemos: ``` Carry = 1```

**Overflow**
El overflow ocurre cuando estamos trabajando con números con signo y el resultado no puede representarse en la cantidad de bits disponible.

Con 4 bits en complemento a dos, el rango es:

```-8 hasta +7```

Ejemplo:

```
  0111
+ 0001
------
  1000
```

Convertimos:

- 0111 = +7
- 0001 = +1

Matemáticamente:

```7 + 1 = 8```

Pero +8 no se puede representar con 4 bits, porque el máximo es +7.

El resultado obtenido es: ```1000 = -8```

Por lo tanto: ```Overflow = 1 ```

### 4.3 (práctico en Ubuntu) Escribe un programa en C que sume dos enteros int8_t propensos a overflow (por ejemplo 120 + 20), compílalo con gcc, ejecútalo, y explica por qué el resultado impreso no es el esperado matemáticamente. Adjunta el comando de compilación y la salida. 

Archivo `overflow.c`:
```c
#include <stdio.h>
#include <stdint.h>
 
int main(void) {
    int8_t a = 120;
    int8_t b = 20;
    int8_t suma = a + b;   /* 120 + 20 = 140, pero int8_t solo llega a 127 */
 
    printf("a          = %d\n", a);
    printf("b          = %d\n", b);
    printf("a + b real = %d\n", 120 + 20);      /* aritmetica en int: 140 */
    printf("suma int8_t= %d\n", suma);          /* valor truncado a 8 bits */
    return 0;
}
```
 
Compilación y ejecución:
```bash
gcc overflow.c -o overflow
./overflow
```
 
Salida obtenida:
```
a          = 120
b          = 20
a + b real = 140
suma int8_t= -116
```

## Nivel 5 — Punto flotante (IEEE 754) 
### 5.1. Representa el número decimal 10.25 en formato IEEE 754 de precisión simple (32 bits), mostrando signo, exponente y mantisa por separado. 

La computadora guarda un número real en 32 bits repartidos así:

```
[ 1 bit ][   8 bits   ][        23 bits        ]
  signo    exponente            mantisa
```

Es notación científica pero en binario. Igual que en decimal escribís 10.25 como 1.025 × 10¹, en binario se escribe como 1.algo × 2^algo. Los tres campos guardan justamente esas tres piezas: el signo, el exponente (la potencia de 2) y la mantisa (los decimales después del 1.).

**Paso 1: pasar 10.25 a binario.**
Se separa parte entera y parte decimal.

- Entera: 10 = 1010
- Decimal: 0.25. Esto se hace multiplicando por 2 y anotando el acarreo entero:
```
0.25 × 2 = 0.5 → primer bit 0
0.5 × 2 = 1.0 → segundo bit 1
Parte decimal sobrante: 0.0 
llegó a 0, paramos → 0.01
```

Entonces ```10.25 = 1010.01``` en binario.

**Paso 2: normalizar (correr la coma hasta que quede un solo 1 a la izquierda).**

```1010.01  →  1.01001 × 2³```

- **Signo =** 0 (es positivo). Si fuera negativo sería 1.
- **Exponente =** acá está el truco. No se guarda el 3 directo, se guarda 3 + 127 = 130. Ese 127 se llama bias (sesgo) y sirve para poder representar exponentes negativos sin usar otro bit de signo. 130 en binario = 10000010.
- **Mantisa =** lo que queda después del 1., o sea 01001. El 1. de adelante no se guarda (es implícito, siempre está). Rellenás con ceros hasta llegar a 23 bits: 01001000000000000000000.

**Resultado:**

`` 0   10000010   01001000000000000000000 ``

### 5.2. Dado el patrón de bits IEEE 754 de 32 bits 1 10000010 01100000000000000000000, calcula su valor decimal. 
- **Signo** = 1 → negativo
- **Exponente** = `10000010` = 130 → 130 − 127 = 3
- **Mantisa** = `1.011` = 1 + 0.25 + 0.125 = 1.375
Valor = −1.375 × 2³ = −1.375 × 8 = **−11.0**
### 5.3. Explica qué es la pérdida de precisión en punto flotante y demuéstralo con un ejemplo numérico (por ejemplo, sumar 0.1 + 0.2 en punto flotante).
Muchos decimales "sencillos" no tienen representación **exacta** en binario. Por ejemplo, 0.1 en binario es `0.00011001100110011…` (periódico infinito); al guardarse en 32/64 bits se **redondea**. Lo mismo pasa con 0.2. Al sumarlos, los pequeños errores de redondeo se acumulan.
 
Demostración en Python:
```python
>>> 0.1 + 0.2
0.30000000000000004
>>> 0.1 + 0.2 == 0.3
False
```
El resultado no es exactamente 0.3. Por eso en programación **nunca** se comparan flotantes con `==`; se usa una tolerancia (p. ej. `abs(a - b) < 1e-9`).

## Nivel 6 — Integración: script de verificación (el más difícil) 

### 6.1. (práctico en Ubuntu) Escribe un script en Python (o Bash) que: - - - - 
- Reciba un número entero decimal. 
- Imprima su representación en binario, octal y hexadecimal. 
- Imprima su representación en complemento a dos de 8, 16 y 32 bits (si aplica). 
- Indique si el número, al representarse en 8 bits con signo, produce overflow. 

Prueba el script con al menos 5 valores distintos, incluyendo un caso límite (por ejemplo 127, 128, -128, -129, 0), y adjunta las salidas obtenidas. 

Archivo `conversor.py`:
```python
#!/usr/bin/env python3
import sys
 
 
def complemento_a_dos(n: int, bits: int):
    """Representación en complemento a dos con 'bits' bits.
    Devuelve None si el número no cabe con signo en esa cantidad de bits."""
    limite_inf = -(2 ** (bits - 1))          # p. ej. -128 para 8 bits
    limite_sup = 2 ** (bits - 1) - 1          # p. ej.  127 para 8 bits
    if n < limite_inf or n > limite_sup:
        return None
    mascara = (1 << bits) - 1
    return format(n & mascara, f"0{bits}b")
 
 
def procesar(n: int) -> None:
    print(f"Número decimal: {n}")
    print(f"  Binario     : {bin(n)}")
    print(f"  Octal       : {oct(n)}")
    print(f"  Hexadecimal : {hex(n)}")
 
    for bits in (8, 16, 32):
        rep = complemento_a_dos(n, bits)
        if rep is None:
            print(f"  C2 {bits:>2} bits : NO CABE (fuera de rango con signo)")
        else:
            print(f"  C2 {bits:>2} bits : {rep}")
 
    if n < -128 or n > 127:
        print("  >> OVERFLOW en 8 bits con signo (rango válido: -128 a 127)")
    else:
        print("  >> Sin overflow en 8 bits con signo")
    print("-" * 48)
 
 
def main() -> None:
    if len(sys.argv) > 1:
        valores = [int(x) for x in sys.argv[1:]]
    else:
        valores = [127, 128, -128, -129, 0]   # incluye casos límite
    for v in valores:
        procesar(v)
 
 
if __name__ == "__main__":
    main()
```
 
Ejecución:
```bash
python3 conversor.py 127 128 -128 -129 0
```
 
Salida obtenida (5 valores, con casos límite):
```
Número decimal: 127
  Binario     : 0b1111111
  Octal       : 0o177
  Hexadecimal : 0x7f
  C2  8 bits : 01111111
  C2 16 bits : 0000000001111111
  C2 32 bits : 00000000000000000000000001111111
  >> Sin overflow en 8 bits con signo
------------------------------------------------
Número decimal: 128
  Binario     : 0b10000000
  Octal       : 0o200
  Hexadecimal : 0x80
  C2  8 bits : NO CABE (fuera de rango con signo)
  C2 16 bits : 0000000010000000
  C2 32 bits : 00000000000000000000000010000000
  >> OVERFLOW en 8 bits con signo (rango válido: -128 a 127)
------------------------------------------------
Número decimal: -128
  Binario     : -0b10000000
  Octal       : -0o200
  Hexadecimal : -0x80
  C2  8 bits : 10000000
  C2 16 bits : 1111111110000000
  C2 32 bits : 11111111111111111111111110000000
  >> Sin overflow en 8 bits con signo
------------------------------------------------
Número decimal: -129
  Binario     : -0b10000001
  Octal       : -0o201
  Hexadecimal : -0x81
  C2  8 bits : NO CABE (fuera de rango con signo)
  C2 16 bits : 1111111101111111
  C2 32 bits : 11111111111111111111111101111111
  >> OVERFLOW en 8 bits con signo (rango válido: -128 a 127)
------------------------------------------------
Número decimal: 0
  Binario     : 0b0
  Octal       : 0o0
  Hexadecimal : 0x0
  C2  8 bits : 00000000
  C2 16 bits : 0000000000000000
  C2 32 bits : 00000000000000000000000000000000
  >> Sin overflow en 8 bits con signo
------------------------------------------------
```
*Nota:* para números negativos, `bin()`/`oct()`/`hex()` de Python muestran el signo (`-0b…`), que es notación signo-magnitud. El complemento a dos real se muestra aparte en las líneas `C2 8/16/32 bits`.

### 6.2. A partir del resultado de tu script, redacta un párrafo explicando qué pasaría si un sensor de hardware reporta temperaturas como enteros de 8 bits con signo y se produce un overflow silencioso: ¿qué valor vería el sistema y por qué es peligroso en un contexto real (por ejemplo, un sistema embebido)? 
Supongamos un sensor que reporta temperaturas como enteros de 8 bits con signo (rango −128 a 127 °C). Si la temperatura real sube a 128 °C, el valor no cabe: el patrón de bits `10000000` se interpreta con signo como **−128 °C**. Es decir, ante un ambiente extremadamente caliente el sistema "vería" la temperatura más fría posible, un salto que además ocurre **sin error ni aviso** (overflow silencioso). En un sistema embebido —el control térmico de una batería, un horno industrial o un motor— esto es peligroso porque la lógica de seguridad tomaría exactamente la decisión contraria a la necesaria: en vez de activar el enfriamiento o cortar la alimentación al detectar sobrecalentamiento, podría interpretar que hace frío y seguir calentando, con riesgo de daño al equipo, incendio o falla catastrófica. Por eso en sistemas reales se eligen tipos con rango suficiente (p. ej. `int16_t`), se validan los límites del sensor y se activan las banderas de overflow del hardware en lugar de ignorarlas.