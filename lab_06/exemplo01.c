#include <stdio.h>

int main() {
    char nome_completo[50];
    printf("Informe o seu nome:");
    fgets(nome_completo, 50, stdin);
    printf("%s", nome_completo);
}