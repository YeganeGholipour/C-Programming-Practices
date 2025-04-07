#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    unsigned mask = ~(((1 << n) - 1) << (p - n + 1)); // Step 1: Create a mask
    unsigned bits = (y & ((1 << n) - 1)) << (p - n + 1); // Step 2: Extract and shift bits
    return (x & mask) | bits; // Step 3: Replace bits
}
