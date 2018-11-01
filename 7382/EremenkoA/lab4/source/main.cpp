#include <iostream>
#include "Bintree.cpp"
#include "Queue.cpp"

int main()
{
	Bintree<char>tree;//инициализация дерева и очереди
	Queue<char> queue;
	std::cout << "Вид бинарного дерева задается вот так-сын обозначается в скобочках,а брат обозначается на одном уровнем с родителем.пример:(a(b)c)-b сын a,а с брат a\nENTER:";
	tree.settext();
	tree.createbintree();
	tree.gettext();
	if (!tree.Iscorrecttext()) //проверяем на корректность бинарное дерево
	{
		std::cout << "wrong\n";
		exit(0);
	}
	tree.pushbintree(0, 0, 1);
	std::cout << "binary tree:\n";
	tree.getbintree();
	std::cout << "_______________________________\nQUEUE:\n";
	queue.fulling_queue(tree.bintree, tree.len);
	queue.getqueue();
	std::cout << "\n";
	
	return 0;
}

