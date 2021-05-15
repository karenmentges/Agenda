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
struct node {
    char name[30];
    char email[40];
    char phone[15];
	struct node *left;
	struct node *right;
};

// Tipo criado para instanciar variaveis do tipo agenda
typedef struct node Node;


// Apresenta o menu da aplicação e retorna a opção selecionada
int menu() {

    int op=0;

    printf("1 Inserir Contato\n");
    printf("2 Deletar Contato\n");
    printf("3 Consultar um Contato\n");
    printf("4 Listar Contatos\n");
    printf("%d Finaliza",EXIT);
    printf("\n: ");
    scanf("%d",&op);
    
    return op;

}


// Função que inicializa a árvore binária de busca
void initializeTree(Node **root) {

    // Faz o aponteiramento para NULL
    *root = NULL;

}

// Função que verifica se a árvore binária de busca está vazia
int emptyTree(Node *root) {
    
    return (root == NULL);

}

// Permite o cadastro de um contato
Node *insContact(Node *root, Node *aux) {

    if(root==NULL){
        root = malloc(sizeof(Node));
        root = aux;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else if(aux->name[0] <= root->name[0]){
        root->left = insContact(root->left, aux);
    }
    else{
        root->right = insContact(root->right, aux);
    }
    
    return root;

}

// Permite excluir um contato da agenda
void delContact() {
    return;
}

// Lista o conteudo da agenda (todos os campos)
void listContacts(Node *root) {

    if(root!=NULL){
        printf("\tNome: %s\n\tE-mail: %s\n\tTelefone: %s\n\n", root->name, root->email, root->phone);
        listContacts(root->left);
        listContacts(root->right);
    }

}

Node *searchContact(Node *root, char *name) {
    if (strcmp(root->name, name) == 0 || root == NULL){
        return root;
    }
    if (strcmp(root->name, name) < 0) {
        return searchContact(root->right, name);
    }
    return searchContact(root->left, name);
}

// Permite consultar um contato da agenda por nome
void queryContact(Node *root, char *name) {
    Node *contact = searchContact(root, name);
    if (contact == NULL) {
        printf("\tContato não existe.\n");
    } else {
        printf("\tNome: %s\n\tE-mail: %s\n\tTelefone: %s\n\n", contact->name, contact->email, contact->phone);
    }
    return;
}


// Programa principal
int main() {

    int op=0;
    //Contact MContact;
    Node *root, *aux;
    

    initializeTree(&root);

    while(op!=EXIT) {
        op = menu();
        switch(op) {
            case 1: 
                aux = malloc(sizeof(Node));
                scanf("%*c");
                printf("Nome: \n");
                fgets(aux->name, sizeof(aux->name), stdin);
                aux->name[strcspn(aux->name, "\n")] = '\0';

                printf("Email: \n");
                fgets(aux->email, sizeof(aux->email), stdin);
                aux->email[strcspn(aux->email, "\n")] = '\0';

                printf("Telefone: \n");
                fgets(aux->phone, sizeof(aux->phone), stdin);
                aux->phone[strcspn(aux->phone, "\n")] = '\0';
                
                root = insContact(root, aux);
                break;
            case 2: 
                delContact();
                break;
            case 3: 
                queryContact();
                break;
            case 4: 
                listContacts(root);
                break;
        }
    }

    return 0;
}