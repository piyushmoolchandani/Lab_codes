#include<stdio.h>

int main(){
	int a;
	for(a = 0; a < 5; a++){
		printf("%d", a);
		for (int j = 0; j < 3; j++){
			printf("\t how you doing %d", j);
			for (int l = 0; l < 2; l++){
				printf(" hey ");
			}
			for (;3 > 7;){
				continue;
			}
			while(2 > 9){
				continue;
			}
		}
		printf("\n");
	}
	// above loop simply prints the value of a
}
