/*
 * Tarefa de laboratorio 09 - Avaliacao 1 - Parte 2 - Deque
 *
 * GEX605 AB 2020/1
 *
 * Nome:      Karen Ruver Mentges
 * Matricula: 1921100003
 *
 */


#include <stdio.h>
#include <stdlib.h>

// Declarando as variaveis a serem utilizadas no programa
typedef int Item;

typedef struct elemFila {
 Item item;
 struct elemFila *anterior;
 struct elemFila *proximo;
} ElemFila;

typedef struct {
 ElemFila *primeiro;
 ElemFila *ultimo;
} Fila;


// Função que inicializa a deque
void inicializaDeque(Fila *fila) {

    // Faz os aponteiramentos para NULL
    fila->primeiro = NULL;
    fila->ultimo = NULL;

}

// Função que verifica se a fila está vazia
int dequeVazio(Fila *fila) {
    
    return (fila->primeiro == NULL);

}

// Função que insere um novo elemento no início da deque
void insereInicioDeque (Fila *fila, Item item){

   ElemFila *aux;
    
    // Cria um novo elemento da lista encadeada (Fila)
    aux = malloc(sizeof(ElemFila));

    //Armazena o item a ser inserido no novo elemento 
    aux->item = item;

    // Faz os aponteiramentos para NULL
    aux->proximo = NULL;
    aux->anterior = NULL;
    
    // Insere o novo elemento no inicio da lista encadeada (Fila)
    if (fila->primeiro == NULL) { // Se a fila esta vazia
        fila->primeiro = aux;
        fila->ultimo = aux;
    }

    else { // Se a fila nao esta vazia
        aux->proximo = fila->primeiro;
        fila->primeiro->anterior = aux;
        fila->primeiro = aux;
    }

}

// Função que insere um novo elemento no fim da deque
void insereFimDeque(Fila *fila, Item item) {
    
    ElemFila *aux;
    
    // Cria um novo elemento da lista encadeada (Fila)
    aux = malloc(sizeof(ElemFila));

    // Armazena o item a ser inserido no novo elemento 
    aux->item = item;

    // Faz os aponteiramentos para NULL
    aux->proximo = NULL;
    aux->anterior = NULL;
    
    // Insere o novo elemento no fim da lista encadeada (Fila)
    if (fila->primeiro == NULL) { // Se a fila esta vazia
        fila->primeiro = aux;
        fila->ultimo = aux;
    }

    else { // Se a fila nao esta vazia
        aux->anterior = fila->ultimo;
        fila->ultimo->proximo = aux;
        fila->ultimo = aux;
    }
    
}

// Função que remove o elemento que se encontra no início da deque
void removeInicioDeque(Fila *fila) {
    
    ElemFila *aux;
    Item item;
    
    // Verificar se a fila esta vazia
    if (fila->primeiro == NULL) {
        printf("\nErro na operacao removeFila: fila vazia!\n");
        return;
    }

    else {
        // Armazena o item a ser removido da fila
        item = fila->primeiro->item; 
    
        // Armazena o primeiro elemento da lista encadeada (Fila)
        aux = fila->primeiro;
    
        // Remove este primeiro elemento da lista
        if (fila->primeiro == fila->ultimo) {
            fila->primeiro = NULL;
            fila->ultimo = NULL;
        }
        else {
            fila->primeiro = fila->primeiro->proximo;
            fila->primeiro->anterior = NULL;
        }   

        // Imprime item removido
        printf("%d\n", item);

        // Libera a memoria alocada para o elemento removido
        free(aux);
    }

}

// Função que remove o elemento que se encontra no fim da deque
void removeFimDeque(Fila *fila) {
    
    ElemFila *aux;
    Item item;
    
    // Verificar se a fila esta vazia
    if (fila->primeiro == NULL) {
        printf("\nErro na operacao removeFila: fila vazia!\n");
        return;
    }

    else {
        // Armazena o item a ser removido da fila
        item = fila->ultimo->item; 
    
        // Armazena o ultimo elemento da lista encadeada (Fila)
        aux = fila->ultimo;
    
        // Remove este ultimo elemento da lista
        if (fila->ultimo == fila->primeiro) {
            fila->primeiro = NULL;
            fila->ultimo = NULL;
        }
        else {
            fila->ultimo = fila->ultimo->anterior;
            fila->ultimo->proximo = NULL;
        }   

        // Imprime item removido
        printf("%d\n", item);

        // Libera a memoria alocada para o elemento removido
        free(aux);
    }

}

// Função que libera todos os elementos da deque
void liberaDeque(Fila *fila) {
    
    ElemFila *aux;
    int cont=0;
    
    while (fila->primeiro != NULL) {
        
        // Armazena o primeiro elemento da lista encadeada (Fila)
        aux = fila->primeiro;
        // Faz o aponteiramento para o proximo elemento
        fila->primeiro = fila->primeiro->proximo;
        // Conta quantos elementos são liberados
        cont = cont + 1;
        
        // Libera a memoria alocada para o elemento removido
        free(aux);

    }

    // Aponta o final da fila para NULL
    fila->ultimo = NULL;

    // Imprime os itens liberados
    printf("%d\n", cont);

}


// Função principal do programa
int main() {
    
    // Declarando as variaveis para o main
    Fila fila;
    Item I=0;
    int i, N=0, O=0;
 
    // Recebe o número de operações
    scanf("%d", &N);
    
    // Verifica o número minimo de operações (inicializaDeque e liberaDeque)
    if(N>=2){ 
            
        // Laço para receber cada operação
        for (i = 0; i < N; i++) {
            
            // Recebe o número correspondente a operação
            scanf("%d", &O);

            // Compara o número recebido com o número designado a cada operação
            if(O == 1){
                inicializaDeque(&fila);
            }
            else if(O == 2){
                scanf(" %d", &I);
                insereInicioDeque(&fila, I);
            }
            else if(O == 3){
                scanf(" %d", &I);
                insereFimDeque(&fila, I);
            }
            else if(O == 4){
                removeInicioDeque(&fila);
            }
            else if(O == 5){
                removeFimDeque(&fila);
            }
            else if(O == 6){
                liberaDeque(&fila);
            }
            else{ // Se o "O" não for entre 1 e 6, o programa é finalizado
                break;
            }
        }   
    }
    
    
    return 0;

}