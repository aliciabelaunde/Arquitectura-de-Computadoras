# Simulación de Lanzamiento de Dados y Probabilidad en Excel

## 1. Objetivo

Crear una simulación en **Microsoft Excel utilizando VBA** para lanzar dos dados 1.000 veces, calcular sus sumas y determinar cuántas veces se obtiene una suma igual a 7.

La simulación utiliza el **método de Montecarlo**, que permite aproximar una probabilidad mediante muchos experimentos aleatorios.

La probabilidad teórica de obtener 7 con dos dados es:

$$P(7) = \frac{6}{36} = 16{,}67\%$$


## 2. Crear el archivo de Excel

1. Abrir Microsoft Excel.
2. Crear un libro nuevo.
3. Guardarlo como **Libro de Excel habilitado para macros (*.xlsm)**.

En la primera hoja crear los siguientes encabezados en la **Fila 1**:

| A | B | C | D |
| --- | --- | --- | --- |
| N° Tirada | Dado 1 | Dado 2 | Suma |

También crear un pequeño panel de resultados en las columnas **F y G**:

| F | G |
| --- | --- |
| **RESULTADOS** | |
| Total de simulaciones | |
| Veces que salió 7 | |
| Probabilidad empírica | |
| Probabilidad teórica | |


## 3. Crear el programa VBA

Presionar **Alt + Fn + F11** (o **Alt + F11**) para abrir el editor de VBA.

Luego seleccionar: **Insertar → Módulo** y copiar el siguiente código:

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

    total = 1000
    contador7 = 0

    ' Limpiar resultados anteriores
    Range("A2:D1001").ClearContents

    ' Inicializar aleatoriedad
    Randomize

    ' Realizar simulaciones
    For i = 1 To total

        dado1 = Int(Rnd() * 6) + 1
        dado2 = Int(Rnd() * 6) + 1

        suma = dado1 + dado2

        Cells(i + 1, 1).Value = i
        Cells(i + 1, 2).Value = dado1
        Cells(i + 1, 3).Value = dado2
        Cells(i + 1, 4).Value = suma

        If suma = 7 Then
            contador7 = contador7 + 1
        End If

    Next i

    ' Calcular probabilidades
    probEmpirica = contador7 / total
    probTeorica = 6 / 36

    ' Mostrar resultados
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

    ' Formato visual
    Range("A1:D1").Font.Bold = True
    Range("F1:G1").Font.Bold = True
    Columns("A:G").AutoFit

    MsgBox "Simulación completada." & vbCrLf & _
           "Lanzamientos: " & total & vbCrLf & _
           "Veces que salió 7: " & contador7 & vbCrLf & _
           "Probabilidad empírica: " & Format(probEmpirica, "0.00%") & vbCrLf & _
           "Probabilidad teórica: " & Format(probTeorica, "0.00%")

End Sub

```

## 4. ¿Cómo funciona?

El programa realiza automáticamente los siguientes pasos:

1. Genera un número aleatorio entre **1 y 6** para el primer dado.
2. Genera otro número entre **1 y 6** para el segundo dado.
3. Suma ambos resultados.
4. Guarda los datos en Excel.
5. Comprueba si la suma es **7**.
6. Cuenta cuántas veces aparece el 7.
7. Calcula la probabilidad obtenida.

La generación de los dados se realiza con:

```vb
dado1 = Int(Rnd() * 6) + 1
dado2 = Int(Rnd() * 6) + 1

```

## 5. Ejecutar la simulación

Para ejecutar el programa:

1. Regresar a Excel.
2. Presionar **Alt + Fn + F8** (o **Alt + F8**).
3. Seleccionar **SimularDados**.
4. Presionar **Ejecutar**.

Excel generará las **1.000 tiradas automáticamente**.

El resultado podría ser, por ejemplo:

| Resultado | Valor |
| --- | --- |
| Simulaciones | 1000 |
| Veces que salió 7 | 168 |
| Probabilidad empírica | 16,80 % |
| Probabilidad teórica | 16,67 % |

El resultado cambiará ligeramente cada vez que se ejecute la simulación.

## 6. Crear un botón

Para facilitar la ejecución:

1. Activar la pestaña **Desarrollador** (o *Programador*).
2. Seleccionar **Insertar → Botón (Control de formulario)**.
3. Dibujar el botón en la hoja.
4. Asignarle la macro **SimularDados**.
5. Cambiar el texto por: **SIMULAR 1000 LANZAMIENTOS**.

Así, el usuario podrá ejecutar todo el experimento presionando solamente el botón.


## 7. Resultado final

El proyecto debe permitir visualizar:

* Los **1.000 lanzamientos**.
* El resultado de cada dado.
* La suma de cada lanzamiento.
* La cantidad de veces que aparece el **7**.
* La **probabilidad empírica**.
* La **probabilidad teórica**.

De esta manera, se crea en Excel una **simulación de Montecarlo funcional mediante VBA**, que permite comprobar experimentalmente que, al aumentar la cantidad de lanzamientos, la probabilidad obtenida tiende a acercarse al **16,67 % teórico**.