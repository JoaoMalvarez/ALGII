#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    char cargo[30];
    float salario;
} Funcionario;

void lerFuncionarios(Funcionario vet[], int n){
    for(int i = 0; i < n; i++) {
        printf("\nDigite o nome do seu funcionário: ");
        scanf("%s", vet[i].nome);

        printf("\nDigite o cargo do funcionário: ");
        scanf("%s", vet[i].cargo);

        printf("\nDigite o salário do funcionário: ");
        scanf("%f", &vet[i].salario);
    }
}

void ordenarPorNome(Funcionario vet[], int n) {
    Funcionario temp;
    for(int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if(strcmp(vet[j].nome, vet[j + 1].nome) > 0) {
                temp = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = temp;
            }
        }
    }
}

void exibirFuncionarios(Funcionario vet[], int n) {
    ordenarPorNome(vet, n);
    for(int i = 0; i < n; i++) {
        printf("\n\nFuncionário %d", i + 1);
        printf("\nNome: %s \nCargo: %s \nSalário: R$%f", vet[i].nome, vet[i].cargo, vet[i].salario);
    }
}

float calcularMedia(Funcionario vet[], int n) {
    int soma = 0;
    for (int i = 0; i < n; i++) {
        soma += vet[i].salario;
    }
    int media = soma / n;
    return media;
}

int indiceMaiorSalario(Funcionario vet[], int n) {
    int indiceMaior = 0;
    for(int i = 0; i < n -1; i++) {
        if(vet[i].salario > vet[indiceMaior].salario) {
            indiceMaior = i;
        }
    }
    return indiceMaior;
}

int main() {
    int n;
    printf("Digite a quantidade de funcionarios: ");
    scanf("%d", &n);

    Funcionario funcionarios[n];

    lerFuncionarios(funcionarios, n);

    exibirFuncionarios(funcionarios, n);

    float media = calcularMedia(funcionarios, n);
    printf("\n\nA média salarial é de %f", media);

    int indiceMaior = indiceMaiorSalario(funcionarios, n);
    printf("\n\nE o maior salário é de %f, de %s\n\n", funcionarios[indiceMaior].salario, funcionarios[indiceMaior].nome);
    
    return 0;
}