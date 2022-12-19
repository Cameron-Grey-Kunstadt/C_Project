#include <stdio.h>

void main(void){

	int white_space = 0;
	int c;
	
	while ((c = getchar()) != EOF){
		if (c == ' ' || c == '\n' || c == '\t'){
			white_space++;
		}			
		printf("Total white space: %d\n", white_space);
	}
}