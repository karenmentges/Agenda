#include <stdio.h>

int buscaBinaria (int *vet, int inicio, int fim, int chave){
    int meio;
    
    if (inicio > fim){
        printf("Achou foi nada!\n");
        return -1;
    }

    meio = (inicio+fim)/2;
    printf("inicio: %d, meio: %d, fim: %d\n", inicio, meio, fim);

    if (vet[meio] == chave) {
        printf("Achou!\n");
        return meio;
    }

    if (chave > vet[meio]){
        printf("Foi para os maiores!\n");
        return buscaBinaria(vet, meio+1, fim, chave);
    }
    else{
        printf("Foi para os menores!\n");
        return buscaBinaria(vet, inicio, meio-1, chave);
    }
}

int main(){
    int vet[] = {1,2,3,4,5,6,7,8,9};

    printf("Busca retornou: %d\n", buscaBinaria(vet, 0, 8, 10));
    
    return 0;
}