#include <stdio.h>

void escape(char s[], char t[]) {
    int i = 0, j = 0; 
    while (t[i] != '\0') {
        switch (t[i]) {
            case '\n': s[j++] = '\\'; s[j++] = 'n'; break;
            case '\t': s[j++] = '\\'; s[j++] = 't'; break;
            case '\b': s[j++] = '\\'; s[j++] = 'b'; break;
            case '\r': s[j++] = '\\'; s[j++] = 'r'; break;
            case '\f': s[j++] = '\\'; s[j++] = 'f'; break;
            case '\v': s[j++] = '\\'; s[j++] = 'v'; break;
            case '\a': s[j++] = '\\'; s[j++] = 'a'; break;
            default:   s[j++] = t[i]; break;
        }
        i++;
    }
    s[j] = '\0';
}


void unescape(char s[], char t[]) {
    int i = 0, j = 0;
    while (t[i] != '\0')
    {
        if (t[i] == '\\') {
            switch (t[i]) {
                case 'n': s[j++] = '\n'; break;
                case 't': s[j++] = '\t'; break;
                case 'b': s[j++] = '\b'; break;
                case 'r': s[j++] = '\r'; break;
                case 'f': s[j++] = '\f'; break;
                case 'v': s[j++] = '\v'; break;
                case 'a': s[j++] = '\a'; break;
                default: s[j++] = t[i]; break;
            }
        }
        else {
            s[j++] = t[i];
        }

        i++;
    }
    s[j] = '\0';
    
}


int main() {
    char input[] = "Hello\tWorld\nTest";
    char escaped[100];
    char unescaped[100];

    escape(escaped, input);
    printf("Escaped: %s\n", escaped);

    unescape(unescaped, escaped);
    printf("Unescaped: %s\n", unescaped);

    return 0;
}
