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

typedef struct {
    char name[30];
    char email[40];
    char phone[15];
} Contatos;


// Apresenta o menu da aplicação e retorna a opção selecionada
int menu() {
    int op=0;

    printf("\nMenu\n");
    printf("\n1 Inserir Contato\n");
    printf("2 Deletar Contato\n");
    printf("3 Consultar um Contato\n");
    printf("4 Listar Contatos\n");
    printf("\n%d Finaliza\n",EXIT);
    printf("\n");
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
    else if(strcmp(root->name, aux->name) > 0){
        root->left = insContact(root->left, aux);
    }
    else {
        root->right = insContact(root->right, aux);
    }
    
    return root;
}

Node *menorNo(Node *node) {
    Node *aux = node;
    while (aux && aux->left != NULL) {
        aux = aux->left;
    }
    return aux;
}

Node *delContact(Node *root, char *name) {
    if (root==NULL) {
        return root;
    }
    // se name > root.name
    if (strcmp(name, root->name) < 0 ) {
        root->left = delContact(root->left,name);
    }
    // se name < root.name
    else if (strcmp(name, root->name) > 0) {
        root->right = delContact(root->right, name);
    }
    // se name == root
    else {
        // se tiver só um filho ou nenhum filho
        if (root->left==NULL) {
            Node *aux = root->right;
            free(root);
            return aux;
        }
        else if (root->left==NULL) {
            Node *aux = root->left;
            free(root);
            return aux;
        }
        Node *aux = menorNo(root->right);
        strcpy(root->name, aux->name);
        strcpy(root->email, aux->email);
        strcpy(root->phone, aux->phone);
        root->right = delContact(root->right, aux->name);
    }
    return root;
}

int contaContatos(Node* root) {
    if(root==NULL){
        return 0;
    }
    return (1 + contaContatos(root->left) + contaContatos(root->right));
}

Contatos *copiaAgenda(Contatos *agenda, Node *root, int i) {
    if(root!=NULL){
        strcpy(agenda[i].name, root->name);
        strcpy(agenda[i].email, root->email);
        strcpy(agenda[i].phone, root->phone);
        i++;
        copiaAgenda(agenda, root->left, i);
        copiaAgenda(agenda, root->right, i+contaContatos(root->left));
    }
}

void intercala(Contatos A[], int inicio, int meio, int fim) {
    Contatos *aux = malloc((fim-inicio+1)*sizeof(Contatos));
    int i = inicio;
    int j = meio+1;
    int k = 0;
    while (i <= meio && j <= fim) {
        if (strcmp(A[i].name, A[j].name) <= 0) {
            aux[k] = A[i];
            i++;
        }
        else {
            aux[k] = A[j];
            j++;
        }
        k++;
    }
    while (i <= meio) {
        aux[k] = A[i];
        k++;
        i++;
    }
    while (j <= fim) {
        aux[k] = A[j];
        k++;
        j++;
    }
    for (k = inicio; k <= fim; k++) {
        A[k] = aux[k-inicio];
    }
    free(aux);
}

void mergeSort(Contatos A[], int inicio, int fim) {
    int meio;
    if (inicio < fim) {
        meio = (inicio + fim)/2;
        mergeSort(A, inicio, meio);
        mergeSort(A, meio + 1, fim);
        intercala(A, inicio, meio, fim);
    }
}

// Lista o conteudo da agenda (todos os campos)
void listContacts(Node *root) {
    int n = contaContatos(root);
    Contatos agenda[n];
    copiaAgenda(agenda, root, 0);
    mergeSort(agenda, 0, (n-1));
    for (int i = 0; i < n; i++) {
        printf("\tNome: %s\n\tE-mail: %s\n\tTelefone: %s\n\n", agenda[i].name, agenda[i].email, agenda[i].phone);
    }
    
}

Node *searchContact(Node *root, char *name) {
    if (strcmp(root->name, name) == 0 || root == NULL){
        return root;
    }
    if (strcmp(root->name, name) > 0) {
        return searchContact(root->left, name);
    }
    else {
        return searchContact(root->right, name);
    }
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
    char name[40];    

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
                scanf("%*c");
                printf("Nome: \n");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                root = delContact(root, name);
                break;
            case 3: 
                scanf("%*c");
                printf("Nome: \n");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                queryContact(root, name);
                break;
            case 4: 
                listContacts(root);        
                break;
        }
    }

    return 0;
}