#include <stdio.h>
#include <stdbool.h>
#include <ctype.h> //fornece métodos como tolower, touper, etc
bool eh_vogal(char c) {
    switch (tolowe(c)) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u': return true;
        default: return false;
    }
}

int main() { 
    char letra = 'A'
    printf("%c é vogal? %s.\n", letra (eh_vogal(letra) ? "sim" : "não"));
    ++letra;
    printf("%c é vogal? %s. \n", letra, (eh_vogal(letra) ? " sim" : "não"));
}