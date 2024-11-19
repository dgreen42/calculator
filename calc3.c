#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

struct Number {
	char content;
	char* after;
};

struct Number *number(char** exp) {
	if (is_number(&exp[0])) {
		struct Number *num = (struct Number *)malloc(sizeof(struct Number));
		num->content = *exp[0];
		char* after = *exp+1;
		memcpy(num->after, &after, sizeof(after));
		return num;
	}
	return NULL;
}

struct Modifier {
	char content;
	char* after;
};

struct Modifier *modifier(char** exp) {
	if (is_symbol(&exp[0])) {
		struct Modifier *mod = (struct Modifier *)malloc(sizeof(struct Modifier));
		mod->content = *exp[0];
		char* after = *exp+1;
		memcpy(mod->after, &after, sizeof(after));
		return mod;
	}
	return NULL;
}

struct Expression {
	char content;
	char* after;
};

struct Group {
	struct Expression content;
	char* after;
};

struct Group *group(char** exp) {
	if (*exp[0] == *"(") {
		char* after = *exp+1;
		if (!expression(after)) {
			struct Expression *expr = expression(&after);
			if (expr->after[0] == *")") {
				struct Group *grp = (struct Group *)malloc(sizeof(struct Group));
				grp->content = expr->content;
				grp->after = expr->after;
				return grp;
			}
		}
	}
	return NULL;
}

struct Item {
	char content;
	char* after;
};

struct Item *item(char** exp) {
	if (!number(exp)) {
		struct Number *num = number(exp);
		struct Item *itm = (struct Item *)malloc(sizeof(struct Item));
		itm->content = num->content;
		itm->after = num->after;
		free(num);
		return itm;
	}
	if (!group(exp)) {
		struct Number *num = number(exp);
		struct Item *itm = (struct Item *)malloc(sizeof(struct Item));
		itm->content = num->content;
		itm->after = num->after;
		free(num);
		return itm;
	}

	return NULL;
}
