#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "poly.h"

//head of the linked list
//NOTE: I defined the struct 'PolyTerm' for each node in the linked list 
//(i.e each term in the polynomial) in the header file 'poly.h'
//the struct has three members: two int variables named coeff and one Polyterm pointer pointing to the next linked node
struct PolyTerm *head=NULL;


// Louis & Yantian

/* DESCRIPTION:
 * 	This function accepts two integer arguments (a coefficient and exponent) and
 * 	adds that term into the existing Polynomial. If the polynomial already has
 * 	a term with the same exponent as the one provided, this method will update
 * 	the coefficient instead of adding a new term. Terms are listed in descending
 * 	order of exponents.
 *
 * PARAMETERS:
 * 	coeff:	The integer coefficient of the term to add
 * 	expo:	The exponent of x. Any integer < 0 will be ignored and considered 0.
 *
 * RETURN:
 * 	0:	Success
 * 	-1:	Failure (e.g. out of memory for a new node)
 */
int addPolyTerm(int coeff, int expo) {

	//Here is the repartition I tought of:
	//Yantian makes a function that sorts the lists in ascending exponential order
	



	//function from yantian, this part should do the addPolyTerm by itself.
	


	struct PolyTerm *current = head;
    	struct PolyTerm *prev = NULL;

	//iterate and finds
    	while (current != NULL && current->expo < expo) {
        	prev = current;
       		current = current->next;
    	}

	//same expo, update
    	if (current != NULL && current->expo == expo) {
        	current->coeff += coeff;
        	return 0;
    	}

	//create new node 
	struct PolyTerm *newTerm = (struct PolyTerm* )malloc(sizeof(struct PolyTerm));
    	      if (newTerm == NULL) {
        	return -1;
    	}
    	newTerm->coeff = coeff;
    	newTerm->expo = expo;

    	// Insert new node 
    	if (prev == NULL) {
        	newTerm->next = head;
        	head = newTerm;
    	} else {
       		newTerm->next = prev->next;
        	prev->next = newTerm;
    	}

    	return 0;




	//Louis does addPolyTerm
	//(or vice-versa, but the person that makes the sorting function should probably the one
	//that also does displayPolynomial)
}


// Yantian

/*
 * DESCRIPTION:
 * 	display the polynomial expression in increasing order of exponents. It will 
 * 	not include the hat symbol (circumflex). For example, an output could be 
 * 	0x2+12x3+4x5.
 */
void displayPolynomial()
{
	//pointing to head
	struct PolyTerm *current = head;
	//check if head is null
	if (current == NULL) {
        	printf("0\n");
        	return;
    	}
	//iterate and print axb+
	while(current->next!=NULL){	
		printf("%dx%d+",current->coeff,current->expo);
		current = current->next;
	}
	//print the last polyterm with out the +
	printf("%dx%d\n",current->coeff,current->expo);

}

// Alexander

/*
 * DESCRIPTION:
 * 	This function evaluates the polynomial stored in this runtime with a given
 * 	value of 'x'. 
 *
 * PARAMETERS:
 * 	x:	The variable 'x' value to use in the evaluation.
 *
 * RETURN:
 * 	This function returns the sum of all evaluated terms in this polynomial.
 * 	If the sum is larger than what an int can represent, the maximum value
 * 	of 'int' is returned.
 */
int evaluatePolynomial(int x)
{
	int MAX_INT = max_int();

	// Traverse polynomial
	long sum = 0;
	for (struct PolyTerm* t = head; t != NULL; t = t->next) {
		long term = t->coeff * powi(x , t->expo);
		sum += term;

		// Break if the sum exceeds the maximum integer value
		if ( sum >= MAX_INT )
			return MAX_INT;
	}

	return (int) sum; // Will always be < MAX_INT
}


