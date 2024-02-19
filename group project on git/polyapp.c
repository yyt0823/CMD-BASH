#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "poly.h"
#include "utils.h"


int main(int argc, char *argv[]){
// Start by extracting coefficients and exponents from csv using parse (from utils) and add it to the polynomial using the addPolyTerm (from poly)
	FILE *file = fopen(argv[1], "r");
	if (file == NULL) {
		printf("Error opening file");
		return -1; // Error opening file
	}
	int coeff, expo;
	char line[100];
	while(fgets(line, sizeof(line), file) != NULL){
		parse(line, &coeff, &expo);
		if (addPolyTerm(coeff, expo)==-1){
			printf("Error adding polyTerm");
			return -1;
		}
	}
	fclose(file);
		//If addPolyTerm fails, print an appropriate message and terminate your program from the main function

//when all the polynomial terms are read and the polynomial is constructed, the main should call display Polynomial to print the polynomial expression to the screen
	displayPolynomial();
//Then the main function should call evaluatePolynomial for the values -2, -1 ,0 ,1, 2 in that order and print the results
	for (int i=-2;i<=2; i++){
		int result = evaluatePolynomial(i);
		printf("For x=%d, y=%d\n",i,result);
	}

}
