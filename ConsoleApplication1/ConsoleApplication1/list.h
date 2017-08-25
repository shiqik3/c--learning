#include<iostream>
#include<math.h>
#include<stdlib.h>
#define Type int
using namespace std; 
enum { INIT_SIZE = 8 };
class seqlist
{
private:
	Type *base;
	size_t capacity;
	size_t size;
	
public:
	seqlist()
	{
		capacity = 8;
		base = new Type[capacity];
		size = 0;
	}
	seqlist(size_t sz)
	{
		capacity = sz > INIT_SIZE ? sz : INIT_SIZE;
		base = new Type[capacity];
		size = 0;
	};
	~seqlist() {};
	bool isFull()
	{
		return size == capacity;
	}
	bool isEmpty()
	{
		return size == 0;
	}
	void insert(Type in)
	{
		if (isFull()) {
			cout << "顺序表已经满了" << endl;
		}
		base[size] = in;
		size++;
		return ;
	}
	void pop(size_t num)
	{
		if (NULL == base[num])
		{
			//cout << "当前位置为空" << endl;
		};
		for (size_t i = num; i+1 < size; i++)
		{
			base[i] = base[i + 1];
			size--;
		}
	}
	void display()
	{
		size_t i = 0;
		while (i < size)
		{
			cout << base[i] << "  " << endl;
			i++;
		}
	}
};
//int main() 
//{
//	size_t num= (size_t)rand() * 10;
//	seqlist *list=new seqlist();
//	for (int i = 0; i < 10; i++)
//	{
//		num = (size_t)rand() * 10;
//		list->insert(num);
//	}
//	list->display();
//	delete list;
//	return 0;
//}