#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
int square(FILE *fp, FILE *f, char a, int i);// Функция для идентификации квадратных скобок
int circular(FILE *fp, FILE *f, char a, int i);// -//- круглых скобок
int figure(FILE *fp, FILE *f, char a, int i);// -//- фигурных скобок
int sign(FILE *fp, FILE *f, char* a); //Функция для считывания и вывода данных посимвольно
int brackets(FILE *fp, FILE *f); // функция, которая проверяет является ли введенная последовательность скобками
int main() {

	FILE *fp; FILE *f;  char arr[10000];
	setlocale(LC_ALL, "rus");
	//Считываем данные с клавиатуры и записываем в файл input для дальнейшего использования
	fp = fopen("input.txt", "w"); //открыли файл ввода, для записи туда данные с консоли
	printf("Syntactical analyzer.\n");
	printf("Enter the data for analysis:\n");
	scanf("%s", arr);
	fputs(arr, fp);
	fclose(fp);

	fp = fopen("input.txt", "r");//открыли файл ввода
	if (fp == NULL) {
		fprintf(stderr, "Error: file 'input.txt' is not opened!\n");
		exit(EXIT_FAILURE);
	}
	f = fopen("output.txt", "w");//открыли файл вывода
	if (f == NULL) {
		fprintf(stderr, "Error: You can`t create 'output.txt' file!\n");
		exit(EXIT_FAILURE);
	}
	printf("Аnalysis...\n");
	getchar();
	brackets(fp, f);
	fclose(fp);//закрытие файла ввода
	fclose(f);//и вывода
	return 0;
}

int brackets(FILE *fp, FILE *f) {
	char a; int b = 0; int i = 0;
	sign(fp, f, &a);
	if (a == EOF) {//Проверка на наличие данных в файле
		printf("The file is empty");
		fprintf(f, "The file is empty");
		return 0;
	}
	//Проверка первого символа. Если он не соответствует возможному началу скобок, программа завершает работу,иначе - переходит в функцию для дальнейшей проверки на скобки
	if (a == '+' || a == '[')
		b = square(fp, f, a, i);
	if (a == '-' || a == '(')
		b = circular(fp, f, a, i);
	if (a == '0' || a == '{')
		b = figure(fp, f, a, i);
	if (b == 1 && fscanf(fp, "%c", &a) == 1) {//Случай, если данные - скобки, но в конце присутствуют лишние символы
		printf("\nThere are extra characters. This is not brackets!");
		fprintf(f, "\nThere are extra characters. This is not brackets!");
		getchar();
		return 0;
	}
	if (b != 1) {
		printf("\nThis is not brackets!");
		fprintf(f, "\nThis is not brackets!");
	}
	if (b == 1) {
		printf("\nThis is brackets!");
		fprintf(f, "\nThis is brackets!");
	}
	getchar();
	return 0;
}

int square(FILE *fp, FILE *f, char a, int i) {
	for (int k = 0; k < i; k++) { //печать отступа, соответствующего глубине рекурсии. i - счётчик, который увеличивается при новом входе в функцию проверки скобок и уменьшается при выходе
		printf(" ");
		fprintf(f, " ");
	}
	i++;
	if (a == '+') {//первый из допустимых вариантов символа для данных скобок, дальнейшая проверка для них не требуется
		i--;
		printf(" This is square brackets.\n");
		fprintf(f, " This is square brackets.\n");
		getchar();
		return 1;
	}
	if (a == '[') {//второй из допустимых вариантов символа для данных скобок
		printf(" This is square brackets.Сheck on...\n");
		fprintf(f, " This is square brackets.Сheck on...\n");
		sign(fp, f, &a);
		if (circular(fp, f, a, i) == 1) {//проверка на то, находятся ли внутри круглые скобки. Если так, функция продолжает работу
			sign(fp, f, &a);
			if (figure(fp, f, a, i) == 1) {//проверка на то, находятся ли внутри фигурные скобки. Если так, то далее потребуется лишь закрывающий символ квадратных скобок
				sign(fp, f, &a);
				if (a == ']') {//проверка на завершающий символ данных скобок
					i--;
					for (int k = 0; k < i; k++) {
						printf(" ");
						fprintf(f, " ");
					}
					fprintf(f, " This is square brackets.\n");
					printf(" This is square brackets.\n");
					getchar();
					return 1;

				}
			}
		}
	}
	getchar();
	return 0;
}

int circular(FILE *fp, FILE *f, char a, int i) {//функция похожа на предыдущую, поэтому комментарии будут только там, где есть какие-либо различия
	for (int k = 0; k < i; k++) {
		printf(" ");
		fprintf(f, " ");
	}
	i++;
	if (a == '-') {
		i--;
		printf("This is round brackets.\n");
		fprintf(f, "This is round brackets.\n");
		getchar();
		return 1;
	}
	if (a == '(') {
		printf(" This is round brackets. Сheck on...\n");
		fprintf(f, " This is round brackets. Сheck on...\n");
		sign(fp, f, &a);
		if (figure(fp, f, a, i) == 1) {	//проверка на то, находятся ли внутри фигурные скобки. Если так, функция продолжает работу
			sign(fp, f, &a);
			if (square(fp, f, a, i) == 1) {//проверка на то, находятся ли внутри квадратные скобки. Если так, то далее потребуется лишь закрывающий символ квадратных скобок
				sign(fp, f, &a);
				if (a == ')') {
					i--;
					for (int k = 0; k < i; k++) {
						printf(" ");
						fprintf(f, " ");
					}
					printf(" This is round brackets.\n");
					fprintf(f, " This is round brackets.\n");
					return 1;
				}
			}
		}
	}
	getchar();
	return 0;
}

int figure(FILE *fp, FILE *f, char a, int i) {//функция похожа на предыдущую, поэтому комментарии будут вставлены только там, где есть какие-либо различия
	for (int k = 0; k < i; k++) {
		printf(" ");
		fprintf(f, " ");
	}
	i++;
	if (a == '0') {
		i--;
		printf(" This is figure brackets.\n");
		fprintf(f, " This is figure brackets.\n");
		getchar();
		return 1;
	}
	if (a == '{') {
		printf(" This is figure brackets. Сheck on...\n");
		fprintf(f, " This is figure brackets. Сheck on...\n");
		sign(fp, f, &a);
		if (square(fp, f, a, i) == 1) {//проверка на то, находятся ли внутри квадратные скобки. Если так, функция продолжает работу
			sign(fp, f, &a);
			if (circular(fp, f, a, i) == 1) {//проверка на то, находятся ли внутри круглые скобки. Если так, то далее потребуется лишь закрывающий символ квадратных скобок
				sign(fp, f, &a);
				if (a == '}') {
					i--;
					for (int k = 0; k < i; k++) {
						printf(" ");
						fprintf(f, " ");
					}
					printf(" This is figure brackets.\n");
					fprintf(f, " This is figure brackets.\n");
					return 1;
				}
			}
		}
	}
	getchar();
	return 0;
}

int sign(FILE *fp, FILE *f, char* a) {
	*a = fgetc(fp);
	printf("%c", *a);
	fputc(*a, f);
	return 0;
}
