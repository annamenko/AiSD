#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
int square(FILE *fp, FILE *f, char a, int i);// Функция для идентификации квадратных скобок
int round(FILE *fp, FILE *f, char a, int i);// -//- круглых скобок
int figure(FILE *fp, FILE *f, char a, int i);// -//- фигурных скобок
int znak(FILE *fp, FILE *f, char* a); //Функция для считывания и вывода данных посимвольно
int brackets(FILE *fp, FILE *f); // функция, которая проверяет является ли введенная последовательность скобками
int main() {

	FILE *fp; FILE *f;  char arr[10000];
	setlocale(LC_ALL, "rus");
	//Считываем данные с клавиатуры и записываем в файл input для дальнейшего использования
	fp = fopen("input.txt", "w"); //открыли файл ввода, для записи туда данные с консоли
	printf("Здравствуйте! Вас приветствует синтаксический анализатор для понятния <скобки>.\n");
	printf("Введите данные для анализа:\n");
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
	printf("Идет анализ...\n");
	getchar();
	brackets(fp, f);
	fclose(fp);//закрытие файла ввода
	fclose(f);//и вывода
	return 0;
}

int brackets(FILE *fp, FILE *f) {
	char a; int b = 0; int i = 0;
	znak(fp, f, &a);
	if (a == EOF) {//Проверка на наличие данных в файле
		printf("The file is empty");
		fprintf(f, "The file is empty");
		return 0;
	}
	//Проверка первого символа. Если он не соответствует возможному началу скобок, программа завершает работу,иначе - переходит в функцию для дальнейшей проверки на скобки
	if (a == '+' || a == '[')
		b = square(fp, f, a, i);
	if (a == '-' || a == '(')
		b = round(fp, f, a, i);
	if (a == '0' || a == '{')
		b = figure(fp, f, a, i);
	if (b == 1 && fscanf(fp, "%c", &a) == 1) {//Случай, если данные - скобки, но в конце присутствуют лишние символы
		printf("\nПрисутствуют дополнительные символы. Это не скобки.");
		fprintf(f, "\nПрисутствуют дополнительные символы. Это не скобки.");
		getchar();
		return 0;
	}
	if (b != 1) {
		printf("\nЭто не скобки.");
		fprintf(f, "\nЭто не скобки.");
	}
	if (b == 1) {
		printf("\nЭто скобки.");
		fprintf(f, "\nЭто скобки.");
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
		printf(" Это квадратные скобки.\n");
		fprintf(f, " Это квадратные скобки.\n");
		getchar();
		return 1;
	}
	if (a == '[') {//второй из допустимых вариантов символа для данных скобок
		printf(" Это квадратная скобка. Выполняем проверку дальше...\n");
		fprintf(f, " Это квадратная скобка. Выполняем проверку дальше...\n");
		znak(fp, f, &a);
		if (round(fp, f, a, i) == 1) {//проверка на то, находятся ли внутри круглые скобки. Если так, функция продолжает работу
			znak(fp, f, &a);
			if (figure(fp, f, a, i) == 1) {//проверка на то, находятся ли внутри фигурные скобки. Если так, то далее потребуется лишь закрывающий символ квадратных скобок
				znak(fp, f, &a);
				if (a == ']') {//проверка на завершающий символ данных скобок
					i--;
					for (int k = 0; k < i; k++) {
						printf(" ");
						fprintf(f, " ");
					}
					fprintf(f, " Это квадратная скобка.\n");
					printf(" Это квадратная скобка.\n");
					getchar();
					return 1;

				}
			}
		}
	}
	getchar();
	return 0;
}

int round(FILE *fp, FILE *f, char a, int i) {//функция похожа на предыдущую, поэтому комментарии будут только там, где есть какие-либо различия
	for (int k = 0; k < i; k++) {
		printf(" ");
		fprintf(f, " ");
	}
	i++;
	if (a == '-') {
		i--;
		printf("Это круглые скобки.\n");
		fprintf(f, "Это круглые скобки.\n");
		getchar();
		return 1;
	}
	if (a == '(') {
		printf(" Это круглая скобка. Выполняем проверку дальше...\n");
		fprintf(f, " Это круглая скобка. Выполняем проверку дальше...\n");
		znak(fp, f, &a);
		if (figure(fp, f, a, i) == 1) {	//проверка на то, находятся ли внутри фигурные скобки. Если так, функция продолжает работу
			znak(fp, f, &a);
			if (square(fp, f, a, i) == 1) {//проверка на то, находятся ли внутри квадратные скобки. Если так, то далее потребуется лишь закрывающий символ квадратных скобок
				znak(fp, f, &a);
				if (a == ')') {
					i--;
					for (int k = 0; k < i; k++) {
						printf(" ");
						fprintf(f, " ");
					}
					printf(" Это круглая скобка.\n");
					fprintf(f, " Это кругая скобка.\n");
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
		printf(" Это фигурные скобки.\n");
		fprintf(f, " Это фигурные скобки.\n");
		getchar();
		return 1;
	}
	if (a == '{') {
		printf(" Это фигурная скобка. Выполняем проверку дальше...\n");
		fprintf(f, " Это фигурная скобка. Выполняем проверку дальше...\n");
		znak(fp, f, &a);
		if (square(fp, f, a, i) == 1) {//проверка на то, находятся ли внутри квадратные скобки. Если так, функция продолжает работу
			znak(fp, f, &a);
			if (round(fp, f, a, i) == 1) {//проверка на то, находятся ли внутри круглые скобки. Если так, то далее потребуется лишь закрывающий символ квадратных скобок
				znak(fp, f, &a);
				if (a == '}') {
					i--;
					for (int k = 0; k < i; k++) {
						printf(" ");
						fprintf(f, " ");
					}
					printf(" Это фигурная скобка.\n");
					fprintf(f, " Это фигурная скобка.\n");
					return 1;
				}
			}
		}
	}
	getchar();
	return 0;
}

int znak(FILE *fp, FILE *f, char* a) {
	*a = fgetc(fp);
	printf("%c", *a);
	fputc(*a, f);
	return 0;
}