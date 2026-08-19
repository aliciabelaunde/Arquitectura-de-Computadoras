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