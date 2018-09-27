#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "API.h"

void print_list(Node *node) {								//Printting function list

	if (node->flag_type[1] == 1)							//Case of division by zero
		if (node->sign == '/' && node->two == 0)
			abort_("\nError - deviision by zero!");				//Call error func with message

	if(node->sign == '+' && node->flag_type[0] == 1)		//Case of odd or subtraction left 0
		if(node->one == 0) {
			if(node->flag_type[1] == 1)
				printf(" %d", node->two);
			else
				print_list(node->right);
			return;
		}

	if((node->sign == '+' || node->sign == '-') && node->flag_type[1] == 1)		//Case of odd or subtraction right 0
		if(node->two == 0) {
			if(node->flag_type[0] == 1)
				printf(" %d", node->one);
			else
				print_list(node->left);
			return;
		}

	if(node->sign == '*' && node->flag_type[0] == 1)				//Case of multiplicate on left 1
		if(node->one == 1) {
			if(node->flag_type[1] == 1)
				printf(" %d", node->two);
			else
				print_list(node->right);
			return;
		}

	if(node->sign == '*' && node->flag_type[1] == 1)				//Case of multiplicate on right 1
		if(node->two == 1) {
			if(node->flag_type[0] == 1)
				printf(" %d", node->one);
			else
				print_list(node->left);
			return;
		}
	if(node->sign == '/' && node->flag_type[1] == 1)				//Case division by 1
		if(node->two == 1) {
			if(node->flag_type[0] == 1)
				printf(" %d", node->one);
			else
				print_list(node->left);
			return;
		}

	printf(" (%c", node->sign);							//Print sign
	if (node->flag_type[0] == 2)
		print_list(node->left);							//Print left exprission
	else
		printf(" %d", node->one);						//Print left arg
	if(node->flag_type[1] == 2)
		print_list(node->right);						//Print right expression
	else
		printf(" %d", node->two);						//Print right exprission
	printf(")");

}

void abort_(const char * s, ...)							//Consulting error with message
{
        va_list args;
        va_start(args, s);
        vfprintf(stderr, s, args);
        fprintf(stderr, "\n");
        va_end(args);
        abort();
}

void fill_list(Node * node, char *str) {						//Filling function list
	int args[5];
	find_args(str, args);
	fill_node(node, args, str);

}

void fill_node(Node * node, int *args, char *str){					//Filling finction node
	node->sign = str[args[0]];							//Set value sign
	node->left = (Node *)malloc(sizeof(Node));					//Allocate memory to left exprission
	node->right = (Node *)malloc(sizeof(Node));					//Allocate memory to right exprission
	if (isdigit(str[args[1]])) {							//If first arg os digit
		node->flag_type[0] = 1;							//Set type first arg 1
		node->one = 0;								//Set valuse first arg 0
		while (isdigit(str[args[1]]))						//Ramp up first arg while we meet digit
			node->one = node->one * 10 + str[args[1]++] - '0';
		if (isdigit(str[args[2]])) {						//If second arg is digit
			node->flag_type[1] = 1;						//Set type second arg 1
			node->two = 0;							//Set value second arg 0
			while (isdigit(str[args[2]]))					//Ramp up second arg while we meet digit
				node->two = node->two * 10 + str[args[2]++] - '0';
		}
		else {									//If second arg is expression
			node->flag_type[1] = 2;						//Set type second arg 2
			fill_expr(node->right, args[2], args[3], str);			//Fill next exprission
		}
	}
	else {
		node->flag_type[0] = 2;							//Set type first arg 2
		fill_expr(node->left, args[1], args[2], str);				//Fill next exprission

		if (isdigit(str[args[3]])) {						//If second arg is digit
			node->flag_type[1] = 1;						//Set type second arg 1
			node->two = 0;							//Set value second arg 0
			while (isdigit(str[args[3]]))					//Ramp up second arg while we meet digit
				node->two = node->two * 10 + str[args[3]++] - '0';
		}
		else {									//If second arg is exprission
			fill_expr(node->right, args[3], args[4], str);
			node->flag_type[1] = 2;						//Set tyoe second arg 2
		}
	}
}
void fill_expr(Node *node,int  arg1, int arg2, char *str) {				//Filling function exprission
	int odd = arg2 - arg1 + 1;							//Set odd
	char *new_str = (char *)malloc(sizeof(char) * odd);
	strncpy(new_str, str + arg1, odd);
	printf("Component expr %s\n", new_str);
	fill_list(node, new_str);							//Continue fill list
}

void find_args(char *str, int *args) {							//Finding function args
	for (int i = 0; i < strlen(str); i++)						//Find index sign
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
			args[0] = i;
			break;
		}

	int limit = 3;									//Number of args
	int add = args[0];								//Deletion ariable from the beginning of string 
	for (int i = 1; i < limit; i++) {
		args[i] = add + 1;							//Set next arg to next index
		while (str[args[i]] == ' ') {						//Skip spaces
			args[i]++;
		}
		add = args[i];								//Set deletion to current arg
		if (isdigit(str[args[i]]) && isdigit(str[args[i]+1])) {			//While we meet digit ramp up deletion
			while (isdigit(str[add]))
				add++;
		}
		if (str[args[i]] == '(') {						//If we meet openong bracket 
			i++;
			args[i] = find_sec_bracket(str + args[i-1] + 1) + args[i-1];	//Set next arg to index closing bracket
			limit++;							//Increment number args
			add += args[i] - args[i-1] ;					//Add deletion 
		}
	}
}

int find_sec_bracket(char *str) {							//Finding function second bracket
	int left_br = 1, right_br = 0;
	int i;
	for (i = 0; left_br != right_br; i++) {						//While left bracket doesn't right bracket continue 								//While the number of left and right brackets does'nt equal
		if (str[i] == '(')
			left_br++;
		if (str[i] == ')')
			right_br++;
	}
	return i;									//return deleting
}
