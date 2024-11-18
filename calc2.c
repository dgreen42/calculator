#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum eTerm {
	ITEM_OPPERATION,
	ITEM,
};

enum eExpression {
	TERM_EXPRESSION,
	TERM,
};

enum eItem {
	NUMBER,
	GROUP,
};


struct Character {
	char content;
	char* after[128];
};

struct Modifier {
	char content;
	char* after[128];
};

struct Expression {
	char first;
	char opp;
	char second;
	char* after[128];
};

struct Group {
	char open;
	char close;
	char* expression[64];
};

struct Item {
	char content;
	char *content_group[128];
	char *after[128];
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

struct Character *character(char** exp) {
	
	if (is_number(&exp[0]) == 1) {
		struct Character *ch = (struct Character *)malloc(sizeof(struct Character));
		if (!ch) {
			printf("Failed to allocate memory for character");
			exit(-1);
		}
		ch->content = *exp[0];
		char* after = *exp + 1;
		memcpy(ch->after, &after, sizeof(after));
		return ch;
	}

	return NULL;
}

struct Modifier *modifier(char** exp) {
	
	if (is_symbol(&exp[0]) == 1) {
		struct Modifier *mod = (struct Modifier *)malloc(sizeof(struct Modifier));
		if (!mod) {
			printf("Failed to allocate memory for modifier");
			exit(-1);
		}
		mod->content = *exp[0];
		char* after = *exp + 1;
		memcpy(mod->after, &after, sizeof(after));
		return mod;
	}

	return NULL;
}

struct Expression *expression(char** exp) {
	printf("%c", *exp[0]);
	if (is_number(&exp[0]) == 1) {
		if (is_symbol(&exp[1]) == 1) {
			if (is_number(&exp[2]) == 1) {
				struct Expression *expr = (struct Expression *)malloc(sizeof(struct Expression));
				expr->first = *exp[0];
				expr->opp = *exp[1];
				expr->second = *exp[2];
				char* after = *exp + 3;
				memcpy(expr->after, &after, sizeof(after));

				return expr;
			}
			//check if it is a paren
		}
		//check if it is a paren
	}
	return NULL;
}

/*
struct Group *group(char** exp) {
	struct Group *grp = (struct Group *)malloc(sizeof(struct Group));
	if (!grp) {
		printf("Failed to allocate memory for group");
		exit(-1);
	}

	if (*exp[0] == *"(") {
		if (!expression(exp)) {
			if (*exp[0]+4 == *")") { //come back to this
				return grp;
			}
		}
	}
}

struct Item *item() {
	struct Item *itm = (struct Item *)malloc(sizeof(struct Item));
	if (!itm) {
		printf("Failed to allocate memory for item");
		exit(-1);
	}
	if () {
		//parse as group
	} else {
		//parse as character
	}
}
*/

void parser(char** exp) {
	
}

int main() {
	char *simple_case = "1+2";
	char *ordered_case = "4+6/2";
	char *bracket_case1 = "(3-1)";
	char *bracket_case2 = "2+(3-1)";

	struct Expression *expr = expression(&simple_case);


}

