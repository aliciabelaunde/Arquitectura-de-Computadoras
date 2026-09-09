# Investigación: Simulación de Lanzamiento de Dados y Probabilidad mediante Montecarlo en Excel

## 1. Introducción

La simulación de procesos aleatorios permite estudiar situaciones de la vida real mediante modelos matemáticos y computacionales. Una aplicación sencilla de este método consiste en simular el lanzamiento de dos dados y analizar la frecuencia con la que se obtiene una determinada suma.

En este trabajo se utilizará el **método de Montecarlo**, que consiste en realizar una gran cantidad de experimentos aleatorios para aproximar la probabilidad de que ocurra un determinado evento.

Como ejemplo, se estudiará la probabilidad de obtener una **suma igual a 7 al lanzar dos dados de seis caras**.

La simulación se realizará utilizando **Microsoft Excel y programación en VBA**, de manera que el programa pueda generar automáticamente los lanzamientos, calcular las sumas y determinar la probabilidad obtenida experimentalmente.


# 2. Marco teórico

## 2.1. Lanzamiento de dos dados

Cada dado tiene seis posibles resultados:

$$
1,2,3,4,5,6
$$

Al lanzar dos dados existen:

$$
6 \times 6 = 36
$$

combinaciones posibles.

Para obtener una suma de 7 existen las siguientes combinaciones:

* (1,6)
* (2,5)
* (3,4)
* (4,3)
* (5,2)
* (6,1)

Por lo tanto, existen **6 resultados favorables** de un total de 36 resultados posibles.

La probabilidad teórica de obtener una suma de 7 es:

$$
P(7)=\frac{6}{36}
$$

$$
P(7)=\frac{1}{6}
$$

$$
P(7)\approx16.67\%
$$

Por lo tanto, la probabilidad teórica de obtener una suma de 7 al lanzar dos dados es aproximadamente **16,67 %**.


# 3. Método de Montecarlo

El método de Montecarlo utiliza experimentos aleatorios repetidos para aproximar resultados matemáticos.

En este caso se realizarán **1.000 lanzamientos simulados de dos dados**.

En cada lanzamiento:

1. Se genera aleatoriamente el resultado del dado 1.
2. Se genera aleatoriamente el resultado del dado 2.
3. Se calcula la suma de ambos dados.
4. Se verifica si la suma es igual a 7.
5. Se cuenta la cantidad de veces que aparece el resultado 7.
6. Se calcula la probabilidad empírica.

La probabilidad empírica se obtiene mediante:

$$
P_{empírica}=
\frac{\text{Cantidad de veces que salió 7}}
{\text{Cantidad total de simulaciones}}
$$

Por ejemplo, si después de 1.000 lanzamientos el número 7 aparece 168 veces:

$$
P_{empírica}=\frac{168}{1000}=0.168
$$

Por lo tanto:

$$
P_{empírica}=16.8\%
$$

Este resultado se encuentra muy cerca de la probabilidad teórica de 16,67 %.


# 4. Creación de la simulación en Excel

## 4.1. Crear el archivo

Primero se debe abrir Microsoft Excel.

Crear un libro nuevo y guardar el archivo utilizando el formato:

**Libro de Excel habilitado para macros (*.xlsm)**

Esto es importante porque el programa utilizará código VBA.


# 5. Preparar la hoja de Excel

En la primera hoja del libro se debe crear la siguiente estructura.

| Celda | Contenido             |
| ----- | --------------------- |
| A1    | N° Tirada             |
| B1    | Dado 1                |
| C1    | Dado 2                |
| D1    | Suma                  |
| F1    | RESULTADOS            |
| F2    | Total de simulaciones |
| F3    | Veces que salió 7     |
| F4    | Probabilidad empírica |
| F5    | Probabilidad teórica  |

La tabla principal tendrá cuatro columnas:

| N° Tirada | Dado 1 | Dado 2 | Suma |
| --------: | -----: | -----: | ---: |
|         1 |      4 |      2 |    6 |
|         2 |      3 |      4 |    7 |
|         3 |      6 |      1 |    7 |
|         4 |      2 |      5 |    7 |
|       ... |    ... |    ... |  ... |
|      1000 |      5 |      3 |    8 |

Los valores de los dados serán generados automáticamente mediante VBA.


# 6. Abrir el editor de VBA

Para comenzar a programar la simulación:

### Paso 1

Abrir el archivo de Excel.

### Paso 2

Presionar:

**Alt +  Fn + F11**

Esto abrirá el **Editor de Visual Basic para Aplicaciones (VBA)**.

### Paso 3

En la parte superior seleccionar:

**Insertar → Módulo**

Se abrirá una ventana donde se puede escribir el código.


# 7. Código VBA de la simulación

Copiar y pegar el siguiente código dentro del módulo:

```vb
Sub SimularDados()

    Dim i As Integer
    Dim dado1 As Integer
    Dim dado2 As Integer
    Dim suma As Integer
    Dim contador7 As Integer
    Dim total As Integer
    Dim probEmpirica As Double
    Dim probTeorica As Double

    'Cantidad de simulaciones
    total = 1000

    'Limpiar datos anteriores
    Range("A2:D1001").ClearContents

    'Encabezados
    Range("A1").Value = "N° Tirada"
    Range("B1").Value = "Dado 1"
    Range("C1").Value = "Dado 2"
    Range("D1").Value = "Suma"

    'Inicializar contador
    contador7 = 0

    'Realizar las simulaciones
    For i = 1 To total

        'Generar valores aleatorios de los dados
        dado1 = Int(Rnd() * 6) + 1
        dado2 = Int(Rnd() * 6) + 1

        'Calcular la suma
        suma = dado1 + dado2

        'Guardar los resultados
        Cells(i + 1, 1).Value = i
        Cells(i + 1, 2).Value = dado1
        Cells(i + 1, 3).Value = dado2
        Cells(i + 1, 4).Value = suma

        'Verificar si la suma es 7
        If suma = 7 Then
            contador7 = contador7 + 1
        End If

    Next i

    'Calcular probabilidades
    probEmpirica = contador7 / total
    probTeorica = 6 / 36

    'Crear panel de resultados
    Range("F1").Value = "RESULTADOS"
    Range("F2").Value = "Total de simulaciones"
    Range("G2").Value = total

    Range("F3").Value = "Veces que salió 7"
    Range("G3").Value = contador7

    Range("F4").Value = "Probabilidad empírica"
    Range("G4").Value = probEmpirica
    Range("G4").NumberFormat = "0.00%"

    Range("F5").Value = "Probabilidad teórica"
    Range("G5").Value = probTeorica
    Range("G5").NumberFormat = "0.00%"

    'Aplicar formato
    Range("A1:D1").Font.Bold = True
    Range("F1:G1").Font.Bold = True

    Columns("A:G").AutoFit

    'Mostrar resumen
    MsgBox "Simulación completada." & vbCrLf & _
           "Se realizaron " & total & " lanzamientos." & vbCrLf & _
           "El 7 apareció " & contador7 & " veces." & vbCrLf & _
           "Probabilidad empírica: " & Format(probEmpirica, "0.00%") & vbCrLf & _
           "Probabilidad teórica: " & Format(probTeorica, "0.00%"), _
           vbInformation, "Simulación de Montecarlo"

End Sub
```


# 8. Explicación del código

## 8.1. Definición de variables

El programa comienza definiendo las variables necesarias:

```vb
Dim i As Integer
Dim dado1 As Integer
Dim dado2 As Integer
Dim suma As Integer
Dim contador7 As Integer
Dim total As Integer
```

Estas variables permiten almacenar:

* El número de la tirada.
* El resultado del primer dado.
* El resultado del segundo dado.
* La suma de los dados.
* La cantidad de veces que aparece el 7.
* El número total de simulaciones.


# 9. Cantidad de simulaciones

La siguiente instrucción establece que se realizarán 1.000 experimentos:

```vb
total = 1000
```

Esto significa que el programa realizará automáticamente 1.000 lanzamientos de dos dados.


# 10. Generación de los dados

Para generar números aleatorios entre 1 y 6 se utiliza:

```vb
dado1 = Int(Rnd() * 6) + 1
dado2 = Int(Rnd() * 6) + 1
```

La función `Rnd()` genera un número aleatorio.

La expresión:

```vb
Int(Rnd() * 6) + 1
```

permite obtener un número entero entre:

$$
1 \leq dado \leq 6
$$

De esta manera se simula el lanzamiento de un dado de seis caras.


# 11. Cálculo de la suma

Después de generar los dos dados, se calcula su suma:

```vb
suma = dado1 + dado2
```

Por ejemplo:

```text
Dado 1 = 3
Dado 2 = 4

Suma = 3 + 4

Suma = 7
```

# 12. Guardar los resultados en Excel

El programa coloca automáticamente los resultados en las columnas correspondientes:

```vb
Cells(i + 1, 1).Value = i
Cells(i + 1, 2).Value = dado1
Cells(i + 1, 3).Value = dado2
Cells(i + 1, 4).Value = suma
```

Por ejemplo:

| N° Tirada | Dado 1 | Dado 2 | Suma |
| --------: | -----: | -----: | ---: |
|         1 |      2 |      5 |    7 |
|         2 |      6 |      3 |    9 |
|         3 |      1 |      2 |    3 |
|         4 |      4 |      3 |    7 |
|         5 |      5 |      5 |   10 |


# 13. Contar las veces que aparece 7

El programa verifica cada resultado mediante:

```vb
If suma = 7 Then
    contador7 = contador7 + 1
End If
```

Cuando la suma es igual a 7, el contador aumenta en uno.

Por ejemplo:

```text
Tirada 1 → 5
Tirada 2 → 7 → contador = 1
Tirada 3 → 9
Tirada 4 → 7 → contador = 2
```

Al finalizar las 1.000 tiradas se obtiene el número total de veces que apareció el 7.

# 14. Cálculo de la probabilidad empírica

La probabilidad simulada se calcula mediante:

```vb
probEmpirica = contador7 / total
```

Por ejemplo, si el resultado fuera:

```text
Veces que salió 7 = 167
Total de simulaciones = 1000
```

Entonces:

$$
P_{empírica}=\frac{167}{1000}
$$

$$
P_{empírica}=0.167
$$

o:

$$
P_{empírica}=16.70\%
$$

---

# 15. Cálculo de la probabilidad teórica

La probabilidad teórica se establece mediante:

```vb
probTeorica = 6 / 36
```

El resultado es:

$$
P_{teórica}=0.1667
$$

o aproximadamente:

$$
P_{teórica}=16.67\%
$$


# 16. Ejecutar el programa

Una vez pegado el código:

### Paso 1

Cerrar el editor de VBA o regresar a Excel.

### Paso 2

Presionar:

**Alt + F8**

### Paso 3

Seleccionar:

**SimularDados**

### Paso 4

Presionar:

**Ejecutar**

Excel realizará automáticamente las 1.000 simulaciones.

Al finalizar aparecerá una ventana con un resumen similar a:

```text
Simulación completada.

Se realizaron 1000 lanzamientos.
El 7 apareció 169 veces.
Probabilidad empírica: 16.90%
Probabilidad teórica: 16.67%
```

El número exacto cambiará cada vez que se ejecute la simulación porque los resultados son aleatorios.


# 17. Crear un botón para ejecutar la simulación

Para hacer que el proyecto sea más interactivo se puede agregar un botón.

### Paso 1

Regresar a Excel.

### Paso 2

Activar la pestaña:

**Desarrollador**

Si no aparece:

**Archivo → Opciones → Personalizar cinta de opciones → activar "Desarrollador"**

### Paso 3

Seleccionar:

**Desarrollador → Insertar → Botón (Control de formulario)**

### Paso 4

Dibujar el botón sobre la hoja.

Excel preguntará qué macro se desea asignar.

Seleccionar:

**SimularDados**

### Paso 5

Cambiar el texto del botón por:

**SIMULAR 1000 LANZAMIENTOS**

Ahora la simulación podrá ejecutarse simplemente presionando el botón.

# 18. Ejemplo de resultados

Una ejecución podría producir los siguientes resultados:

| Indicador             | Resultado |
| --------------------- | --------: |
| Total de simulaciones |      1000 |
| Veces que salió 7     |       172 |
| Probabilidad empírica |   17,20 % |
| Probabilidad teórica  |   16,67 % |

En otra ejecución los resultados podrían ser diferentes:

| Indicador             | Resultado |
| --------------------- | --------: |
| Total de simulaciones |      1000 |
| Veces que salió 7     |       161 |
| Probabilidad empírica |   16,10 % |
| Probabilidad teórica  |   16,67 % |

Esto ocurre porque cada simulación utiliza números aleatorios.

---

# 19. Comparación entre probabilidad teórica y empírica

La probabilidad teórica de obtener una suma de 7 es:

$$
16.67\%
$$

La probabilidad empírica depende de los resultados obtenidos en la simulación.

Por ejemplo:

$$
P_{empírica}=17.20\%
$$

La diferencia entre ambas sería:

$$
17.20\%-16.67\%=0.53\%
$$

Mientras mayor sea la cantidad de simulaciones, generalmente la probabilidad empírica se acercará más a la probabilidad teórica.

Esto representa la **Ley de los Grandes Números**.

---

# 20. ¿Por qué funciona el método de Montecarlo?

El método de Montecarlo se basa en realizar una gran cantidad de experimentos aleatorios.

En este caso:

```text
1 lanzamiento
        ↓
2 dados
        ↓
Calcular suma
        ↓
¿La suma es 7?
        ↓
Contar resultado
        ↓
Repetir 1000 veces
        ↓
Calcular probabilidad
```

Si se realizan pocas simulaciones, el resultado puede alejarse bastante del valor teórico.

Si se realizan muchas simulaciones, el resultado tiende a aproximarse al valor teórico.

Por ejemplo:

| Simulaciones | Probabilidad simulada |
| -----------: | --------------------: |
|           10 |               20,00 % |
|          100 |               15,00 % |
|        1.000 |               16,70 % |
|       10.000 |               16,59 % |
|      100.000 |               16,68 % |

Estos valores son únicamente ejemplos. Los resultados reales cambiarán debido a la aleatoriedad.

---

# 21. Conclusiones

1. El lanzamiento de dos dados tiene **36 combinaciones posibles**.

2. Existen **6 combinaciones cuya suma es 7**.

3. Por lo tanto, la probabilidad teórica de obtener 7 es:

$$
\frac{6}{36}=16.67\%
$$

4. Mediante VBA es posible automatizar miles de lanzamientos de dados dentro de Excel.

5. La simulación permite calcular una **probabilidad empírica** a partir de los resultados obtenidos.

6. La probabilidad empírica puede variar en cada ejecución debido a la naturaleza aleatoria del experimento.

7. Al aumentar el número de simulaciones, la probabilidad empírica tiende a acercarse a la probabilidad teórica.

8. El experimento demuestra de manera práctica el funcionamiento del **método de Montecarlo** y la **Ley de los Grandes Números**.

9. Excel, mediante VBA, permite implementar modelos probabilísticos sin necesidad de utilizar un lenguaje de programación externo.

---

# 22. Resultado final esperado

Al finalizar el proyecto, la hoja de Excel debe tener una estructura similar a:

```text
┌──────────┬─────────┬─────────┬────────┐       ┌────────────────────────┐
│ N° Tirada│ Dado 1  │ Dado 2  │  Suma  │       │       RESULTADOS        │
├──────────┼─────────┼─────────┼────────┤       ├────────────────────────┤
│    1     │    4    │    3    │   7    │       │ Total simulaciones 1000│
│    2     │    2    │    5    │   7    │       │ Veces que salió 7   167│
│    3     │    6    │    2    │   8    │       │ Prob. empírica     16.7%│
│    4     │    1    │    4    │   5    │       │ Prob. teórica      16.67%│
│   ...    │   ...   │   ...   │  ...   │       └────────────────────────┘
│  1000    │    5    │    2    │   7    │
└──────────┴─────────┴─────────┴────────┘

             [ SIMULAR 1000 LANZAMIENTOS ]
```

De esta forma, el proyecto pasa de ser solamente una hoja con fórmulas a una **simulación programada en Excel mediante VBA**, donde el usuario puede ejecutar el experimento automáticamente y observar los resultados.
