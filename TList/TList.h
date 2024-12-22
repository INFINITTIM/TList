#pragma once

#include <iostream>

using namespace std;

template <class T>
struct TNode
{
	T val;
	TNode<T>* pNext;
};

template <class T>
class TList
{
	TNode<T>* pFirst;
public:
	TList() : pFirst(nullptr) {}
	TList(const TList<T>& list);
	~TList();

	TNode<T>* ToPos(int pos);

	void PushFront(T val);
	void PushLast(T val);
	void PushInPosition(int pos, T val);

	void PopFirst();
	void PopLast();
	void PopInPosition(int pos);

	T& operator[](int pos);

	bool IsEmpty();
	int Size();

	friend ostream& operator<<(ostream& out, const TList<T>& list) 
	{
		TNode<T>* list_tmp = list.pFirst;
		while (list_tmp != nullptr)
		{
			out << list_tmp->val << " ";
			list_tmp = list_tmp->pNext;
		}
		return out;
	}
};

template<class T>
TList<T>::TList(const TList<T>& list) {
	TNode<T>* list_tmp = list.pFirst; // создаем временный указатель stmp, который указывает на первый элемент листа list
	if (list_tmp != nullptr) { // если лист не пустой (stmp != nullptr), мы создаем новый узел для первого элемента
		pFirst = new TNode<T>; // выделяем память для нового узла
		pFirst->val = list_tmp->val; // копируем значение из stmp->val
		pFirst->pNext = nullptr; // и устанавливаем pNext этого узла в nullptr, так как это будет последний элемент на данный момент

		list_tmp = list_tmp->pNext; // переходим к следующему узлу в исходном листе

		TNode<T>* p = pFirst; // создаем указатель prev, который будет использоваться для связывания новых узлов
		while (list_tmp != nullptr) { //  цикл while продолжается до тех пор, пока есть элементы для копирования
			TNode<T>* new_node = new TNode<T>; // Внутри цикла создаем новый узел newnode
			new_node->val = list_tmp->val; // копируем значение из текущего узла stmp
			new_node->pNext = nullptr; // и устанавливаем его pNext в nullptr

			p->pNext = new_node; // связываем предыдущий узел с новым узлом

			list_tmp = list_tmp->pNext; // переходим к следующему узлу в исходном листе
			p = p->pNext; // и обновляем указатель prev на новый узел
		}
	}
	else {
		pFirst = nullptr; // если исходный лист пуст, устанавливаем pFirst в nullptr
	}
}

template<class T>
TList<T>::~TList() {
	while (pFirst != nullptr) {
		TNode<T>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
	}
}

template<class T>
T& TList<T>::operator[](int pos)
{
	TNode<T>* p = ToPos(pos);
	return p->val;
}

template<class T>
TNode<T>* TList<T>::ToPos(int pos)
{
	if (pos < 0)
		throw - 1;
	TNode<T>* list_tmp = pFirst;
	for (int i = 0; i < pos; i++)
	{
		list_tmp = list_tmp->pNext;
		if (i != pos - 1 && list_tmp == nullptr)
			throw - 1;
	}
	return list_tmp;
}

template<class T>
void TList<T>::PushFront(T val)
{
	TNode<T>* node = new TNode<T>;
	node->val = val;
	node->pNext = pFirst;
	pFirst = node;
}

template<class T>
void TList<T>::PushLast(T val)
{
	if (pFirst == nullptr)
		PushFront(val);
	else
	{
		TNode<T>* list_tmp = pFirst;
		while (list_tmp->pNext != nullptr)
		{
			list_tmp = list_tmp->pNext;
		}
		TNode<T>* node = new TNode<T>;
		node->val = val;
		node->pNext = nullptr;
		list_tmp->pNext = node;
	}
}

template<class T>
void TList<T>::PushInPosition(int pos, T val)
{
	if (pFirst == nullptr && pos != 0)
		throw - 1;
	if (pos == 0)
		PushFront(val);
	else
	{
		TNode<T>* p_before = ToPos(pos - 1);
		TNode<T>* p = ToPos(pos);
		TNode<T>* node = new TNode<T>;
		node->val = val;
		node->pNext = p;
		p_before->pNext = node;
	}
}

template<class T>
void TList<T>::PopFirst()
{
	if (pFirst == nullptr)
		throw - 1;
	TNode<T>* list_tmp = pFirst;
	pFirst = pFirst->pNext;
	delete list_tmp;
}

template<class T>
void TList<T>::PopLast()
{
	if (pFirst == nullptr)
		throw - 1;
	if (pFirst->pNext == nullptr)
		PopFirst();
	else
	{
		TNode<T>* list_tmp = pFirst;
		while (list_tmp->pNext->pNext != nullptr)
		{
			list_tmp = list_tmp->pNext;
		}
		TNode<T>* pred_list_tmp = list_tmp;
		list_tmp = list_tmp->pNext;
		delete list_tmp;
		pred_list_tmp->pNext = nullptr;
	}
}

template<class T>
void TList<T>::PopInPosition(int pos)
{
	if (pFirst == nullptr)
		throw - 1;
	if (pos == 0)
		PopFirst();
	else
	{
		TNode<T>* p_before = ToPos(pos - 1);
		TNode<T>* p = ToPos(pos);
		if (p->pNext == nullptr)
			PopLast();
		else
		{
			TNode<T>* p_after = ToPos(pos + 1); // TNode<T>* p_after = p->pNext;
			p_before->pNext = p_after;
			delete p;
		}
	}
}

template<class T>
bool TList<T>::IsEmpty()
{
	if (pFirst == nullptr)
		return true;
	return false;
}

template<class T>
int TList<T>::Size()
{
	int size = 0;
	while (pFirst != nullptr) {
		pFirst = pFirst->pNext;
		size++;
	}
	return size;
}