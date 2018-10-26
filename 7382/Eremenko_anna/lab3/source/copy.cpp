#include<string>
using namespace std;
class Expression {
public:
	string current_input;
};

class Element {
public:
	Element* next = nullptr;
	explicit Element(int number) {
		this->number = number;
	}
	Element(int a, int b) {
		brackets = new int[2];
		this->brackets[0] = a;
		this->brackets[1] = b;
	}
	int getNumber();
	int getOpening();
	int getClosing();
private:
	union {
		int number;
		int* brackets;
	};
};

class ListBrackets {
private:
	Element* head = nullptr;
public:
	void add(int a, int b);
	Element* findElement(int a);
	Element* lastElement();
};

class Stack {
private:
	Element* head = nullptr;
public:
	void pop();
	void push(int num);
	int top();
};

class List {
private:
	Element* head = nullptr;
public:
	void pop();
	void push(int num);
	Element* back();
	int front();
};
