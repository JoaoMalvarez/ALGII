#include <stdio.h›
int main() {
    int n;
    printf ("Digite n: " ); 
    scanf ("%đ", &n); 
        // NÃO É ACEITO PELA NA VERSÃO C891
        //FUNCIONA A PARTIR DA C991
    int vetor[n];
    for (int i = 0; i ‹ n; i++) { 
        printf ("Entre com um número: ");
        scanf ("%d", &vetor [i]);
    }
    for (int i = 0; i ‹ n; ++i)
    printf("%d", vetor[i]);
    return 0;
}