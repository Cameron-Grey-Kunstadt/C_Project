#include <stdio.h>

/* print the reverse Fahrenheit-Celsius table
for Celsius  = 0, 20, ..., 300; floating-point version */

void main(void){
    
    float celsius, fahr;
    int lower, upper, step;
    
    lower = 0; // lower limit of temp table
    upper = 300; // upper limit
    step = 20; // step size
    
    celsius = lower;
    
    printf("%s %s\n", "celsius", "fahr");// I think this looks fine,the 3.0 and 6.1 spacing doesn't look right 
    
    while (celsius <= upper){
        fahr= (((9.0/5.0) * (celsius)) + 32.0);
        printf("%3.0f %6.1f\n", celsius, fahr);
        celsius= celsius + step;
    }
    
}