#pragma once
#include <string>
#include <iostream>
#include <math.h>
template <typename T>
class Bintree
{
public:
	Bintree();
	~Bintree();
	void settext();
	void gettext();
	bool Iscorrecttext();//проверка на корректность
	void pushbintree(int index,int index_place,int level);
	void createbintree();
	void getbintree();
	int len;
	T* bintree;//бинарное дерево на основе массива
private:
	int numberofbrackets;//кол-во скобок
	std::string text;//исходный текст из  cout
	int index_of_str;
	void add(int&index_place,T element);
};


