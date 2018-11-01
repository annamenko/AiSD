#include <algorithm>
#include <iostream>
#include <cstring>
template<typename V>
class Queue
{
public:
	Queue();
	~Queue();
	void push(V element);
	V pop();
	void fulling_queue(V*text,int len);//заполнение очереди
	void getqueue();//вывод очереди
private:
	int index;
	V*queue;
	int size,
		lenght;
};


