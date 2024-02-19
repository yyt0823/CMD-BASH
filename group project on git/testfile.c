#include <stdio.h>
#include <string.h>
#include "utils.c"
#include "poly.c"

struct Section {
	struct Section* previous;
	char name[64];
	int test_count;
	int pass_count;
};

struct Section* sections_tail = NULL;
int section_passes = 0;
int section_total_tests = 0;

void begin_tests();
void section(char text[]);
void end_tests();
void test_parse(char test_name[], char input[], int expected_coefficient, int expected_exponent);
void test_eval_poly();
void assert_eq();

int main() {

	// UNIT TESTS
	begin_tests();

	// Test parse() in utils.c
	section("PARSE()");
	test_parse("Identical positives",	"1 1",		1,   1);
	test_parse("Different positives",	"2 5",		2,   5);
	test_parse("Identical negatives",	"-2 -2",	-2, -2);
	test_parse("Different negatives",	"-6 -3",	-6, -3);
	test_parse("Both zero",			"0 0",		0,   0);
	test_parse("Empty string",		"",		0,   0);
	test_parse("Only coefficient",		"3",		3,   0);
	test_parse("Gibberish",			"nhb83g4",	0,   0);
	test_parse("Comma-separator",		"5, 19",	5,   19);
	test_parse("Extra whitespace",		"  7  23  ",	7,   23);
	test_parse("One number invalid", 	"a 12",		0,   12);
	test_parse("Coefficient larger than int max value.",	"76886882687423421 1", 0, 0);

	// powi(b,e)
	section("POWI()");
       	assert_eq("3^2", 9, powi(3,2));
	assert_eq("3^0", 1, powi(3,0));
	assert_eq("0^3", 0, powi(0,3));
	assert_eq("0^0", 1, powi(0,0));
	assert_eq("(-5)^2", 25, powi(-5,2));
	assert_eq("(-5)^3", -125, powi(-5,3));
	assert_eq("5^(-3)", 1, powi(5,-3));
	assert_eq("5^15", max_int(), powi(5,15));	
	assert_eq("150^5", max_int(), powi(150,5));	

	// evaluatePolynomial()
	section("EVALUATE_POLYNOMIAL()");
	test_eval_poly("Empty polynomial", 0, NULL, NULL, 5, 0);
	test_eval_poly("0x^0, x=5", 1, (int[]){0}, (int[]){0}, 5, 0);
	test_eval_poly("1x^0, x=5", 1, (int[]){1}, (int[]){0}, 5, 1);
	test_eval_poly("1x^1, x=5", 1, (int[]){1}, (int[]){1}, 5, 5);
	test_eval_poly("2x^1, x=5", 1, (int[]){2}, (int[]){1}, 5, 10);
	test_eval_poly("1x^2, x=5", 1, (int[]){1}, (int[]){2}, 5, 25);
	test_eval_poly("2x^2 + 3x^1 + 5, x=5",	3,	(int[]){2, 3, 5}, 	(int[]){2, 1, 0}, 5, 70);
	test_eval_poly("2x^2 + 3x^1 + 5, x=-5",	3, 	(int[]){2, 3, 5}, 	(int[]){2, 1, 0}, -5, 40);
	test_eval_poly("Sum > int max value",	3, 	(int[]){1, 1, 1}, 	(int[]){5, 5, 5}, 70, max_int());
	test_eval_poly("Power > int max value (1*5^15)", 1, (int[]){1}, 	(int[]){15}, 5, max_int());
	test_eval_poly("Power > int max value (1*150^5)", 1, (int[]){1}, 	(int[]){5}, 150, max_int());

	end_tests();
}

void header(char text[]) {
	printf("\n\n\x1B[1m\x1B[7m======== %s =========\x1B[K\x1B[0m\n\n", text);
}

// Begin unit testing
void begin_tests() {
	header("BEGIN UNIT TESTING");
	sections_tail = NULL;
}

// End unit testing
void end_tests() {

	if ( sections_tail != NULL )
		section_summary();

	header("END OF UNIT TESTING");

	// Print section summaries
	printf("\x1B[1m\x1B[7m \x1B[4mTEST SUMMARY:\x1B[24m\x1B[K\x1B[0m\n");
	for ( struct Section* t = sections_tail ; t != NULL; t = t->previous ) {
		printf("  \x1B[1m%-25s \x1B[0m\x1B[1m %s%-2d PASSED    %-2d FAILED\x1B[0m\n",
		       t->name,
		       t->pass_count < t->test_count ? "\x1B[31m" : "\x1B[32m",
		       t->pass_count,
		       t->test_count - t->pass_count);
	}
	//printf("\x1B[7m\x1B[K\x1B[0m\x1B[0m\n"); // Reset font to default
}

// Print section pass/fail summary
void section_summary() {
	int total = sections_tail->test_count;
	int pass = sections_tail->pass_count;

	printf("\n\x1B[1m\x1B[7mSUMMARY FOR %s:%s %d/%d tests passed.\x1B[0m\n", 
   	       sections_tail->name,
	       pass < total ? "\x1B[31m" : "\x1B[32m",
	       pass,
	       total);
}

// Start new test section
void section( char text[] ) {

	// Print summmary for previous section
	if ( sections_tail != NULL )
		section_summary();

	// Section header
	header(text);

	// New section
	struct Section* s = (struct Section*) malloc( sizeof( struct Section ) );
	strcpy(s->name, text);
	s->previous = sections_tail;
	sections_tail = s;
}

// 0 for fail, 1 for pass
void record_test(int status) {
	sections_tail->test_count++;
	sections_tail->pass_count += status == 1;
}

// Assert that expected == actual otherwise print error
void assert_eq(char* test_name, int expected, int actual) {
	char fail_msg[30];
	sprintf(fail_msg, " (%d expected, %d given)", expected, actual);
	printf(	"%-20s | \033[1m%-4s %s\x1B[0m\n", 
		test_name, 
		expected == actual ? "\x1B[32mPASS" : "\x1B[31mFAIL", 
		expected != actual ? fail_msg : "" );
	record_test( expected == actual );
}

// Test the parse() method in utils
void test_parse(char test_name[], char input[], int expected_a, int expected_b) {
	int a = -1, 
	    b = -1;
	parse( input, &a, &b );
	printf("parse() test: %s\n", test_name);
	assert_eq( "  coefficient", expected_a, a );
	assert_eq( "  exponent", expected_b, b );
}

// Test the evaluatePolynomial() method in poly.c
void test_eval_poly(char test_name[], int num_terms, int coefficients[], int exponents[], int x, int expected_sum) {
	head = NULL;
	struct PolyTerm* previous = NULL;

	// Construct LL
	for ( int i = 0; i < num_terms; i++ ) {
		struct PolyTerm *t = (struct PolyTerm*) malloc( sizeof (struct PolyTerm) );
		t->coeff = coefficients[i];
	       	t->expo = exponents[i];	
		if ( previous == NULL )
			head = t;
		else
			previous->next = t;
		previous = t;
	}
	
	// Compute and compare sum
	int actual_sum = evaluatePolynomial(x);
	char full_test_name[128];
	sprintf(full_test_name, "evaluatePolynomial(): %s", test_name);
	assert_eq(full_test_name, expected_sum, actual_sum);

	// Free LL
	for ( struct PolyTerm* t = head; t != NULL; ) {
		struct PolyTerm* to_free = t;
		t = t->next;
		free( to_free );
	} 
}
