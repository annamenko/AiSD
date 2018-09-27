#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "API.h"

int main() {

	char *str = (char *)malloc(100 * sizeof(char));				//Allocate memory to string
	fgets(str, 100, stdin);
	if (!strcmp(str, "\n"))							//Cheking on the empty string
		abort_("Expression is empty.");

	printf("In first expr look like this %s", str);				//Output string

	List list;								//Creating list
	Node top;
	list.top = &top;							//Creating node
	fill_list(list.top, str);						//Fill list with our string
	printf("Abridged expression lools like this:");
	print_list(list.top);							//Print abridged expression
	printf("\n");
	return 0;
}
