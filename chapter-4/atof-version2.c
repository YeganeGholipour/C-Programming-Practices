#include <stdio.h>
#include <ctype.h>
#include <math.h>

float my_atof(char *s);
float my_pow(float base, int exponent);

int main() {
    char string[] = "  -14.25e3 foo";
    float f = my_atof(string);
    printf("Result: %f\n", f);
    return 0;
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