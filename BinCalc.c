// Gabriel Reis Panho - 23/03/23 - PUCRS

#include <stdio.h>
#include <stdlib.h>
#include <fenv.h>

/* Some examples of exceptions:

➜   ./BinCalc 3.40e38 '*' 3.40e38
Overflow occurred: FE_OVERFLOW
val1   = 339999995214436424907732413799364296704.000000 01111111011111111100100110011110
val2   = 339999995214436424907732413799364296704.000000 01111111011111111100100110011110
result = inf 01111111100000000000000000000000

➜   ./BinCalc 1.23456 / 2.3456
Inexact exception occurred: FE_INEXACT
val1   = 1.234560 00111111100111100000011000010000
val2   = 2.345600 01000000000101100001111001001111
result = 0.526330 00111111000001101011110110010011

➜   ./BinCalc 1e-45 / 2
Underflow occurred: FE_UNDERFLOW
val1   = 0.000000 00000000000000000000000000000001
val2   = 2.000000 01000000000000000000000000000000
result = 0.000000 00000000000000000000000000000000

➜   ./BinCalc 1 / 0
Division by zero occurred: FE_DIVBYZERO
val1   = 1.000000 00111111100000000000000000000000
val2   = 0.000000 00000000000000000000000000000000
result = inf 01111111100000000000000000000000

➜  ./BinCalc 0 / 0
Invalid operand or operation: FE_INVALID
val1   = 0.000000 00000000000000000000000000000000
val2   = 0.000000 00000000000000000000000000000000
result = -nan 11111111110000000000000000000000

*/

char *floatToBinary(float num)
{
    char *result = (char *)malloc(sizeof(char) * 33);
    if (result == NULL)
    {
        return NULL; // malloc failed
    }
    for (int i = 31; i >= 0; i--)
    {
        result[31 - i] = ((*(unsigned int *)&num) >> i) & 1 ? '1' : '0';
    }
    result[32] = '\0';
    return result;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s num1 operation num2 \n", argv[0]);
        return 1;
    }

    float num1 = atof(argv[1]);
    float num2 = atof(argv[3]);
    char op = argv[2][0];
    char *binaryNum1 = floatToBinary(num1);
    char *binaryNum2 = floatToBinary(num2);
    char *binaryResult;
    float result;

    feclearexcept(FE_ALL_EXCEPT);

    switch (op)
    {
    case '+':
        result = num1 + num2;
        binaryResult = floatToBinary(result);
        break;
    case '-':
        result = num1 - num2;
        binaryResult = floatToBinary(result);
        break;
    case '*':
        result = num1 * num2;
        binaryResult = floatToBinary(result);
        break;
    case '/':
        result = num1 / num2;
        binaryResult = floatToBinary(result);
        break;
    default:
        printf("Invalid operation\n");
        return 1;
    }

    if (fetestexcept(FE_ALL_EXCEPT) & FE_INVALID)
    {
        printf("Invalid operand or operation: FE_INVALID\n");
    }
    else if (fetestexcept(FE_ALL_EXCEPT) & FE_OVERFLOW)
    {
        printf("Overflow occurred: FE_OVERFLOW\n");
    }
    else if (fetestexcept(FE_ALL_EXCEPT) & FE_UNDERFLOW)
    {
        printf("Underflow occurred: FE_UNDERFLOW\n");
    }
    else if (fetestexcept(FE_ALL_EXCEPT) & FE_DIVBYZERO)
    {
        printf("Division by zero occurred: FE_DIVBYZERO\n");
    }
    else if (fetestexcept(FE_ALL_EXCEPT) & FE_INEXACT)
    {
        printf("Inexact exception occurred: FE_INEXACT\n");
    }

    // printf("%f (%s) %c %f (%s) = %f (%s)\n", num1, binaryNum1, op, num2, binaryNum2, result, binaryResult);
    printf("val1   = %f %s \n", num1, binaryNum1);
    printf("val2   = %f %s \n", num2, binaryNum2);
    printf("result = %f %s \n\n", result, binaryResult);

    return 0;
}