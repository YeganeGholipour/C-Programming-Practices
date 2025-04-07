unsigned extractbits(unsigned x, int n) {
    unsigned mask = (1 << n) - 1;
    unsigned bits = mask & x;
    return bits;
}

unsigned clearbits(unsigned x) {
    
}