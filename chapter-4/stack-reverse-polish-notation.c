#include <stdio.h>
#include <stdlib.h>  // For atof() to convert strings to numbers
#include <ctype.h>   // For isdigit() to check if a character is a digit

#define MAXOP 100     // Max size of operand or operator
#define NUMBER '0'    // Signal that a number was found

int getop(char []);    // Function prototype for getop
void push(double);     // Function prototype for push
double pop(void);      // Function prototype for pop

// Reverse Polish calculator
int main() {
    int type;
    double op2;
    char s[MAXOP];
    
    while ((type = getop(s)) != EOF) {  // Read input until EOF
        switch (type) {
            case NUMBER:
                push(atof(s));  // Convert string to double and push onto stack
                break;
            case '+':
                push(pop() + pop());  // Add two numbers
                break;
            case '*':
                push(pop() * pop());  // Multiply two numbers
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);  // Subtract two numbers
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0) 
                    push(pop() / op2);  // Divide two numbers, check for zero divisor
                else 
                    printf("error: zero divisor\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop());  // Print result with 8 digits of precision
                break;
            default:
                printf("error: unknown command %s\n", s);  // Unknown command error
                break;
        }
    }
    return 0;
}

// Stack for values (operand stack)
#define MAXVAL 100
int sp = 0;  // Next free stack position
double val[MAXVAL];  // Value stack

// Push a value onto the stack
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

// Pop a value from the stack
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

// getop: Get the next character or numeric operand
int getop(char s[]) {
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')  // Skip whitespace
        ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.')  // If not a number or decimal point, return operator
        return c;
    
    i = 0;
    if (isdigit(c))  // Collect integer part of number
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')  // Collect fractional part of number
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';  // Null-terminate the string

    if (c != EOF) 
        ungetch(c);  // Push the unread character back
    return NUMBER;
}

// Buffer for ungetch
#define BUFSIZE 100
char buf[BUFSIZE];  // Buffer for ungetch
int bufp = 0;       // Next free position in buf

// Get a (possibly pushed-back) character
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

// Push a character back on input
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
