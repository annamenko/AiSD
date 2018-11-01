#include "Bintree.h"

template <typename T>
Bintree<T>::Bintree()//начальная инициализация
{
	numberofbrackets = 0;
	len = 0;
	index_of_str = 0;
}

template <typename T>
Bintree<T>::~Bintree()
{
	delete[]bintree;//удаление дерева
}
template <typename T>
void Bintree<T>::settext()
{
	std::getline(std::cin,text);
}

template<typename T>
void Bintree<T>::gettext()
{
	std::cout << text <<  "\n";
}
template<typename T>
bool Bintree<T>::Iscorrecttext()
{
	int brackets = 0;
	if (text[0] != '(') {
		return false;
	}
	for (int i = 0;i < text.size();i++)
	{
		if (brackets < 0)//на случай ())(
		{
			std::cout << "NOT correct bintree\n";
			return false;
		}
		if (text[i] == '(')
		{
			numberofbrackets++;
			if (i)
			{
				if (text[i - 1] == ')')//на случай )(
				{
					if (brackets)
					{
						return false;
					}
				}
			}
			brackets++;
			continue;
		}
		if (text[i] == ')')
		{
			numberofbrackets++;
			brackets--;
			continue;
		}
	}
	if (brackets)
		return false;
	return true;
}

template<typename T>
void Bintree<T>::pushbintree(int index, int index_place, int level) //start 0 0 1 
{
	//int level_brackets = level - 1;
	int prev = index_place;
	bool first_bracket = true;
	while (index_of_str < text.length())
	{
			if (text[index_of_str] == '(')
			{
				if (!first_bracket)//1 скобку на считаем за сына 
				{												//prev ýòî ðàñïîëîæåíèå ïðåäûäóùåãî ýëåìåíòà
					pushbintree(index, prev * 2 + 1, level + 1);//каждый сын находится на индексе родителя умноженного на 2 + 1 
					continue;
				}
				else
				{
					index_of_str++;
					first_bracket = false;
					continue;
				}
			}
		if (text[index_of_str] == ')')//при встрече ')'выходим из рекурсии
		{			
			index_of_str++;
			return;
		}	
			prev = index_place;
			add(index_place, text[index_of_str]);
			index_of_str++;
			continue;
	}
}
template<typename T>
void Bintree<T>::add(int & index_place, T element)
{
	bintree[index_place] = element;
	index_place = index_place * 2 + 2;//каждый брат будет находиться на индексе родителя умноженного на 2 + 2
}
template<typename T>
void Bintree<T>::createbintree()
{
	bintree = new T[(int)pow(2,text.length() - numberofbrackets)+1]();//идет расчет на самый худший случай
}

template<typename T>
void Bintree<T>::getbintree()
{
	len = pow(2, text.length() - numberofbrackets) + 1;
	for (int i = 0;i < len;i++)
	std::cout <<"{"<< bintree[i]<<"}" << "["<<i<<"] ";
	std::cout << "\n";
}



