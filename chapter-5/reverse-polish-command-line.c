#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STACKSIZE 100
#define NUMBER '0'

float stack[STACKSIZE];
float *sp = stack;

float pop(void);
void push(float val);
char gettop(char *argument);
float get_number(char *argument);
float my_pow(float base, int exponent);
float my_atof(char *s);

float pop(void) {
    if (sp > stack)
        return *--sp;
    else {
        printf("error: stack empty\n");
        return 0;
    }
}

void push(float val) {
    if (sp < stack + STACKSIZE)
        *sp++ = val;
    else
        printf("error: stack full\n");
}

float my_atof(char *s) {
    int sign = 1, exponentSign = 1;
    float number = 0.0, power = 1.0, exponent = 0.0;
    float digit;

    // skip leading spaces
    while (*s == ' ')
        s++;

    while (*s != '\0') {

        if (*s == '-' || *s == '+') {
            sign = (*s == '-') ? -1 : 1;
            s++;
        }

        while (isdigit(*s)) {
            digit = *s++ - '0';
            number = number * 10 + digit;
        }

        if (*s == '.') {
            s++;
            while (isdigit(*s)) {
                digit = *s++ - '0';
                number = number * 10 + digit;
                power *= 10;
            }
        }

        if (*s == 'e' || *s == 'E') {
            s++;
            if (*s == '-' || *s == '+') {
                exponentSign = (*s == '-') ? -1 : 1;
                s++;
            }
            while (isdigit(*s)) {
                digit = *s++ - '0';
                exponent = exponent * 10 + digit;
            }

            exponent *= exponentSign;
        }

        if (number == -(float)0)
            return 0;

        return (number * sign / power) * my_pow(10, exponent);
    
    }   
    
}

float my_pow(float base, int exponent) {
    float result = 1.0;

    if (exponent > 0)
        for (int i = 0; i < exponent; i++)
            result *= base;
    else if (exponent < 0)
        for (int i = 0; i < -exponent; i++)
            result /= base;

    return result;
}

float get_number(char *argument) {
    // return atof(argument);
    return my_atof(argument);
}


char gettop(char *argument) {
    if (isdigit(*argument) || ((*argument == '-' || *argument == '+') && isdigit(*(argument+1)))) 
        return NUMBER;
    return *argument;
}
    

float reverse_polish(char **arguments, int size) {
    char *element;
    char type;
    float number, op2;

    while (size > 0) {
        element = *arguments++;
        type = gettop(element);
        
        switch (type)
        {
        case NUMBER:
            number = get_number(element);
            push(number);
            break;
        
        case '+':
            push(pop() + pop());
            break;
        
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;

        case '/':
            op2 = pop();
            if (op2 != 0)
                push(pop() / op2);
            else
                printf("Erorr: Division By Zero!\n");
            break;
        
        case '*':
            push(pop() * pop());
            break;

        default:
            printf("Error: Unkonwn Token!\n");
            break;
        }

        size--;
    }

    return pop();
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./program <RPN expression>\n");
        return 1;
    }

    for (int i = 0; i < argc; i++)
        printf("argument[%d]: %s\n", i+1, argv[i]);

    float res = reverse_polish(argv + 1, argc - 1);
    printf("Result: %.2f\n", res);
    return 0;
}
