#include <stdio.h>

float calcularMediaTurma(float notas[], int qntdAlunos) {
    float soma = 0;
    for (int i = 0; i < qntdAlunos; i++) {
        soma += notas[i];
    }
    return soma / qntdAlunos;
}

void imprimirResultados(char nomes[][50], float notas[], int qntdAlunos) {
    int aprovados = 0, recuperacao = 0;

    for (int i = 0; i < qntdAlunos; i++) {
        if (notas[i] >= 7.0) {
            printf("Aluno %s: nota %.2f -> Aprovado\n", nomes[i], notas[i]);
            aprovados++;
        } else {
            printf("Aluno %s: nota %.2f -> Recuperação\n", nomes[i], notas[i]);
            recuperacao++;
        }
    }

    printf("\nTotal de aprovados: %d\n", aprovados);
    printf("Total de recuperação: %d\n", recuperacao);
}

int main() {
    int qntdAlunos;

    printf("Quantos alunos existem na turma? ");
    scanf("%d", &qntdAlunos);

    float notas[qntdAlunos];
    char nomes[qntdAlunos][50]; // cada linha é o nome de um aluno

    // Cadastro de alunos
    for (int i = 0; i < qntdAlunos; i++) {
        printf("\nDigite o nome do aluno %d: ", i + 1);
        scanf("%s", nomes[i]);

        printf("\nDigite a nota do aluno %s: ", nomes[i]);
        scanf("%f", &notas[i]);
    }

    // Calcular média da turma
    float media = calcularMediaTurma(notas, qntdAlunos);
    printf("\nMédia da turma: %.2f\n\n", media);

    // Mostrar resultados
    imprimirResultados(nomes, notas, qntdAlunos);

    return 0;
}
