/* Transforme a estrutura da lista implementada nas questões 1 e 2 em uma
lista duplamente encadeada. E implemente as seguintes funcionalidades:
a. Imprimir a lista do primeiro para o último elemento, e depois do último
para o primeiro.
b. Crie uma função de busca que apresenta as informações de um
funcionário. A busca deve ser feita utilizando o id.
c. Atualize a função de delete. */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
 int dia;
 int mes;
 int ano;
} Data;

struct funcionario{
 int id;
 char nome[41];
 double salario;
 Data nascimento;
 struct funcionario *proximo;
 struct funcionario *anterior;
};
typedef struct funcionario Funcionario;



void imprimePrimeiro(Funcionario *primeiro, Funcionario *ultimo){

    Funcionario *aux;
    
    if(primeiro==NULL){
        printf("Lista Vazia \n");
    }
    else { 
        printf("Imprimindo do primeiro ao ultimo funcionario: \n");
        for(aux = primeiro; aux != NULL; aux = aux->proximo){
            printf("Funcionario\n\t ID: %d\n\t Nome: %s\n\t Data de nascimento: %d/%d/%d\n\t Salario: %lf\n", aux->id, aux->nome, aux->nascimento.dia, aux->nascimento.mes, aux->nascimento.ano, aux->salario);
        }
        printf("\n\n");
    }

}


void imprimeUltimo(Funcionario *primeiro, Funcionario *ultimo){

    Funcionario *aux;
    
    if(primeiro==NULL){
        printf("Lista Vazia \n");
    }
    else { 
        printf("Imprimindo do ultimo ao primeiro funcionario: \n");
        for(aux = ultimo; aux != NULL; aux = aux->anterior){
            printf("Funcionario\n\t ID: %d\n\t Nome: %s\n\t Data de nascimento: %d/%d/%d\n\t Salario: %lf\n", aux->id, aux->nome, aux->nascimento.dia, aux->nascimento.mes, aux->nascimento.ano, aux->salario);
        }
        printf("\n\n");
    }

}

void buscaFuncionario(Funcionario *primeiro, int id){

    Funcionario *aux;
    for(aux = primeiro; aux != NULL; aux = aux->proximo){
        if(aux->id == id){
            if(primeiro == NULL){
                printf("\n\n");
                printf("Nao foi possivel localizar, lista está vazia \n");
            }
            else { 
                printf("\n\n");
                printf("Funcionario\n\t ID: %d\n\t Nome: %s\n\t Data de nascimento: %d/%d/%d\n\t Salario: %lf\n", aux->id, aux->nome, aux->nascimento.dia, aux->nascimento.mes, aux->nascimento.ano, aux->salario);
            }
        }
    }
}

Funcionario *deletaPrimeiroFuncionario(Funcionario *primeiro, Funcionario *ultimo, int id){

    Funcionario *aux=NULL, *anterior=NULL; 
    for(aux = primeiro; aux != NULL; aux = aux->proximo){
        if(aux->id == id){
            if(primeiro == NULL){
                free(ultimo);
                ultimo = NULL;
                return NULL; //verifica se a lista está vazia
            }
            else if(aux == primeiro) { 
                primeiro = primeiro->proximo; //verifica se é o primeiro
                primeiro->anterior = NULL;
            }
            else if (aux == ultimo) { //verifica se é o ultimo
                ultimo = ultimo->anterior;
                ultimo->proximo = NULL;
            } 
            else {
                anterior = aux->anterior;
                anterior->proximo = aux->proximo;
                aux->proximo->anterior = anterior;
            }
        free(aux); //apaga o aux
        break;
        }
    }

    return primeiro;

}


Funcionario *deletaUltimoFuncionario(Funcionario *ultimo, Funcionario *primeiro, int id){

    Funcionario *aux=NULL, *proximo=NULL; 
    for(aux = ultimo; aux != NULL; aux = aux->anterior){
        if(aux->id == id){
            if(ultimo == NULL){
                free(primeiro);
                primeiro = NULL;
                return NULL; //verifica se a lista está vazia
            }
            else if(aux == ultimo) { 
                ultimo = ultimo->anterior; 
                ultimo->proximo = NULL;
            }
            else if (aux == primeiro) { 
                primeiro = primeiro->proximo;
                primeiro->anterior = NULL;
            } 
            else {
                proximo = aux->proximo;
                proximo->anterior = aux->anterior;
                aux->anterior->proximo = proximo;
            }
        free(aux); //apaga o aux
        break;
        }
    }

    return ultimo;

}


void limpaTodaLista(Funcionario *Lista){
	Funcionario *aux;
	while (Lista != NULL){
		aux = Lista;
		Lista = Lista->proximo;
		free(aux);
	}
}

int main () {
    
    Funcionario *aux, *primeiro=NULL, *ultimo;
    int i=0, num=0, id=0;


    printf("Insira o numero de funcionarios a serem incluidos: \n");
    scanf("%d", &num);


    for(i=0; i<num; i++){

        aux = malloc(sizeof(Funcionario));
    
        printf("ID do funcionario: \n");
        scanf("%d%*c", &aux->id); //o %*c representa ler um caractere mas não gravar, só outra forma de eliminar o '\n', pois ele atrapalha o fgets

        printf("Nome do funcionario: \n");
        fgets(aux->nome, sizeof(aux->nome), stdin);
        aux->nome[strcspn(aux->nome, "\n")] = '\0';

        printf("Dia de nascimento do funcionario: \n");
        scanf("%d", &aux->nascimento.dia);

        printf("Mes de nascimento do funcionario: \n");
        scanf("%d", &aux->nascimento.mes);

        printf("Ano de nascimento do funcionario: \n");
        scanf("%d", &aux->nascimento.ano);

        printf("Salario do funcionario: \n");
        scanf("%lf", &aux->salario);

        printf("\n\n");

        aux->proximo = NULL;
        aux->anterior = NULL;

        if (primeiro == NULL){
			primeiro = aux;
			ultimo = aux;
		}
        else{
			aux->anterior = ultimo;
			ultimo->proximo = aux;
			ultimo = aux;
		}


    }

    imprimePrimeiro(primeiro, ultimo);
    imprimeUltimo(primeiro, ultimo);

    printf("Insira o ID do funcionario a ser buscado: \n");
    scanf("%d", &id);
    buscaFuncionario(primeiro, id);
    id=0;

    printf("Insira o ID do funcionario a ser deletado: \n");
    scanf("%d", &id);
    primeiro = deletaPrimeiroFuncionario(primeiro, ultimo, id);
    ultimo = deletaUltimoFuncionario(ultimo, primeiro, id);

    printf("Listas apos a exclusao do funcionario selecionado: \n");
    imprimePrimeiro(primeiro, ultimo);
    imprimeUltimo(primeiro, ultimo);

    limpaTodaLista(primeiro);


    return 0;
}