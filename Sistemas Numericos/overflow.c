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