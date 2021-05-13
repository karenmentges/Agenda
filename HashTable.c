#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct item{
    int chave;
    struct item *anterior;
    struct item *proximo;
}; typedef struct item Item;

typedef struct{
    Item *primeiro;
    Item *ultimo;
} ItemHash;


// Calcula a função da Tabela Hash
int hashFunction(int k, int M){
    return k%M;
} 


// Adiciona os elementos à Tabela Hash
ItemHash *controiTabela(ItemHash *tabelaHash, int chave, int M){
    int posicaoHash;
    Item *aux;
   
    aux = malloc(sizeof(Item));   
    aux->chave = chave;
    aux->anterior = NULL;
    aux->proximo = NULL;

    posicaoHash = hashFunction(aux->chave, M);
        
    if (tabelaHash[posicaoHash].primeiro == NULL){
        tabelaHash[posicaoHash].primeiro = aux;
        tabelaHash[posicaoHash].ultimo = aux;
    }
    else {
        aux->anterior = tabelaHash[posicaoHash].ultimo;
        tabelaHash[posicaoHash].ultimo->proximo = aux;
        tabelaHash[posicaoHash].ultimo = aux;
        printf("C %d: %d\n", posicaoHash, chave);
    }

    return tabelaHash;
}

Item *removeItemTabela(Item *primeiro, Item *ultimo, int chave){

    Item *aux=NULL, *anterior=NULL; 
    for(aux = primeiro; aux != NULL; aux = aux->proximo){
        if(aux->chave == chave){
            if(primeiro == NULL){
                free(ultimo);
                ultimo = NULL;
                return NULL; 
            }
            else if(aux == primeiro && aux == ultimo){
                primeiro = NULL;
                ultimo = NULL;
                return NULL;
            }
            else if(aux == primeiro) { 
                primeiro = primeiro->proximo;
                primeiro->anterior = NULL;
            }
            else if (aux == ultimo) { 
                ultimo = ultimo->anterior;
                ultimo->proximo = NULL;
            } 
            else {
                anterior = aux->anterior;
                anterior->proximo = aux->proximo;
                aux->proximo->anterior = anterior;
            }
        free(aux); 
        break;
        }
    }

    return primeiro;

}


// Imprime a Tabela Hash
void imprimirTabela(ItemHash *tabelaHash, int M){
    Item *aux;
    
    for(int m=0; m<M; m++){
        if (tabelaHash[m].primeiro == NULL){
            printf("%d -> \\\n", m);
        }
        else {
            aux = tabelaHash[m].primeiro;
            printf("%d", m);
            while(aux!=NULL){
                printf(" -> %d", aux->chave);
                aux = aux->proximo; 
            }
            printf(" -> \\\n");
        }
    }
}


// Imprime item da Tabela Hash
void imprimirItem(ItemHash *tabelaHash, int P){
    Item *aux;

    if (tabelaHash[P].primeiro == NULL){
        printf("%d -> \\\n", P);
    }
    else {
        aux = tabelaHash[P].primeiro;
        printf("%d", P);
        while(aux!=NULL){
            printf(" -> %d", aux->chave);
            aux = aux->proximo; 
        }
        printf(" -> \\\n");
    }
}


// Libera a Tabela Hash
void liberarTabela(ItemHash *tabelaHash, int M){
    Item *aux=NULL, *aux2=NULL;

    for(int m=0; m<M; m++){
        aux = tabelaHash[m].primeiro;
        while(aux!=NULL){
            aux2 = aux->proximo;
            free(aux);
            aux = aux2; 
            printf("-");
        }
        free(aux2);
    }

}


int main(){
    
    ItemHash tabelaHash[200];
    int M, V, cont=0, posicaoHash;
    char O;

    // Recebe a constante para calcular a posição da Tabela Hash
    scanf("%d", &M);

    // Inicializa a Tabela Hash
    for(int m=0; m<M; m++){
        tabelaHash[m].primeiro = NULL;
    }

    // Compara o número recebido com o número designado a cada operação
    do{
        scanf("\n");
        scanf("%c", &O);

        if(O == 'I'){
            scanf(" %d", &V);
            controiTabela(tabelaHash, V, M);
        }
        else if(O == 'R'){
            scanf(" %d", &V);
            posicaoHash = hashFunction(V, M);
            tabelaHash[posicaoHash].primeiro = removeItemTabela(tabelaHash[posicaoHash].primeiro, tabelaHash[posicaoHash].ultimo, V); 
            tabelaHash[posicaoHash].ultimo = removeItemTabela(tabelaHash[posicaoHash].primeiro, tabelaHash[posicaoHash].ultimo, V); 
        }
        else if(O == 'L'){
            scanf(" %d", &V);
            if(V == -1){
                imprimirTabela(tabelaHash, M);
            }
            else{
                imprimirItem(tabelaHash, V);
            }
        }
        else if(O == 'S'){
            liberarTabela(tabelaHash, M);
            printf("\n");
            break;
        }
    } while(cont==0);

    
    return 0;
}