#include <stdio.h>
#include "utils.h"

/*
 * DESCRIPTION:
 * 	This function parses a string of two signed integers, separated by
 * 	a space.
 *
 * PARAMETERS:
 * 	str:	The string containing the two signed integers separated by
 * 		a space.
 * 	coeff:	A pointer to the variable that this function will store 
 * 		the first integer parsed from this string. That is, the
 * 		variable that will store the coefficient of the polynomial
 * 		term.
 * 	expo:	A pointer to the variable that this function will store
 * 		the second integer parsed from this string. That is, the
 * 		variable that will store the exponent of the polynomial
 * 		term.
 */
void parse(char *str, int *coeff, int *expo) {
	sscanf(str,"%d %d",coeff,expo);
	
}

/*
 * DESCRIPTION:
 * 	Compute the power of base 'x' raised to expnent 'expo'
 *
 * PARAMETERS:
 * 	x:	The base of the power.
 * 	expo:	The exponent.
 *
 * RETURNS:
 * 	The integer that is the result of evaluating x raised to the 
 * 	exponent 'expo'. If the exponent is negative, it will be 
 * 	treated as 0, thus this method will return 1. 0^0 = 1.
 * 	Powers too large to be stores in ints are returned as the
 * 	maximum possible signed integer value (e.g. 5^15 or 150^5).
 */
int powi(int x, int expo) {

	long product = 1;
	int MAX_INT = max_int();

	for(int i = 0; i < expo; i++) {
		product *= x;

		// Edge-case: power too large to be stored in signed int.
		if ( product > MAX_INT )
			return MAX_INT;
	}

	return (int) product; // Always < MAX_INT
}

/*
 * RETURNS:
 * 	The maximum value of signed int on this system.
 */
int max_int(void) {
	#pragma GCC diagnostic ignored "-Woverflow" // Suppress overflow warning
	const static int MAX_INT = (1 << (sizeof(int) * 8 - 1)) - 1;
	return MAX_INT;
}


//For tests [DELETE LATER]
/*int main(void)
{

	int coeff;
	int expo;

	parse("12 2",&coeff,&expo);
	parse("3 2",&coeff,&expo);
	parse("1 0",&coeff,&expo);
	parse("0 0",&coeff,&expo);
	int product=powi(coeff,expo);
	printf("product: %d",product);
}*/



