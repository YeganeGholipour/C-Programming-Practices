/*

for (;;) {
    prompt user to enter operation code;
    read code;

    switch (code) {
        case 'i': perform insert operation; break;
        case 's': perform search operation; break;
        case 'u': perform update operation; break;
        case 'p': perform print operation; break;
        case 'q': terminate program;
        default: print error message
    }
}

since all functions need to have access to inventory and num_parts
we need to make them global.

we also could declare these variables inside main, and then
pass them to the functions as parameters

We have Three files:
    inventory.c : contains the bulk of the program
    readline.h : contains the prototype for the read_line function
    readline.c : contains the definition of read_line

*/


#include <stdio.h>
#include "readline.h"

#define NAME_LEN 25
#define MAX_PARTS 100

typedef struct {
    int number;
    char name[NAME_LEN+1];
    int on_hand;
} Part;

Part inventory[MAX_PARTS];

int num_parts = 0;

int find_part(int number);
void insert(void);
void search(void);
void update(void);
void print(void);

int main() {
    char code;

    for (;;) {
        printf("Enter Operation Code:  ");
        scanf("%c", &code);
        while (getchar() != '\n') // to consume the garbage characters including \n
            ;
        switch (code)
        {
        case 'i': insert(); break;
        case 's': search(); break;
        case 'u': update(); break;
        case 'p': print(); break;
        case 'q': print(); break;
        default: printf("Illegal Code\n");
        }

        printf("\n");
    }
}


int find_part(int number) {
    int i;

    for (i = 0; i < num_parts; i++)
        if (inventory[i].number == number)
            return i;

    return -1;
}

void insert(void) {
    int part_number;

    if (num_parts == MAX_PARTS) {
        printf("Database is full; can't add more parts.\n");
        return;
    }

    printf("Enter part number: ");
    scanf("%d", &part_number);

    if (find_part(part_number) >= 0) {
        printf("Part already exists.\n");
        return;
    }

    inventory[num_parts].number = part_number;

    printf("Enter part name: ");
    read_line(inventory[num_parts].name, NAME_LEN);

    printf("Enter quantity on hand: ");
    scanf("%d", &inventory[num_parts].on_hand);

    num_parts++;
}


void search(void) {
    int i, number;

    printf("Enter part number: ");
    scanf("%d", &number);

    i = find_part(number);

    if (i >= 0) {
        printf("Part name: %s\n", inventory[i].name);
        printf("Quantity on hand: %d\n", inventory[i].on_hand);
    } else {
        printf("Part not found.\n");
    }
}


void update(void) {
    int i, number, change;

    printf("Enter part number: ");
    scanf("%d", &number);

    i = find_part(number);

    if (i >= 0) {
        printf("Enter change in quantity on hand: ");
        scanf("%d", &change);
        inventory[i].on_hand += change;
    } else {
        printf("Part not found,\n");
    }
}


void print(void) {
    int i;

    printf("Part Number    Part Name     Quantity on Hand\n");
    for (i = 0; i < num_parts; i++)
    {
        printf("%7d       %-25s%11d\n", inventory[i].number, inventory[i].name, inventory[i].on_hand);
    }
    
}