#include <stdio.h›
int main() {
    int vetor (] = ( 1, 2, 3, 4, 5, 0 };
    //size_t => unsigned integer
    //é utilizado para representar o tamanho de qualquer 
    //objeto em bytes, como resultado da operação sizeof
    size_t tam_vetor = sizeof(vetor);
    printf ("Tamanho do vetor em bytes: %ld\n", tam_vetor);
    
    size_t tam_int = sizeof(int);
    printf("Quantidade de bytes em um int: %ld\n", tam_int);
    
    size_t tam_elem = sizeof(vetor[0]);
    printf ("Tamanho de um elemento do vetor em bytes: %1d\n", tam_elem);
    
    size_t qtd_elem = sizeof(vetor) / sizeof(vetor (0]);
    printf("Quantidade de elementos no vetor: %dn", qtd_elem);
    
    return 0;
}



-----------------------------

#include <stdio.h›
void funcao(int arr[]) {
    printf(" funcao(): \n");
    printf(" - tamanho do vetor: %ld\n", sizeof(arr));
    printf(" - elementos do vetor: %ld\n", (sizeof (arr) / sizeof(arr[0])));
}

int main(){
    printf ("tamanho de um ponteiro: %ld\n", sizeof(void*));
    int vetor [] = ( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    printf("main(): \n");
    printf(" - tamanho do vetor: %ld\n" sizeof (vetor));
    printf(" - elementos do vetor: %ld\n", (sizeof(vetor) / sizeof (vetor [@])));
    funcao (vetor);
    return 0;
}
//O que será impresso?
//Será impresso será a posição 8 