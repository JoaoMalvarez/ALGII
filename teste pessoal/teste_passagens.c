#include ‹stdio.h>
void modificaValor (int numero) {
    numero = 20;
    printf("Dentro da funcao: numero = %dn" , numero);
}

int main() {
    int x = 10;
    printf("Antes da função: x = %d\n", x);
    modificaValor (x); // Passagem por valor
    printf("Depois da funcao: x = %d\n", x);
    return 0;
}



void modificaValor (int 1numero) {
    1numero = 20;
    printf("Dentro da funcao: numero = %d\n", numero);
}

int main () {
    int x = 10;
    printf ("Antes da função: x = %d\n", x);
    modificaValor (&x); // Passagen por referincia
    printf("Depois da funcao: x = %d\n", x);
    return 0;
}