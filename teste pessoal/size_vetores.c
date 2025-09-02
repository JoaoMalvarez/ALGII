#include <stdio.h›
int main() {
    int vetor (] = ( 1, 2, 3, 4, 5, 0 };
    //size_t => unsigned integer
    //é utilizado para representar o tamanho de qualquer 
    //objeto em bytes, como resultado da operação sizeof
    size_t tam_vetor = sizeof(vetor);
    printf ("Tamanho do vetor em bytes: %1d\n", tam_vetor);
    
    size_t tam_int = sizeof(int);
    printf("Quantidade de bytes em um int: %1d\n", tam_int);
    
    size_t tam_elem = sizeof(vetor[0]);
    printf ("Tamanho de um elemento do vetor em bytes: %1d\n", tam_elem);
    
    size_t qtd_elem = sizeof(vetor) / sizeof(vetor (0]);
    printf("Quantidade de elementos no vetor: %dn", qtd_elem);
    
    return 0;
}