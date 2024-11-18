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

struct Group {
	char open;
	char close;
	char* expression[64];
};

struct Character {
	char content;
	char* after[256];
};

struct Modifier {
	char content;
	char* after[256];
};

struct Item {
	char content;
	char *content_group[256];
	char *after[256];
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
	struct Character *ch = (struct Character *)malloc(sizeof(struct Character));
	if (!ch) {
		printf("Failed to allocate memory for character");
		exit(-1);
	}
	
	if (is_number(&exp[0]) == 1) {
		ch->content = *exp[0];
		char* after = *exp + 1;
		memcpy(ch->after, &after, sizeof(after));
	}

	return ch;
}

struct Modifier *modifier(char** exp) {
	struct Modifier *mod = (struct Modifier *)malloc(sizeof(struct Modifier));
	if (!mod) {
		printf("Failed to allocate memory modifier");
		exit(-1);
	}
	
	if (is_symbol(&exp[0]) == 1) {
		mod->content = *exp[0];
		char* after = *exp + 1;
		memcpy(mod->after, &after, sizeof(after));
	}

	return mod;
}

struct Item *item() {
	struct Item *itm = (struct Item *)malloc(sizeof(struct Item));
	if (!itm) {
		printf("Failed to allocate memory for item");
		exit(-1);
	}

	if (is_goup == 1) {
		//parse as group
	} else {
		//parse as character
	}
}


int main() {
	char *simple_case = "1+2";
	char *ordered_case = "4+6/2";
	char *bracket_case = "2+(3-1)";

	struct Character *this = character(&simple_case);
	printf("%c\n", this->content);
	printf("%s\n", *this->after);
	
	/*
	struct Character *test = (struct Character *)malloc(sizeof(struct Character));
	char *t = "this";
	char *after = t+1;
	memcpy(test->after, &after, sizeof(after));
	printf("%s\n", *test->after);
	*/
}
