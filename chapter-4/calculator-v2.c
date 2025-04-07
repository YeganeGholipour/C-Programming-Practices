#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define STACKSIZE 100

char digits[100];  
double stack[STACKSIZE];    
int stack_pointer = 0;  

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

    for (int j = 0; j < 100; j++) {
        digits[j] = '\0';  
    }

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t') continue;

        if (isalpha(c)) {
            digits[i++] = c;
            while (isalpha(c = getchar())) {
                digits[i++] = c;
            }
            digits[i] = '\0';
            return 'F';
        }

        if (isdigit(c)) {
            digits[i++] = c;
            while (isdigit(c = getchar()) || c == '.') {
                digits[i++] = c;
            }
            digits[i] = '\0';
            return 'N';
        }

        else {
            return c;
        }
    }

    return EOF;
}

void calculator() {
    char type;
    double op2;

    while ((type = getop(digits)) != EOF) {
        printf("type: %c, value: %s\n", type, digits); 

        switch (type) {
            case 'N':
                push(atof(digits)); 
                break;

            case '+': push(pop() + pop()); break;
            
            case '*': push(pop() * pop()); break;

            case '-': op2 = pop(); push(pop() - op2); break;

            case '/':
                op2 = pop();  
                if (op2 != 0.0)
                    push(pop() / op2);  
                else
                    printf("error: zero divisor\n");
                break;

            case '%':
                op2 = pop(); 
                if (op2 != 0.0)
                    push(fmod(pop(), op2)); 
                else
                    printf("error: zero divisor\n");
                break;
            
            case 'F':
                if (strcmp(digits, "sin") == 0)
                    push(sin(pop()));
                else if (strcmp(digits, "cos") == 0)
                    push(cos(pop()));
                else if (strcmp(digits, "pow") == 0) {
                    op2 = pop();
                    push(pow(pop(), op2));
                }
                else
                    printf("error: unknown function %s\n", digits);
                break;
            
            case '\n':  
                printf("\tThe Result:%.8g\n", pop());
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
