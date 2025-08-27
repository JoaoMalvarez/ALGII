#include <stdio.h>

int main() {
    int taxa;
    printf("Digite a taxa: ");
    scanf("%d", &taxa);

    int selos5, selos3;
    if (taxa % 5 == 0) {
        selos5 = taxa / 5;
        selos3 = 0;
    }
    else if (taxa % 5 == 1) {
        selos5 = taxa / 5 - 1;
        selos3 = 2;
    }
    else if (taxa % 5 == 2) {
        selos5 = taxa / 5 - 2;
        selos3 = 4;
    }
    else if (taxa % 5 == 3){
        selos5 = taxa / 5;
        selos3 = 1;
    }

    else if (taxa % 5 == 4) {
        selos5 = taxa / 5 - 1;
        selos3 = 3;
    }
    printf("Selos de 5: %d\n", selos5);
    printf("Selos de 3: %d\n", selos3);

    return 0;
}