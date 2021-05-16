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
	struct MREC *next;
	struct MREC *prev;
};

// Tipo criado para instanciar variaveis do tipo agenda
typedef struct MREC Contact;

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
void initializeTree(Contact **root) {
    // Faz o aponteiramento para NULL
    *root = NULL;
}

// Função que verifica se a árvore binária de busca está vazia
int emptyTree(Contact *root) {
    return (root == NULL);
}

// Permite o cadastro de um contato
Contact *insContact(Contact *root, Contact *aux) {
    if(root==NULL){
        root = malloc(sizeof(Contact));
        root = aux;
        root->prev = NULL;
        root->next = NULL;
        return root;
    }
    else if(strcmp(root->name, aux->name) > 0){
        root->prev = insContact(root->prev, aux);
    }
    else {
        root->next = insContact(root->next, aux);
    }
    
    return root;
}

Contact *menorNo(Contact *node) {
    Contact *aux = node;
    while (aux && aux->prev != NULL) {
        aux = aux->prev;
    }
    return aux;
}

Contact *delContact(Contact *root, char *name) {
    if (root==NULL) {
        return root;
    }
    // se name > root.name
    if (strcmp(name, root->name) < 0 ) {
        root->prev = delContact(root->prev,name);
    }
    // se name < root.name
    else if (strcmp(name, root->name) > 0) {
        root->next = delContact(root->next, name);
    }
    // se name == root
    else {
        // se tiver só um filho ou nenhum filho
        if (root->prev==NULL) {
            Contact *aux = root->next;
            free(root);
            return aux;
        }
        else if (root->next==NULL) {
            Contact *aux = root->prev;
            free(root);
            return aux;
        }
        Contact *aux = menorNo(root->next);
        strcpy(root->name, aux->name);
        strcpy(root->email, aux->email);
        strcpy(root->phone, aux->phone);
        root->next = delContact(root->next, aux->name);
    }
    return root;
}

int contaContatos(Contact* root) {
    if(root==NULL){
        return 0;
    }
    return (1 + contaContatos(root->prev) + contaContatos(root->next));
}

void copiaAgenda(Contatos *agenda, Contact *root, int i) {
    if(root!=NULL){
        strcpy(agenda[i].name, root->name);
        strcpy(agenda[i].email, root->email);
        strcpy(agenda[i].phone, root->phone);
        i++;
        copiaAgenda(agenda, root->prev, i);
        copiaAgenda(agenda, root->next, i+contaContatos(root->prev));
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
void listContacts(Contact *root) {
    int n = contaContatos(root);
    Contatos agenda[n];
    copiaAgenda(agenda, root, 0);
    mergeSort(agenda, 0, (n-1));
    if(n == 0){
        printf("\n\tAgenda está vazia.\n");
    }
    else{
        for (int i = 0; i < n; i++) {
            printf("\n\tNome: %s\n\tE-mail: %s\n\tTelefone: %s\n", agenda[i].name, agenda[i].email, agenda[i].phone);
        }
    }    
}

Contact *searchContact(Contact *root, char *name) {
    if(root == NULL){
        return NULL;
    }
    else if (strcmp(root->name, name) == 0){
        return root;
    }
    if (strcmp(root->name, name) > 0) {
        return searchContact(root->prev, name);
    }
    else {
        return searchContact(root->next, name);
    }
}

// Permite consultar um contato da agenda por nome
void queryContact(Contact *root, char *name) {
    Contact *contact = searchContact(root, name);
    if (contact == NULL) {
        printf("\n\tContato não existe.\n");
    } else {
        printf("\n\tNome: %s\n\tE-mail: %s\n\tTelefone: %s\n\n", contact->name, contact->email, contact->phone);
    }
    return;
}

Contact *readArq(Contact *root){
    Contact *aux;
    FILE *arq = fopen("Agenda.txt", "r");
    if(arq == NULL){
        FILE *arq = fopen("Agenda.txt", "w");
        return root;
    }
    fseek(arq, 0, SEEK_SET);
    while(!feof(arq)){
        aux = malloc(sizeof(Contact));
        fscanf(arq, "%s\n", aux->name);
        fscanf(arq, "%s\n", aux->email);
        fscanf(arq, "%s\n", aux->phone);
        root = insContact(root, aux);
    }
    fclose(arq);
    return root;
}

void writeArq(Contact *root){
    int n = contaContatos(root);
    Contatos agenda[n];
    copiaAgenda(agenda, root, 0);
    mergeSort(agenda, 0, (n-1));

    FILE *arq = fopen("Agenda.txt", "w+");
    fseek(arq, 0, SEEK_SET);
    if(arq == NULL){
        printf("Não foi possível acessar o arquivo!");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        fprintf(arq, "%s\n", agenda[i].name);
        fprintf(arq, "%s\n", agenda[i].email);
        fprintf(arq, "%s\n", agenda[i].phone);
    } 
    fclose(arq);
}


// Programa principal
int main() {

    int op=0;
    //Contact MContact;
    Contact *root, *aux;
    char name[40];    

    initializeTree(&root);

    root = readArq(root);

    while(op!=EXIT) {
        op = menu();
        switch(op) {
            case 1: 
                aux = malloc(sizeof(Contact));
                scanf("%*c");
                printf("\nNome: ");
                fgets(aux->name, sizeof(aux->name), stdin);
                aux->name[strcspn(aux->name, "\n")] = '\0';

                printf("Email: ");
                fgets(aux->email, sizeof(aux->email), stdin);
                aux->email[strcspn(aux->email, "\n")] = '\0';

                printf("Telefone: ");
                fgets(aux->phone, sizeof(aux->phone), stdin);
                aux->phone[strcspn(aux->phone, "\n")] = '\0';
                
                root = insContact(root, aux);
                break;
            case 2:
                scanf("%*c");
                printf("\nNome: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                if(searchContact(root, name)==NULL){
                    printf("\n\tContato não existe.\n");
                }
                else{
                    root = delContact(root, name);
                }
                break;
            case 3: 
                scanf("%*c");
                printf("\nNome: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                queryContact(root, name);
                break;
            case 4: 
                listContacts(root);        
                break;
        }
    }

    writeArq(root);

    return 0;
}