/*
 Este é um esqueleto que deve ser utilzado como base para implementação da Agenda.
	- As funções não tem os parâmetros definidos e os parâmetros caso necessários, devem ser incluídos.
    - Caso seja necessário novas funções podem ser incluídas
 	- Devem ser respeitados os nomes dados para o métodos e estruturas, porém novas estruturas e funções podem ser criados, caso julgue necessário
	- Faça os includes necessários
	- A organização das funções fica a critério do programador
	- Códigos não identados sofrerão duras penalidades
	- Não serão toleradas variaveis globais
	- Caso seja detectado plágio, os grupos envolvidos receberão nota 0.
*/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


#define EXIT 10  // valor fixo para a opção que finaliza a aplicação


// Estrutura que contém os campos dos registros da agenda
struct MREC {
    char name[30];
    char email[40];
    char phone[15];
	struct MREC *next; // implemente como lista, como árvore BST, AVL...
	struct MREC *prev;
};

// Tipo criado para instanciar variaveis do tipo agenda
typedef struct MREC Contact;

typedef struct {
    Contact *primeiro;
    Contact *ultimo;
} Fila;


// Apresenta o menu da aplicação e retorna a opção selecionada
int menu() {

    int op=0;

    printf("1 Inserir Contato\n");
    printf("2 Deletar Contato\n");
    printf("3 Listar Contatos\n");
    printf("4 Consultar um Contato\n");
    printf("%d Finaliza",EXIT);
    printf("\n: ");
    scanf("%d",&op);
    
    return op;

}

// Função que inicializa a fila
void inicializaFila(Fila *fila) {

    // Faz os aponteiramentos para NULL
    fila->primeiro = NULL;
    fila->ultimo = NULL;

}

// Permite o cadastro de um contato
void insContact(Fila *fila) {
    Contact *aux;
    
    // Cria um novo elemento da lista encadeada (Fila)
    aux = malloc(sizeof(Contact));

    scanf("%*c");
    // Recebe e armazena os dados no novo elemento
    printf("Nome: \n");
    fgets(aux->name, sizeof(aux->name), stdin);
    aux->name[strcspn(aux->name, "\n")] = '\0';
    
    printf("Email: \n");
    fgets(aux->email, sizeof(aux->email), stdin);
    aux->email[strcspn(aux->email, "\n")] = '\0';

    printf("Telefone: \n");
    fgets(aux->phone, sizeof(aux->phone), stdin);
    aux->phone[strcspn(aux->phone, "\n")] = '\0';

    // Faz os aponteiramentos para NULL
    aux->next = NULL;
    aux->prev = NULL;
    
    // Insere o novo elemento no fim da lista encadeada (Fila)
    if (fila->primeiro == NULL) { // Se a fila esta vazia
        fila->primeiro = aux;
        fila->ultimo = aux;
    }
    else { // Se a fila nao esta vazia
        aux->prev = fila->ultimo;
        fila->ultimo->next = aux;
        fila->ultimo = aux;
    }

}

// Permite excluir um contato da agenda
void delContact() {
    return;
}

// Lista o conteudo da agenda (todos os campos)
void listContacts(Fila *fila) {
    Contact *aux;
    aux = malloc(sizeof(Contact));

    printf("Agenda:\n\n");

    while (fila->primeiro != NULL) {
        aux = fila->primeiro;
        printf("\tNome: %s\n\tE-mail: %s\n\tTelefone: %s\n\n", aux->name, aux->email, aux->phone);
        fila->primeiro = fila->primeiro->next;
    }

    free(aux);
}

// Permite consultar um contato da agenda por nome
void queryContact() {
    return;
}


// Programa principal
int main() {

    int op=0;
    Contact MContact;
    Fila fila;

    inicializaFila(&fila);

    while(op!=EXIT) {
        op = menu();
        switch(op) {
            case 1: 
                insContact(&fila);
                break;
            case 2: 
                delContact();
                break;
            case 3: 
                queryContact();
                break;
            case 4: 
                listContacts(&fila);
                break;
        }
    }

    return 0;

}