#include <stdio.h>
#include <string.h>

int main(){
    int N,j,i;
    char aux[11];
    printf("digite a quantidade de nomes ");
    scanf("%d", &N);
    getchar();
    char nomes[N][11];
    for(i=0;i<N;i++){
        printf("digite o %d nome ",i+1);
		scanf("%[^\n]s",nomes[i]);
		getchar();
	}
	printf("\naqui estão os nomes na ordem digitados\n");
	for(i=0;i<N;i++){
		printf("%s\n",nomes[i]);
	}
	for(i=0;i<N;i++){
        for(j=i+1;j<N;j++){
            if( nomes[i][0]>nomes[j][0]){
                strcpy(aux,nomes[i]);
                strcpy(nomes[i],nomes[j]);
                strcpy(nomes[j],aux);
            }
        }
	}
	printf("\naqui os nomes em ordem crescente\n");
	for(i=0;i<N;i++){
		printf("%s\n",nomes[i]);
	}
	return 0;
}