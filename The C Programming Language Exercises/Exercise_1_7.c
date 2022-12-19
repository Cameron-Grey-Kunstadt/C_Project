#include <stdio.h>

/* This code verifies getchar(0) != EOF is 0 or 1, when you enter a character normally, 
the code prints out that the computation equals 1, if you enter ctrl+z on a windows system, the value will equal 0, indicating EOF*/
void main(void){
	
	int c;
	
	for (int i = 0; i < 10; i++){
		printf("getchar() != EOF:  %d\n", (getchar() != EOF));
		if ((c = getchar()) != EOF){
			putchar(c);
		}
		
	} 
}