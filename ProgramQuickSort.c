#include <stdio.h>
#include <stdlib.h>

int particiona(int A[], int inicio, int fim){
    
    int pivo = fim;
    int k = inicio;
    int aux = 0;

    for(int i = inicio; i < fim; i++){
        if(A[i] <= A[pivo]){
            aux = A[i];
            A[i] = A[k];
            A[k] = aux;
            k++;
        }
    }

    if(A[k] > A[pivo]){
        aux = A[k];
        A[k] = A[pivo];
        A[pivo] = aux;
    }

    return k;

}


void quickSort(int A[], int inicio, int fim){
    int pivo = 0;

    if(inicio < fim){
        pivo = particiona(A, inicio, fim);
        quickSort(A, inicio, pivo-1);
        quickSort(A, pivo+1, fim);
    }

}

int main(){
    int n;
    
    printf("Digite o tamanho do vetor:\n");
    scanf("%d", &n);
    int A[n];
    int inicio = 0;
    int fim = n;

    printf("Digite os valores do vetor:\n");
    for(int x=0; x<n; x++){
        scanf("%d", &A[x]);
    }

    quickSort(A, inicio, fim);

    for(int i=0; i<n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
}