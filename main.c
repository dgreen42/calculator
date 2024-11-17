#include <stdio.h>
#include <stdlib.h>
#include <string.h>




// brackets
//
// exponent
//
// mult
//
// div
//
// sub
//
// add
//

int parseExpression(char **exp, int size) {

	/*
	for (int i = 0; i < sizeof(*exp); i++) {
		if (strcmp(exp[i], "(")) {
			
			if (strcmp(exp[i], ")")) {
				//return to the rest of the expression
			}
		}
	}
	*/

	int result;
	for (result = 0 ; **exp != '\0'; ++*exp) {
		if (strcmp(*exp, "(")) {
			printf("bracket open, %s", *exp);
			if (strcmp(*exp, ")")) {
				printf("bracket close, %s", *exp);
				//return to the rest of the expression
			}
		}
	}

	return result;
}

int add(int first, int second) {
	return first + second;
}

int subtract(int first, int second) {
	return first - second;
}

int multiply(int first, int second) {
	return first * second;
}

int divide(int first, int second) {
	// add divide by zero exception
	return first / second;
}

void removeWhiteSpace() {} // come back to this

int main(int argc, char **argv) {
	char *expression = "(1+2)";
	
	int sum = parseExpression(&expression, sizeof(&expression));
}
