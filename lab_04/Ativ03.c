#include <stdio.h>

char aprovaAluno(int nota[], int qntdAlunos, char nomeAluno[]) {
     printf("Quantos alunos existem na turma? ");
    scanf("%d", &qntdAlunos);
    printf("Insira o Nome do aluno");
    scanf("%s", &nomeAluno);
    printf("Insira a nota do aluno %s: ", nomeAluno);
    scanf("%d", &nota);
    int nota, aprovaAluno;
    for (int i = 0; i < qntdAlunos; i++) {
        if (nota >= 7){
             aprovaAluno = "aprovado";
    }
        else {
        aprovaAluno = "reprovado";
        }
 }
        

    aprovaAluno = nota >= 7;
    return aprovaAluno;
}

int calcularMediaTurma(int nota[], int qntdAlunos) {
    int totalnotas = 0;
    for (int i = 0; i < qntdAlunos; i++) {
        totalnotas += nota[i];
   }
   printf("A média da tuma foi: %d\n", totalnotas / qntdAlunos);
   return totalnotas;
}

int imprimirResultados(int qntdAlunos, int totalnotas, char nomeAluno[], char aprovaAluno) {
    printf("n");
    printf("A nota do aluno %s foram: %d\n Ela(e), foi %s", nomeAluno, totalnotas, aprovaAluno);
    return imprimirResultados;
}


int main(int totalnotas, int qntdAlunos) {
    int qntdAlunos; totalnotas; imprimirResultados;
    int notas[qntdAlunos];
    for (int i = 0; i < qntdAlunos; i++) {
        scanf("%d", &notas[i]);
        printf("Nota[%d]: %d\n", i, notas[i]);
    };
    return 0;
}
