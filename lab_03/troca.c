#include <stdio.h>

void troca(int *a, int *b) {
    int c = *a;
    *a = *b; 
    *b = c;
}

int main() {
    int x = 3;
    int y = 4;
    troca(&x,&y);
    printf("X = %d | Y = %d\n", x, y);
}