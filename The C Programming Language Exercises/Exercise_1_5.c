#include <stdio.h>

/* print Fahrenheit-Celsius table
for fahr = 0, 20, ..., 300; floating-point version */

void main(void){
    
    float fahr, celsius;
    int lower, upper, step;
    
    lower = 0; // lower limit of temp table
    upper = 300; // upper limit
    step = 20; // step size
    
    fahr = upper;
    
    printf("%s %s\n", "fahr", "celsius");// I think this looks fine,the 3.0 and 6.1 spacing doesn't look right 
    
    while (fahr >= lower){
        celsius = (5.0/9.0) * (fahr-32.0);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr - step;
    }
    
}