#include <stdio.h>
#include <limits.h>

double atof(char s[]) {
    int i = 0, sign, exponentSign;
    int j = 0;
    double n = 0.0, power = 1.0, exponent = 0.0;

    while (s[i] == ' ') {
        i++;
    }

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') 
        i++;

    while (s[i] >= '0' && s[i] <= '9') {
        int digit = s[i] - '0';
        n = 10 * n + digit;
        i++;
    }

    if (s[i] == '.') 
        i++;
        while (s[i] >= '0' && s[i] <= '9')
        {   
            int digit = s[i] - '0'; 
            n = 10 * n + digit;
            power *= 10;
            i++;
        }
    
    if (s[i] == 'e' || s[i] == 'E')
        i++;
    
    if (s[i] == '-' || s[i] == '+') {
        exponentSign = (s[i] == '-') ? -1 : 1;
        i++;
    }

    while (s[i] >= '0' && s[i] <= '9') {
        int digit = s[i] - '0'; 
        exponent = 10 * exponent + digit;
        i++;
    }

    exponent *= exponentSign;

    double exponentValue = 1.0;
    if (exponent > 0) {
        for (j = 0; j < exponent; j++)  
            exponentValue *= 10;
    }
    else {
        for (j = 0; j < -exponent; j++)
            exponentValue /= 10;
    }
    
    
    return (sign * n / power) * exponentValue;
    // return (sign * n / power) * pow(10, exponent);
}


int main() {
    // char s[] = "123.45e-6";
    char s[] = "- 123.45e-6";
    printf("Result: %g\n", atof(s));  // Should print 0.00012345
    return 0;
}