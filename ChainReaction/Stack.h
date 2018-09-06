#pragma once
#include <fstream>

template <class T>
class Stack
{
	Stack* head;
	Stack* next;
	T elem;
	size_t maxsize;
	size_t size;
public:
	Stack()
	{
		maxsize = 10;
		size = 0;
		head = NULL;
		next = NULL;
	}
	void push(T);
	void pop();
	void clear();
	Stack* getTop()
	{
		return head;
	}
	size_t getSize()
	{
		return size;
	}
	bool empty();
	void show();
	void sort();
	bool check();
	void save();
	void load();
};

template<class T>
void Stack<T>::push(T elem)
{
	Stack<T>* newEl = new Stack<T>();
	newEl->elem = elem;
	newEl->next = head;
	head = newEl;
	size++;
}

template<class T>
void Stack<T>::pop()
{
	Stack<T>* temp = new Stack<T>();
	temp = head->next;
	delete[] head;
	head = temp;
	size--;
}

template<class T>
void Stack<T>::save()
{
	fstream f;
	f.open("table.txt");
	Stack<T>* temp = head;
	long file_size;
	f.seekg(0, ios::end);
	file_size = f.tellg();
	while (temp != NULL)
	{
		if (file_size != 0)
		{
			fstream("table.txt", ios::app);
			f << temp->elem;
		}
		else
		{
			fstream("table.txt", ios::out);
			f << temp->elem;
		}
		temp = temp->next;
	}
	f.close();
}

template<class T>
void Stack<T>::load()
{
	ifstream f;
	f.open("table.txt");
	long file_size;
	f.seekg(0, ios::end);
	file_size = f.tellg();
	if (file_size != 0)
	{
		f.seekg(0, ios::beg);
		while (!f.eof())
		{
			f >> elem;
			if(!elem)
				push(elem);
		}
	}
	else
		head = NULL;
	f.close();
}

template<class T>
bool Stack<T>::check()
{
	bool buf;
	if (size >= maxsize)
		buf = true;
	else
		buf = false;
	return buf;
}

template<class T>
void Stack<T>::clear()
{
	while (head != NULL)
	{
		pop();
	}
}

template<class T>
bool Stack<T>::empty()
{
	bool buf;
	if (size >= 1)
		buf = true;
	else
		buf = false;
	return buf;
}

template<class T>
void Stack<T>::show()
{
	Stack<T>* temp = new Stack<T>();
	temp = head;
	int i = 1;
	while (temp != NULL)
	{
		cout << i << ". ";
		cout << temp->elem << endl;
		temp = temp->next;
		i++;
	}
	system("pause");
	system("cls");
}

template<class Type>
void sortArr(Type*& arr, size_t n)
{
	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < n - 1; j++)
			if (arr[j] > arr[j + 1])
			{
				Type buf = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = buf;
			}
}

template<class T>
void Stack<T>::sort()
{
	T* arr = new T[size];
	Stack<T>* temp = new Stack<T>();
	int i = 0;
	temp = head;
	while (temp != NULL)
	{
		arr[i] = temp->elem;
		temp = temp->next;
		i++;
	}
	sortArr<T>(arr, i);
	i = 0;
	temp = head;
	while (temp != NULL)
	{
		temp->elem = arr[i];
		temp = temp->next;
		i++;
	}
}