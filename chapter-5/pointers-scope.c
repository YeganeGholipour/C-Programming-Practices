#include <stdio.h>


void change_pointer() {
    *foundp = 1;
}

int main(void)
{
    int found = 0;
    int *foundp = &found;

    printf("%d\n", *foundp);
    return 0;
}