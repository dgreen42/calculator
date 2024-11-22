#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

struct Number *number(char** exp);
struct Modifier *modifier(char** exp);
struct Expression *expression(char** exp);
struct Group *group(char** exp);
struct Item *item(char** exp);
struct Term *term(char** exp);
struct Start *start(char** exp);
void parse(char **exp);

struct Number {
	char content;
	char after[8];
};

struct Modifier {
	char content;
	char after[8];
};

struct Expression {
	struct Term *term;
	struct Expression *next;
	char after[8];
};

struct Group {
	struct Expression *content;
	char after[8];
};

struct Item {
	char content;
	char after[8];
};

struct Term {
	struct Item *item;
	struct Group *group;
	char after[8];
};

struct Start {
	struct Expression *content;
};

int is_number(char** c) {
	if (!c) {
		return 0;
	}
	switch(**c) {
		case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': 
			return 1;
		default:
			return 0;
	}
}

int is_symbol(char** c) {
	if (!c) {
		return 0;
	}
	switch (**c) {
		case '+': case '-': case '*': case '/':
			return 1;
		default:
			return 0;
	}
}


struct Number *number(char** exp) {
	if (!exp) {
		printf("Missing expression fn number\n");
		exit(1);
	}

	if (is_number(&exp[0]) == 1) {
		struct Number *num = (struct Number *)malloc(sizeof(struct Number));

		if (!num) {
			printf("Failed to allocate memory for number\n");
			exit(1);
		}
		num->content = *exp[0];
		char* after = *exp+1;
		memcpy(num->after, after, strlen(after));

		if (!num->after) {
			printf("Failed to copy memory for expression after number\n");
			exit(1);
		}
		printf("num content: %c\n", num->content);
		printf("num after: %s\n", num->after);

		return num;
	}

	return NULL;
}


struct Modifier *modifier(char** exp) {
	if (!exp) {
		printf("Missing expression fn modifier\n");
		exit(1);
	}

	if (is_symbol(&exp[0]) == 1) {
		struct Modifier *mod = (struct Modifier *)malloc(sizeof(struct Modifier));

		if (!mod) {
			printf("Failed to allocate memory for modifier\n");
			exit(1);
		}
		mod->content = *exp[0];
		char* after = *exp+1;
		printf("after mod: %s\n", after);
		memcpy(mod->after, after, strlen(after));

		if (!mod->after) {
			printf("Failed to copy memory for expression after modifier\n");
			exit(1);
		}
		printf("mod content: %c\n", mod->content);
		printf("mod after: %s\n", mod->after);

		return mod;
	}

	return NULL;
}

struct Expression *expression(char* exp[8]) {
	if (!exp) {
		printf("Missing expression fn expression\n");
		exit(1);
	}

	if (term(exp) != NULL) {
		struct Term *trm = term(exp);

		if (!trm) {
			printf("Term allocation failure\n");
			exit(1);
		}

		if (expression(&trm->after) != NULL) {
			struct Expression *expr = expression(&trm->after);

			if (!expr) {
				printf("Expression allocation failure\n");
				exit(1);
			}
			struct Expression *fin_expr = (struct Expression *)malloc(sizeof(struct Expression));

			if (!fin_expr) {
				printf("Failed to allocate memory for expression\n");
				exit(1);
			}
			fin_expr->term = trm;
			fin_expr->next = expr;
			char *after = *exp+sizeof(*trm);
			memcpy(fin_expr->after, &after, strlen(after));

			if (!fin_expr->after) {
				printf("Failed to copy memory for expression after expression\n");
				exit(1);
			}
			printf("fin_expr after: %s\n", fin_expr->after);

			free(trm);
			free(expr);

			return fin_expr;
		}

		struct Expression *fin_expr = (struct Expression *)malloc(sizeof(struct Expression));

		if (!fin_expr) {
			printf("Failed to allocate memory for expression\n");
			exit(1);
		}
		fin_expr->term = trm;
		fin_expr->next = NULL;
		char *after = *exp+sizeof(*trm);
		printf("sizeof *exp: %lu\n", sizeof(*exp)); //size 8
		printf("sizeof trm: %lu\n", sizeof(*trm)); //size 24
		printf("strlen after: %lu\n", strlen(after)); //strlen 0
		printf("sizeof after: %lu\n", sizeof(after)); //size 8
		printf("sizeof fin_expr->after: %lu\n", sizeof(fin_expr->after)); //sizeof 8
		memcpy(fin_expr->after, &after, strlen(after));

		if (!fin_expr->after) {
			printf("Failed to copy memory for expression after expression\n");
			exit(1);
		}

		printf("fin_expr after: %s\n", fin_expr->after);
		free(trm);

		return fin_expr;
	}

	return NULL;
}

struct Group *group(char* exp[8]) {
	if (!exp) {
		printf("Missing expression fn group\n");
		exit(1);
	}

	if (*exp[0] == *"(") {
		char* after = *exp+1;

		if (expression(&after) != NULL) {
			struct Expression *expr = expression(&after);
			if (!expr) {
				printf("Expression allocation failure\n");
				exit(1);
			}
			if (expr->after[0] == *")") {
				struct Group *grp = (struct Group *)malloc(sizeof(struct Group));
				if (!grp) {
					printf("Failed to allocate memory for group\n");
					exit(1);
				}

				grp->content = expr;
				if (sizeof(expr->after) > sizeof(grp->after)) {
					printf("Group overflow\n");
					exit(1);
				}
				memcpy(grp->after, expr->after, sizeof(expr->after));
				printf("gorup after: %s\n", grp->after);

				return grp;
			}
		}
	}

	return NULL;
}

struct Item *item(char* exp[8]) {
	if (!exp) {
		printf("Missing expression fn item\n");
		exit(1);
	}

	//come back to this. Not sure if the way that after is being assigned is correct. Needs testing
	if (number(exp) != NULL) {
		struct Number *num = number(exp);

		if (!num) {
			printf("Number allocation failure\n");
			exit(1);
		}
		struct Item *itm = (struct Item *)malloc(sizeof(struct Item));
		if (!itm) {
			printf("Failed to allocate memory for item\n");
			exit(1);
		}
		itm->content = num->content;

		if (sizeof(num->after) > sizeof(itm->after)) {
			printf("Item overflow for number\n");
			exit(1);
		}
		memcpy(itm->after, num->after, sizeof(num->after));
		printf("item after: %s\n", itm->after);
		free(num);

		return itm;
	}

	if (modifier(exp) != NULL) {

		struct Modifier *mod = modifier(exp);
		if (!mod) {
			printf("Modifier allocation failure\n");
			exit(1);
		}
		struct Item *itm = (struct Item *)malloc(sizeof(struct Item));
		if (!itm) {
			printf("Failed to allocate memory for item\n");
			exit(1);
		}
		itm->content = mod->content;

		if (sizeof(mod->after) > sizeof(itm->after)) {
			printf("Item overflow for modifier\n");
			exit(1);
		}
		memcpy(itm->after, mod->after, sizeof(mod->after));
		printf("item after: %s\n", itm->after);
		free(mod);

		return itm;
	}

	if (group(exp) != NULL) {

		if (!number(exp)) {
			struct Number *num = number(exp);
			if (!num) {
				printf("Number allocation failure in group\n");
				exit(1);
			}
			struct Item *itm = (struct Item *)malloc(sizeof(struct Item));
			if (!itm) {
				printf("Failed to allocate memory for item\n");
				exit(1);
			}
			itm->content = num->content;

			if (sizeof(num->after) > sizeof(itm->after)) {
				printf("Item overflow for group with number\n");
				exit(1);
			}
			printf("item after: %s\n", itm->after);
			free(num);

			return itm;
		}

		if (!modifier(exp)) {
			struct Modifier *mod = modifier(exp);
			if (!mod) {
				printf("Modifier allocation failure in group \n");
				exit(1);
			}
			struct Item *itm = (struct Item *)malloc(sizeof(struct Item));
			if (!itm) {
				printf("Failed to allocate memory for item\n");
				exit(1);
			}
			itm->content = mod->content;

			if (sizeof(mod->after) > sizeof(itm->after)) {
				printf("Item overflow for group with number\n");
				exit(1);
			}
			
			free(mod);
			return itm;
		}
	}

	return NULL;
}

struct Term *term(char* exp[8]) {
	if (!exp) {
		printf("Missing expression fn term\n");
		exit(1);
	}

	if (item(exp) != NULL) {
		struct Item *itm = item(exp);
		printf("break itm: %s", itm->after);

		if (!itm) {
			printf("Item allocation failure\n");
			exit(1);
		}
		struct Term *trm = (struct Term *)malloc(sizeof(struct Term));

		if (!trm) {
			printf("Failed to allocate memory for term\n");
			exit(1);
		}
		trm->item = itm;


		if (group(&itm->after) != NULL) {
			struct Group *grp = group(&itm->after);

			if (!grp) {
				printf("Group allocation failure\n");
				exit(1);
			}
			trm->group = grp;

			if (sizeof(grp->after) > sizeof(trm->after)) {
				printf("Term overflow with group");
				exit(1);
			}
			memcpy(trm->after, grp->after, sizeof(grp->after));
			printf("term after: %s\n", trm->after);
			free(grp);
			free(itm);

			return trm;
		}

		trm->group = NULL;
		if (sizeof(itm->after) > sizeof(trm->after)) {
			printf("Term overflow with item");
			exit(1);
		}
		memcpy(trm->after, itm->after, sizeof(itm->after));
		printf("term after: %s\n", trm->after);
		free(itm);

		return trm;
	}

	return NULL;
}

struct Start *start(char** exp) {
	if (!exp) {
		printf("Missing expression fn start\n");
		exit(1);
	}

	if (expression(exp) != NULL) {
		struct Expression *expr = expression(exp);
		if (!expr) {
			printf("Expression allocation failure\n");
			exit(1);
		}
		
		struct Start *result = (struct Start *)malloc(sizeof(struct Start));
		if (!result) {
			printf("Failed to allocate memory for result\n");
			exit(1);
		}

		result->content = expr;
		return result;
	}

	return NULL;
}

void parse(char **exp) {
	if (!exp) {
		printf("No expression\n");
		exit(1);
	}
	struct Start *strt = start(exp);
	printf("parsed\n");
}

int main() {	
	char *simple_case = "1+2";
	char *ordered_case = "4+6/2";
	char *bracket_case1 = "(3-1)";
	char *bracket_case2 = "2+(3-1)";
	
	parse(&bracket_case2);

	return 0;
}
