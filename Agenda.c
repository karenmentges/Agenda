/* 
*   Pesquisa e ordenação de dados
*   Trabalho Final
*   Acadêmicas: Karen Ruver Mentges (matrícula: 1921100003)
*               Izabela Fusieger (matrícula: 1921101019)
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
	struct MREC *right;
	struct MREC *left;
};

// Tipo criado para instanciar variaveis do tipo agenda
typedef struct MREC Contact;

typedef struct {
    char name[30];
    char email[40];
    char phone[15];
} Contatos;


// Função que apresenta o menu da aplicação e retorna a opção selecionada
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

// Função que permite o cadastro de um contato
Contact *insContact(Contact *root, Contact *aux) {
    if(root==NULL){
        root = malloc(sizeof(Contact));
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

// Função que retorna o menor nó da árvore
Contact *menorNo(Contact *node) {
    Contact *aux = node;
    while (aux && aux->left != NULL) {
        aux = aux->left;
    }
    return aux;
}

// Função que permite deletar um contato
Contact *delContact(Contact *root, char *name) {
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
            Contact *aux = root->right;
            free(root);
            return aux;
        }
        else if (root->right==NULL) {
            Contact *aux = root->left;
            free(root);
            return aux;
        }
        // se tiver dois, procura o menor na subarvore da direita, copia dados e o deleta
        Contact *aux = menorNo(root->right);
        strcpy(root->name, aux->name);
        strcpy(root->email, aux->email);
        strcpy(root->phone, aux->phone);
        root->right = delContact(root->right, aux->name);
    }
    return root;
}

// Função que conta quantos contatos tem na árvore
int contaContatos(Contact* root) {
    if(root==NULL){
        return 0;
    }
    return (1 + contaContatos(root->left) + contaContatos(root->right));
}

// Função que copia os contatos da árvore para um vetor de contatos
void copiaAgenda(Contatos *agenda, Contact *root, int i) {
    if(root!=NULL){
        strcpy(agenda[i].name, root->name);
        strcpy(agenda[i].email, root->email);
        strcpy(agenda[i].phone, root->phone);
        i++;
        copiaAgenda(agenda, root->left, i);
        copiaAgenda(agenda, root->right, i+contaContatos(root->left));
    }
}

// Função de ordenação dos contatos
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

// Função que lista o conteudo da agenda (todos os campos)
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

// Função que busca um contato da agenda por nome
Contact *searchContact(Contact *root, char *name) {
    if(root == NULL){
        return NULL;
    }
    else if (strcmp(root->name, name) == 0){
        return root;
    }
    if (strcmp(root->name, name) > 0) {
        return searchContact(root->left, name);
    }
    else {
        return searchContact(root->right, name);
    }
}

// Função que permite consultar um contato da agenda por nome
void queryContact(Contact *root, char *name) {
    Contact *contact = searchContact(root, name);
    if (contact == NULL) {
        printf("\n\tContato não existe.\n");
    } else {
        printf("\n\tNome: %s\n\tE-mail: %s\n\tTelefone: %s\n\n", contact->name, contact->email, contact->phone);
    }
    return;
}

// Função que lê o arquivo Agenda.txt e adiciona o conteúdo na árvore
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
        fgets(aux->name, 30, arq);
        aux->name[strcspn(aux->name, "\n")] = '\0';
        fscanf(arq, "%s\n", aux->email);
        fscanf(arq, "%s\n", aux->phone);
        root = insContact(root, aux);
    }
    fclose(arq);
    return root;
}

// Função que escreve o conteúdo da árvore no arquivo Agenda.txt
void writeArq(Contact *root){
    int n = contaContatos(root);
    Contatos agenda[n];
    copiaAgenda(agenda, root, 0);

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
    return;
}


// Programa principal
int main() {

    int op = 0;
    Contact *MContact, *aux;
    char name[40];    

    initializeTree(&MContact);

    MContact = readArq(MContact);

    while(op!=EXIT) {
        op = menu();
        switch(op) {
            case 1:
                aux = malloc(sizeof(Contact));
                scanf("%*c");
                printf("\nInforme o nome do contato que deseja inserir: ");
                fgets(aux->name, sizeof(aux->name), stdin);
                aux->name[strcspn(aux->name, "\n")] = '\0';

                printf("Informe email do contato: ");
                fgets(aux->email, sizeof(aux->email), stdin);
                aux->email[strcspn(aux->email, "\n")] = '\0';

                printf("Informe seu telefone do contato: ");
                fgets(aux->phone, sizeof(aux->phone), stdin);
                aux->phone[strcspn(aux->phone, "\n")] = '\0';
                
                MContact = insContact(MContact, aux);
                break;
            case 2:
                scanf("%*c");
                printf("\nInforme o nome do contato a ser deletado: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                if(searchContact(MContact, name)==NULL){
                    printf("\n\tContato não existe.\n");
                }
                else{
                    MContact = delContact(MContact, name);
                }
                break;
            case 3:
                scanf("%*c");
                printf("\nInforme o nome do contato que deseja consultar: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                queryContact(MContact, name);
                break;
            case 4:
                printf("\nLista de Contatos\n");
                listContacts(MContact);        
                break;
        }
    }

    writeArq(MContact);

    return 0;
}