#include <iostream>
#include <cstring>
#include <sstream>
#include <cstdio>
#include <fstream>
#include <string>
#include "copy.cpp"
int main() {
    string input;
    cout << "Enter the expression:" << endl;
    getline(cin, input);
    if (input == "") {
        cout << "input cant be empty!!!";
        exit(0);
    }
    int pad=0,flag=0;
    for(int i=0; i<input.size(); i++)
    {
        if(pad<0) {
            cout<<"wrong input\n";
            exit(1);
        }
        if(input[i]=='(') {
            pad++;
            flag=1;
        }
        if(input[i]==')') {
            pad--;
            flag=1;
        }
    }
    if(pad!=0||flag==0) {
        cout<<"wrong input\n";
        exit(1);
    }
    cout <<"input:"<< input << endl;
    stringstream stream;
    for (int i = 0; i<input.length() ; i++) { //delete all ' '
        if (input[i] == ' ') 
        	input.erase(i, 1);
    }
    auto* expression = new Expression;//it's initialization part
    auto* stack = new Stack;
    auto* list = new List;
    auto* list_brackets = new ListBrackets;
    for (int i = 0; i < input.size(); i++)
    {
        expression->current_input += input[i];
    }
    for (int i = 0; i <= input.length(); i++)
    {
        cout << "Symbol #" << i << ". ";
        if ((expression->current_input[i]) == '(') {
            stack->push(i);				//it's part where u create stack and push
            list->push(i);
            cout << "Found \"(\" and pushed number " << i << " to stack and list" << endl;
        }
        else if ((expression->current_input[i]) == ')') {
            list_brackets->add(stack->top(), i);
            cout << "Found \")\"," << "\"(\" #" << stack->top() << " was popped from stack and pair (" << stack->top()
                 << " " << i << ") was added to brackets` list" << endl;
            stream << stack->top() << " " << i << "; ";
            stack->pop();
        }
        else {
            cout << "Found " << (expression->current_input[i]) << endl;
        }
    }
    cout << "End of input" << endl;
    input = stream.str();
    input = input.erase(input.size() - 2);
    cout << "Brackets` numbers in closing sequence: " << input << endl;
    stream.str("");
    Element* result;
    while (list->back() != nullptr) {
        result = list_brackets->findElement(list->front());
        cout << "\"(\" #" << list->front() << " was popped from list" << endl;
        list->pop();
        stream<< result->getOpening() << " " << result->getClosing() << "; ";
    }
    input = stream.str();
    input = input.erase(input.size() - 2);
    cout << "Brackets` numbers in opening sequence: " << input << endl;
    delete expression;//delete all memory
    delete stack;
    delete list;
    delete list_brackets;
    return 0;
}

void Stack::pop() {
	if(head!=nullptr){
    auto* curr = head;
    head = head->next;
    delete curr;
	}
	else
	{
		cout<<"not correct work of stack\n";
		exit(1);
	}
}

void Stack::push(int num) {

    if (head == nullptr) {
        head = new Element(num);
    }
    else {
        auto* curr = new Element(num);//push in stack.this head is pointer of last element but first in stack
        curr->next = head;
        head = curr;
    }
}

int Stack::top() {
	if(head!=nullptr)
    return head->getNumber();
	else
	{
		cout<<"not correct work of stack\n";
		exit(1);
	}
}

void List::push(int num) {
    if (head == nullptr) {
        head = new Element(num);
    }
    else {
        this->back()->next = new Element(num);
    }
}

Element* List::back() {
    if (head == nullptr) {
        return nullptr;
    }
    Element* curr = head;//find last element for list
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    return curr;
}

int List::front() {
    return head->getNumber();
}

void List::pop() {
    auto* curr = head;
    head = head->next;
    delete curr;
}

int Element::getNumber() {
    return this->number;
}

int Element::getOpening() {
    return this->brackets[0];
}

int Element::getClosing() {
    return this->brackets[1];
}

Element* ListBrackets::lastElement() {// go to last element
    Element* curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    return curr;

}

void ListBrackets::add(int a, int b) {
    if (head == nullptr) {
        head = new Element(a, b);//create head
    }
    else {
        this->lastElement()->next = new Element(a, b);//add element in tail
    }
}

Element* ListBrackets::findElement(int a) {
    Element* curr = head;
    while (curr->getOpening() != a && curr != nullptr) {//find element where symbol==a or not find(curr==nullptr)
        curr = curr->next;
    }
    return curr;
}