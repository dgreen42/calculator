#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Result {
	int result;
};

struct Opperation {
	char *left;
	char *right;
	char *opperation;
};


int add(int first, int second) {
	printf("Adding: %i + %i = %i\n", first, second, first + second);
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


void parseOperation(char **exp, struct Opperation* opp, struct Result *result) {
	int res;
	opp->left = exp[0];
	opp->opperation = exp[1];
	opp->right = exp[2];
	printf("%s", opp->opperation);
}

void parseExpression(char **exp, struct Result *result) {

	while (**exp != '\0') {
		printf("%c", **exp);
		switch(**exp) {
			case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
				struct Opperation *opp = (struct Opperation *)malloc(sizeof(struct Opperation));
				parseOperation(exp, opp, result);
				printf("%c", *opp->opperation);
				switch(*opp->opperation) {
					case '+': printf("+");
					case '-': printf("-");
					case '*': printf("* ");
					case '/': printf("/");
				}
				++*exp;
			default:
				if (**exp == *"(") {
					struct Opperation *opp = (struct Opperation *)malloc(sizeof(struct Opperation));
					parseOperation(exp, opp, result);
					printf("%c", *opp->opperation);
					switch(*opp->opperation) {
						case '+': printf("+");
						case '-': printf("-");
						case '*': printf("* ");
						case '/': printf("/");
					}
					++*exp;
				} else {
					/*
					switch(**exp) {
						case '+':
							printf("Opperation can only come after a number; exp\n");
							exit(-1);
						case '-':
							printf("Opperation can only come after a number; exp\n");
							exit(-1);
						case '*':
							printf("Opperation can only come after a number; exp\n");
							exit(-1);
						case '/':
							printf("Opperation can only come after a number; exp\n");
							exit(-1);
					}
					*/
					++*exp;
					parseExpression(exp, result);
				}
		}
	}
}


void removeWhiteSpace() {} // come back to this

int main(int argc, char **argv) {
	struct Result *result = (struct Result *)malloc(sizeof(struct Result));
	char *expression = "(1+2)";

	parseExpression(&expression, result);
	printf("Result: %i\n", result->result);
}
