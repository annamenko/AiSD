#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

typedef struct Node {
	int type;
	struct Node *next;
	char symbol;
	struct Node *expr;
	int digit;
} Node;

void abort_(const char * s, ...);
void fill_list(int, Node *, char *);
int find_sec_bracket(char *);
void check_division(Node *);
void print_list(Node *node);
int reduct(int, Node *node);

int main() {

	char *str = (char *)malloc(100 * sizeof(char));
	fgets(str, 100, stdin);
	if (!strcmp(str, "\n"))					
		abort_("Expression is empty.");
	printf("Before: %s\n", str);

	printf("Args in expr with levels:\n");
	Node *top = (Node*)malloc(sizeof(Node));
	fill_list(0, top, str);

	printf("\nReduction process:\n");
	reduct(0, top);
	printf("\nAfter: ");
	if(top->next->next == NULL) {
		printf("0\n");
		return 0;
	}
	if(top->next->next->next != NULL)
		print_list(top);
	else {
		if(top->next->type == 1)
			printf("%c", top->next->symbol);
		if(top->next->type == 2)
			printf("%d", top->next->digit);
		if(top->next->type == 3)
			print_list(top->next->expr);
	}
	check_division(top);
	printf("\n");
	return 0;
}

void abort_(const char * s, ...) {

        va_list args;
        va_start(args, s);
        vfprintf(stderr, s, args);
        fprintf(stderr, "\n");
        va_end(args);
        abort();
}

void fill_list(int deep, Node *node, char *str) {

	int sign = 0;
	int end_expr = find_sec_bracket(str + 1);
	for(int i = 0; i < deep; i++)
		printf("%d|\t", i);
	printf("Start of expr.\n");
	for(int i = 1; i < end_expr; i++) {
		if(isalpha(str[i]) || str[i] == '*' || str[i] == '/' || str[i] == '-' || str[i] == '+') {
			if(!sign || isalpha(str[i])) {
				node->type = 1;
				node->symbol = str[i];
				for(int i = 0; i < deep; i++)
					printf("%d|\t", i);
				printf("%d| %c\n", deep, str[i]);
				node->next = (Node *)malloc(sizeof(Node));
				node = node->next;
				if(str[i] == '-' || str[i] == '+' || str[i] == '*' || str[i] == '/')
					sign++;
				continue;
			}
		}
		if(isdigit(str[i]) || (str[i] == '-' && sign)) {
			node->type = 2;
			node->digit = atoi(str + i);
			while(str[i] == '-')
				i++;
			while(isdigit(str[i + 1]))
				i++;
			for(int i = 0; i < deep; i++)
				printf("%d|\t", i);
			printf("%d| %d\n", deep, node->digit);
			node->next = (Node *)malloc(sizeof(Node));
			node = node->next;
		}
		if(str[i] == '(') {
			node->type = 3;
			node->expr = (Node *)malloc(sizeof(Node));
			fill_list(deep + 1, node->expr, str + i);
			node->next = (Node *)malloc(sizeof(Node));
			node = node->next;
			i += find_sec_bracket(str + i + 1);
		}
	}
	node->next = NULL;
	for(int i = 0; i < deep; i++)
		printf("%d|\t", i);
	printf("End of expr.\n");

}

int find_sec_bracket(char *str) {

	int left_br = 1, right_br = 0;
	int i;
	for (i = 0; left_br != right_br; i++) {
		if (str[i] == '(')
			left_br++;
		if (str[i] == ')')
			right_br++;
	}
	return i;
}

void check_division(Node *node) {

	while(node->next) {
		if (node->type == 1 && node->symbol == '/') {
				node = node->next;
				while(node->next->next) {
					node = node->next;
					if(node->type == 2 && node->digit == 0)
							printf("\nError - deviision by zero!");
				}
		}
		if(node->type == 3)
			check_division(node->expr);
		node = node->next;
	}
}

void print_list(Node *node) {

	printf("(");
	while(node->next ) {
		if(node->type == 1)
			printf("%c", node->symbol);
		if(node->type == 2)
			printf("%d", node->digit);
		if(node->type == 3)
			if(node->expr->next)
				print_list(node->expr);
		printf(" ");
		node = node->next;
	}
	printf(")");
}

int reduct(int deep, Node *node) {

	char sign;
	Node *start_node = node;
	if(node->type == 1)
		sign = node->symbol;
	else
		abort_("\nError - pass mark");

	for(int i = 0; i < deep; i++)
		printf("%d|\t", i);
	printf("Start of expr.\n");
	for(int i = 0; i < deep; i++)
		printf("%d|\t", i);
	printf("%d| %c\n", deep, sign);

	while(node->next) {
		for(int i = 0; i < deep && (node->next->type == 1 || node->next->type == 2); i++)
			printf("%d|\t", i);
		if(node->next->type != 3 && node->next->next)
			printf("%d| ", deep);
		if(node->next->type == 1)
			printf("%c ", node->next->symbol);
		if(node->next->type == 2)
			printf("%d ", node->next->digit);

		if(node->next->type == 3) {
			if(reduct(deep + 1, node->next->expr)) {
				if(sign == '+' || sign == '-') {
					node->next = node->next->next;
				}
				if(sign == '/') {
					node->next->type = 2;
					node->next->digit = 0;
				}
				if(sign == '*') {
					start_node->next->next = NULL;
					break;
				}
			}
			else
				if(node->next->expr->next->next->next == NULL) {
					if(node->next->expr->next->type == 1) {
						node->next->type = 1;
						node->next->symbol = node->next->expr->next->symbol;
						for(int i = 0; i < deep; i++)
							printf("%d|\t", i);
						printf("%d| level up with %c", deep, node->next->symbol);
					}
					if(node->next->expr->next->type == 2) {
						node->next->type = 2;
						node->next->digit = node->next->expr->next->digit;
						for(int i = 0; i < deep; i++)
							printf("%d|\t", i);
						printf("%d| level up with %d", deep, node->next->digit);
					}
					if(node->next->expr->next->type == 3)
						node->next->expr = node->next->expr->next->expr;
				}
		}

		if(sign == '+' || sign == '-') {
			if(node->next->type == 2) {
				if(node->next->digit == 0 && (node->symbol != '-' && (node->next->next->next || node->symbol != '*'))) {
					printf("delete\n");
					node->next = node->next->next;
					continue;
				}
			}
		}
		if((sign == '/' || sign == '*') && node->next->type == 2) {
				if(node->next->digit == 1 && (node->symbol != '/' && (node->next->next->next  || node->symbol != '*'))) {
					printf("delete\n");
					node->next = node->next->next;
					continue;
				}
		}
		if(sign == '*' || node->symbol == '/')
			if(node->next->type == 2 && node->next->digit == 0) {
			printf("delete expr\n");
			start_node->next->type = 2;
			start_node->next->digit = 0;
			start_node->next->next = NULL;
			break;
		}
		if(node->next->type != 0 && node->next->type != 3)
			printf("\n");
		node = node->next;
	}
	for(int i = 0; i < deep; i++)
		printf("%d|\t", i);
	printf("End of expr.\n");

	return (start_node->next->next == NULL);
}
