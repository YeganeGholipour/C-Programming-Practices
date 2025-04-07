#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define NUMBER '0'
#define STACKSIZE 100

char digits[100];  // Buffer for holding digits of the current number
double stack[STACKSIZE];    // Stack for operands
int stack_pointer = 0;  // Stack pointer

void push(double operand) {
    if (stack_pointer < STACKSIZE)
        stack[stack_pointer++] = operand;
    else
        printf("error: stack full, can't push %g\n", operand);
}

double pop(void) {
    if (stack_pointer > 0)
        return stack[--stack_pointer];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int getop(char digits[]) {
    int i = 0;
    char c;

    // Reset the digits buffer to start fresh for the new number
    for (int j = 0; j < 100; j++) {
        digits[j] = '\0';  
    }

    while ((c = getchar()) != EOF) {
        // If there's a space or tab, skip it and continue
        if (c == '\t' || c == ' ') {
            if (i > 0) {  // if there are digits in the buffer, return the number
                digits[i] = '\0';  // Null-terminate the string
                return NUMBER;
            }
            continue;
        }

        // If the character is a digit or a decimal point, add it to the buffer
        if (isdigit(c) || c == '.') {
            digits[i++] = c;
        }
        // // Handle newline, end of input for the current expression
        // else if (c == '\n') {
        //     if (i > 0) {
        //         digits[i] = '\0';  // Null-terminate the string
        //         return '\n';
        //     }
        //     continue;
        // }
        // Return the operator
        else {
            return c;
        }
    }
    return EOF;  // If we reach EOF
}

void calculator() {
    char type;
    double op2;

    // Continuously get input and evaluate
    while ((type = getop(digits)) != EOF) {
        printf("type: %c, value: %s\n", type, digits);  // Debugging line

        switch (type) {
            case NUMBER:
                push(atof(digits));  // Convert the digits buffer to a number and push it to the stack
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();  // Pop the second operand
                push(pop() - op2);  // Pop the first operand and subtract
                break;
            case '/':
                op2 = pop();  // Pop the second operand
                if (op2 != 0.0)
                    push(pop() / op2);  // Pop the first operand and divide
                else
                    printf("error: zero divisor\n");
                break;
            
            case '\n':  // End of input for the current expression
                printf("\tThe Result:%.8g\n", pop());
                break;
            case '%':
                op2 = pop();  // Pop the second operand
                if (op2 != 0.0)
                    push(fmod(pop(), op2));  // Pop the first operand and calculate the modulus
                else
                    printf("error: zero divisor\n");
                break;
            default:
                printf("error: unknown command\n");
                break;
        }
    }
}

int main() {
    calculator();
    return 0;
}
