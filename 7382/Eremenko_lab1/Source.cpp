#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
int square(FILE *fp, FILE *f, char a, int i);// ������� ��� ������������� ���������� ������
int round(FILE *fp, FILE *f, char a, int i);// -//- ������� ������
int figure(FILE *fp, FILE *f, char a, int i);// -//- �������� ������
int znak(FILE *fp, FILE *f, char* a); //������� ��� ���������� � ������ ������ �����������
int brackets(FILE *fp, FILE *f); // �������, ������� ��������� �������� �� ��������� ������������������ ��������
int main() {

	FILE *fp; FILE *f;  char arr[10000];
	setlocale(LC_ALL, "rus");
	//��������� ������ � ���������� � ���������� � ���� input ��� ����������� �������������
	fp = fopen("input.txt", "w"); //������� ���� �����, ��� ������ ���� ������ � �������
	printf("������������! ��� ������������ �������������� ���������� ��� �������� <������>.\n");
	printf("������� ������ ��� �������:\n");
	scanf("%s", arr);
	fputs(arr, fp);
	fclose(fp);

	fp = fopen("input.txt", "r");//������� ���� �����
	if (fp == NULL) {
		fprintf(stderr, "Error: file 'input.txt' is not opened!\n");
		exit(EXIT_FAILURE);
	}
	f = fopen("output.txt", "w");//������� ���� ������
	if (f == NULL) {
		fprintf(stderr, "Error: You can`t create 'output.txt' file!\n");
		exit(EXIT_FAILURE);
	}
	printf("���� ������...\n");
	getchar();
	brackets(fp, f);
	fclose(fp);//�������� ����� �����
	fclose(f);//� ������
	return 0;
}

int brackets(FILE *fp, FILE *f) {
	char a; int b = 0; int i = 0;
	znak(fp, f, &a);
	if (a == EOF) {//�������� �� ������� ������ � �����
		printf("The file is empty");
		fprintf(f, "The file is empty");
		return 0;
	}
	//�������� ������� �������. ���� �� �� ������������� ���������� ������ ������, ��������� ��������� ������,����� - ��������� � ������� ��� ���������� �������� �� ������
	if (a == '+' || a == '[')
		b = square(fp, f, a, i);
	if (a == '-' || a == '(')
		b = round(fp, f, a, i);
	if (a == '0' || a == '{')
		b = figure(fp, f, a, i);
	if (b == 1 && fscanf(fp, "%c", &a) == 1) {//������, ���� ������ - ������, �� � ����� ������������ ������ �������
		printf("\n������������ �������������� �������. ��� �� ������.");
		fprintf(f, "\n������������ �������������� �������. ��� �� ������.");
		getchar();
		return 0;
	}
	if (b != 1) {
		printf("\n��� �� ������.");
		fprintf(f, "\n��� �� ������.");
	}
	if (b == 1) {
		printf("\n��� ������.");
		fprintf(f, "\n��� ������.");
	}
	getchar();
	return 0;
}

int square(FILE *fp, FILE *f, char a, int i) {
	for (int k = 0; k < i; k++) { //������ �������, ���������������� ������� ��������. i - �������, ������� ������������� ��� ����� ����� � ������� �������� ������ � ����������� ��� ������
		printf(" ");
		fprintf(f, " ");
	}
	i++;
	if (a == '+') {//������ �� ���������� ��������� ������� ��� ������ ������, ���������� �������� ��� ��� �� ���������
		i--;
		printf(" ��� ���������� ������.\n");
		fprintf(f, " ��� ���������� ������.\n");
		getchar();
		return 1;
	}
	if (a == '[') {//������ �� ���������� ��������� ������� ��� ������ ������
		printf(" ��� ���������� ������. ��������� �������� ������...\n");
		fprintf(f, " ��� ���������� ������. ��������� �������� ������...\n");
		znak(fp, f, &a);
		if (round(fp, f, a, i) == 1) {//�������� �� ��, ��������� �� ������ ������� ������. ���� ���, ������� ���������� ������
			znak(fp, f, &a);
			if (figure(fp, f, a, i) == 1) {//�������� �� ��, ��������� �� ������ �������� ������. ���� ���, �� ����� ����������� ���� ����������� ������ ���������� ������
				znak(fp, f, &a);
				if (a == ']') {//�������� �� ����������� ������ ������ ������
					i--;
					for (int k = 0; k < i; k++) {
						printf(" ");
						fprintf(f, " ");
					}
					fprintf(f, " ��� ���������� ������.\n");
					printf(" ��� ���������� ������.\n");
					getchar();
					return 1;

				}
			}
		}
	}
	getchar();
	return 0;
}

int round(FILE *fp, FILE *f, char a, int i) {//������� ������ �� ����������, ������� ����������� ����� ������ ���, ��� ���� �����-���� ��������
	for (int k = 0; k < i; k++) {
		printf(" ");
		fprintf(f, " ");
	}
	i++;
	if (a == '-') {
		i--;
		printf("��� ������� ������.\n");
		fprintf(f, "��� ������� ������.\n");
		getchar();
		return 1;
	}
	if (a == '(') {
		printf(" ��� ������� ������. ��������� �������� ������...\n");
		fprintf(f, " ��� ������� ������. ��������� �������� ������...\n");
		znak(fp, f, &a);
		if (figure(fp, f, a, i) == 1) {	//�������� �� ��, ��������� �� ������ �������� ������. ���� ���, ������� ���������� ������
			znak(fp, f, &a);
			if (square(fp, f, a, i) == 1) {//�������� �� ��, ��������� �� ������ ���������� ������. ���� ���, �� ����� ����������� ���� ����������� ������ ���������� ������
				znak(fp, f, &a);
				if (a == ')') {
					i--;
					for (int k = 0; k < i; k++) {
						printf(" ");
						fprintf(f, " ");
					}
					printf(" ��� ������� ������.\n");
					fprintf(f, " ��� ������ ������.\n");
					return 1;
				}
			}
		}
	}
	getchar();
	return 0;
}

int figure(FILE *fp, FILE *f, char a, int i) {//������� ������ �� ����������, ������� ����������� ����� ��������� ������ ���, ��� ���� �����-���� ��������
	for (int k = 0; k < i; k++) {
		printf(" ");
		fprintf(f, " ");
	}
	i++;
	if (a == '0') {
		i--;
		printf(" ��� �������� ������.\n");
		fprintf(f, " ��� �������� ������.\n");
		getchar();
		return 1;
	}
	if (a == '{') {
		printf(" ��� �������� ������. ��������� �������� ������...\n");
		fprintf(f, " ��� �������� ������. ��������� �������� ������...\n");
		znak(fp, f, &a);
		if (square(fp, f, a, i) == 1) {//�������� �� ��, ��������� �� ������ ���������� ������. ���� ���, ������� ���������� ������
			znak(fp, f, &a);
			if (round(fp, f, a, i) == 1) {//�������� �� ��, ��������� �� ������ ������� ������. ���� ���, �� ����� ����������� ���� ����������� ������ ���������� ������
				znak(fp, f, &a);
				if (a == '}') {
					i--;
					for (int k = 0; k < i; k++) {
						printf(" ");
						fprintf(f, " ");
					}
					printf(" ��� �������� ������.\n");
					fprintf(f, " ��� �������� ������.\n");
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