#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
   int i,j;
   char nomes[3][40] = {"Izabela Fusieger", "Ana Vargas", "Beatriz Pereira"};
   char temp[40];
    
   for(i=0;i<3;i++) {
      for(j=i+1;j<3;j++){
         if(strcmp(nomes[i],nomes[j])>0){
            strcpy(temp,nomes[i]);
            strcpy(nomes[i],nomes[j]);
            strcpy(nomes[j],temp);
         }
      }
   }

   for(i=0;i<3;i++) {
      printf("%s\n", nomes[i]);
   }
    
    return 0;
}
