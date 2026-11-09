#include <stdio.h>
#include <string.h>

int main() {
    char result[10], op1[10], op2[10], operator;
    char code[50];

    printf("Enter three address code:\n");
    scanf("%s", code);

    /* Split "c=a+b" into result="c", op1="a", operator='+', op2="b" */
    sscanf(code, "%[^=]=%[^+*/-]%c%s", result, op1, &operator, op2);

    printf("\nEquivalent 8086 Assembly Code:\n");

    /* Step 1: load the first operand into AX */
    printf("MOV AX, %s\n", op1);

    /* Step 2: operate with the second operand */
    switch (operator) {
        case '+':
            printf("ADD AX, %s\n", op2);
            break;

        case '-':
            printf("SUB AX, %s\n", op2);
            break;

        case '*':
            printf("MOV BX, %s\n", op2);
            printf("MUL BX\n");
            break;

        case '/':
            printf("MOV BX, %s\n", op2);
            printf("MOV DX, 0\n");
            printf("DIV BX\n");
            break;

        default:
            printf("Invalid operator\n");
            return 1;
    }

    /* Step 3: store the answer from AX into the result */
    printf("MOV %s, AX\n", result);

    return 0;
}




output 

Enter three address code:
c=a*b

Equivalent 8086 Assembly Code:
MOV AX, a
MOV BX, b
MUL BX
MOV c, AX
pranav@laptop:~/compilerlab$ ./a.out
Enter three address code:
result=exp1/exp2

Equivalent 8086 Assembly Code:
MOV AX, exp1
MOV BX, exp2
MOV DX, 0
DIV BX
MOV result, AX
pranav@laptop:~/compilerlab$ ./a.out
Enter three address code:
c=a+b

Equivalent 8086 Assembly Code:
MOV AX, a
ADD AX, b
MOV c, AX
