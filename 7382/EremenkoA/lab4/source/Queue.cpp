#include "Queue.h"

template<typename V>
Queue<V>::Queue()//создаем начальную очередь и переменные
{
	index = 0;
	size = 10;
	lenght = 0;
	queue = new V[size];
}

template<typename V>
void Queue<V>::push(V element)
{
	if (lenght == size)//логика такая же как у реаллока  в си
	{
		// realloc
		V* time_queue = new V[size];						
		std::memcpy(time_queue, queue, (size) * sizeof(V)); 
		delete[]  queue;											
		queue = new V[size + 10];
		std::memcpy(queue, time_queue, (size) * sizeof(V));
		delete[] time_queue;
		size += 10;
	}
		queue[lenght++] = element;
}

template<typename V>
V Queue<V>::pop()
{
	return queue[index++];
}

template<typename V>
void Queue<V>::fulling_queue(V*text,int len)
{
	int j = 1;
	int block = 1;
	for (int i = 0;i < len;i++)
	{
		if (i==block)//каждый уровень дерева находится в промежукте [2^(n-1);2^n]
		{
			push('\n');
			block += pow(2, j++);
		}
			if(!isalpha(text[i]))//пушим только существующий символ
			continue;
		std::cout << "pushing =" << text[i] << "\n";
		push(text[i]);
	}
}

template<typename V>
void Queue<V>::getqueue()
{
	while (index!=lenght)//индекс изменяется в функции pop
		std::cout << pop();
}

template<typename V>
Queue<V>::~Queue()
{
	delete[]queue;//удаляем очередь
}
