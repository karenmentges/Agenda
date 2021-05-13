#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  

#define BLC_MEMORIA 3
#define N_VALUES 7
#define N_FILES 2

struct agenda
{
   char name[15];
   char address[30];
   int  age;
};
typedef struct agenda Agenda;

const int LEN = sizeof(Agenda);
const int MAXREC= 10;

void externalSort(char *arqName, int n);
FILE *combinaBlocos( FILE *arqEnt[], int blocoId, int nFile, int iter);


void merge(Agenda *A, int p, int q, int r);
void mergeSort(Agenda *A, int p, int r);


void imprimeAgenda(Agenda *A, int n);
Agenda *geraDadoAleatorios( int n);
void armazenaDados (FILE *arq, Agenda *A, int n);

int main() {

   int qt, ts, i;
   size_t tRead; // size_t equivalente ao int
   Agenda *mAg; // exatamente igual ag mAg[MAXREC];
   Agenda p;
   char *nomearq="Agenda.dat"; // ou char nomeArq[]="Agenda.dat"
   FILE *arq;

   //Geração dos dados e do arquivo inicial
   mAg = geraDadoAleatorios(N_VALUES);
   arq = fopen(nomearq, "w+b");
   armazenaDados(arq, mAg, N_VALUES);
   free(mAg);
   fclose(arq);

   printf("\n\nSem ordenar:\n\n");
   imprimeAgenda(mAg, N_VALUES);

   externalSort(nomearq,N_VALUES);
   mAg = malloc(sizeof(Agenda)*N_VALUES);
   fseek(arq, 0, SEEK_SET);
   fread(mAg, sizeof(Agenda), N_VALUES, arq);
   
   printf("\n\nOrdenada:\n\n");
   imprimeAgenda(mAg, N_VALUES);

   
   return 0;
}



void mergeSort(Agenda *A, int p, int r)
{
   if (p<r-1) {
      int q=(int) (p+r)/2;
      mergeSort(A,p,q);
      mergeSort(A,q,r);
      merge(A,p,q,r);
   }
}

void merge (Agenda *A, int p, int q, int r)
{
   int i, j, k;
   Agenda B[r-p];
   i = p; j = q;
   k = 0;

   while (i < q && j < r) {
      if (A[i].age <= A[j].age)  B[k++] = A[i++];
      else  B[k++] = A[j++];
   }
   while (i < q)  B[k++] = A[i++];
   while (j < r)  B[k++] = A[j++];
   for (i = p; i < r; ++i)  A[i] = B[i-p];
}

Agenda *geraDadoAleatorios(int n){
   int i;
   Agenda *ag = (Agenda *) malloc (sizeof(Agenda)*n);
   srand(time(NULL)); // gera a semente aleatoria
   for (i=0;i<n;i++){
      ag[i].age = rand()%100;
      snprintf(ag[i].name,sizeof(ag[i].name), "Pessoa %d", i);
      snprintf(ag[i].address,sizeof(ag[i].address), "End %d", i);
   }
   return ag;
}

void imprimeAgenda(Agenda *A, int n){
    int i;
    printf("\n********** Agenda ************ %ld\n\n", sizeof A);
    for (i=0; i< n; i++){
        printf("Record %d: \n\t->name: %s \n\t->age: %d \n\t->address: %s\n", i, A[i].name, A[i].age, A[i].address );
    }
    printf("\n******************************\n\n");
}

void armazenaDados (FILE *arq, Agenda *A, int n){
   fseek(arq,0,SEEK_SET);
   fwrite(A, sizeof(Agenda), n, arq);
}

void externalSort(char *arqName, int n){
   FILE *auxFile[N_FILES];
   FILE *arq;
   Agenda *agBloco = malloc (sizeof(Agenda)*BLC_MEMORIA);
   int size;

   //Primeira fase: ler os dados e colocar nos diferentes arquivos.
   arq = fopen(arqName, "r+b");
   for (int i = 0; i<N_FILES; i++){
      char fileName[40];
      snprintf(fileName, 40, "%s-%d.aux", "arquivo", i);
      auxFile[i] = fopen(fileName, "w+b");
   }
  
   size = fread(agBloco, sizeof(Agenda), BLC_MEMORIA, arq);
   int i = 0;
   while (size > 0){    
      mergeSort(agBloco, 0, size);
      fwrite(agBloco, sizeof(Agenda), size, auxFile[i%N_FILES]);
      i++;
      size = fread(agBloco, sizeof(Agenda), BLC_MEMORIA, arq);
   }
   int numBloco = (i+1)/N_FILES; //numero total de blocos gravados dividido pelo numero de files.
   
   //Segunda fase: intercalação
   FILE **arquivosEntrada = auxFile;
   FILE **arquivosSaida;
   int iteracao = 0;
   while (numBloco > 0){
      arquivosSaida = (FILE **) malloc (sizeof(FILE *)*numBloco);
      for (int j = 0 ; j<numBloco;j++){
         arquivosSaida[j] = combinaBlocos(arquivosEntrada, j+1, N_FILES, iteracao);
      }
      
      numBloco=numBloco/N_FILES;
      iteracao++;
      arquivosEntrada = arquivosSaida;
   }

   //A principo se chegar aqui terminou
   fseek(arq, 0, SEEK_SET);
   fseek(arquivosSaida[0], 0, SEEK_SET);

   size = fread(agBloco, sizeof(Agenda), BLC_MEMORIA, arquivosSaida[0]);
   while (size > 0){
      //printf("\n--Leu: %d %s", agBloco[0].age, agBloco[0].name);
      fwrite(agBloco, sizeof(Agenda), size, arq);
      size = fread(agBloco, sizeof(Agenda), BLC_MEMORIA, arquivosSaida[0]);
   }
}

FILE *combinaBlocos( FILE *arqEnt[], int blocoId, int nFile, int iter){
   char fileName[40];
   snprintf(fileName, 40, "%s%d-%d.aux", "arquivo", blocoId, iter);
   FILE *resposta = fopen(fileName, "w+b");
   int i;
   int *counter = calloc(nFile, sizeof(int));

   for (i=0; i<nFile; i++)
      fseek(arqEnt[i], (blocoId-1)*BLC_MEMORIA*sizeof(Agenda) , SEEK_SET);

   Agenda *auxRead = malloc (sizeof(Agenda)*nFile);
  
   int *lidos = calloc(nFile, sizeof(int));

   int bool=1;   
   while(bool){
      int candidatoEscrita = -1;

      //Le os elementos
       for (i=0; i<nFile; i++){
         int readSize = -1;
         if (!lidos[i] && counter[i] < (blocoId*BLC_MEMORIA*(iter+1))){
            readSize = fread(&auxRead[i], sizeof(Agenda), 1, arqEnt[i]);
            lidos[i]++;
            //printf("leu %d! %d\n %s, %s\n",i, auxRead[i].age, auxRead[i].name, auxRead[i].address);
         }
         if (readSize == 0){
            lidos[i] = -1;
            //printf("Não leu ninguem!\n");
         }
         if (candidatoEscrita < 0 && lidos[i]>0)
            candidatoEscrita = i;
      }  

      for(i=1; i<nFile; i++){
         if (lidos[i] > 0)
            if (auxRead[i].age < auxRead[candidatoEscrita].age){
               candidatoEscrita = i;
            }
      }

      if (candidatoEscrita < 0){
         break;
      }

      fwrite(&auxRead[candidatoEscrita], sizeof(Agenda), 1, resposta);
      
      lidos[candidatoEscrita] = 0;
      counter[candidatoEscrita] ++;

      int soma = 0, endedFiles = 0;
      for (i = 0; i<nFile;i++){
         soma+=counter[i];
         if (feof(arqEnt[i])) 
            endedFiles++;
      }
     
      if (soma >= BLC_MEMORIA*nFile*(iter+1)){
         bool = 0; 
      }
   }

   return resposta;
}