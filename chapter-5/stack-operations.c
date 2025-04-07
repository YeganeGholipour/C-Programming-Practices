#include <stdio.h>
#include <stdbool.h>

#define STACK_SIZE 5

int contents[STACK_SIZE];  // The actual storage
int *top;  // Pointer to the top of the stack

void make_empty(void) {
    top = contents;  // Point to the beginning of the array
}

bool is_empty(void) {
    return top == contents;  // If `top` is still at the start, stack is empty
}

bool is_full(void) {
    return top == contents + STACK_SIZE;  // If `top` moves beyond, it's full
}

void push(int i) {
    if (is_full())
        printf("Error: Stack is full!\n");
    else
        *top++ = i;  // Store value at `top`, then move `top` forward
}

int pop(void) {
    if (is_empty()) {
        printf("Error: Stack is empty!\n");
        return -1;
    } else
        return *--top;  // Move `top` back, then return the value
}

void print_stack() {
    printf("Stack contents: ");
    for (int *p = contents; p < top; p++) {
        printf("%d ", *p);
    }
    printf("\n");
}

int main() {
    make_empty();
    
    push(10);
    push(20);
    push(30);
    
    print_stack();  // Should print: 10 20 30

    printf("Popped: %d\n", pop());  // Should print: 30
    print_stack();  // Should print: 10 20

    printf("****************\n");

    for (int i = 0; i < STACK_SIZE; i++)
        printf("%d\n", contents[i]);

    return 0;
}
