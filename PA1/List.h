#pragma once
#include "Node.h"

template<typename T1, typename T2>
class List {
private:
	Node<T1, T2>* pHead;
	Node<T1, T2>* pTail;
	void deleteList();
public:
	List(Node<T1, T2>* pHead = nullptr);
	~List();
	void removeNode(T1 commandTitle);
	void loadData();
	void insertAtBack(Node<T1, T2>* newNode);
	void insertAtFront(Node<T1, T2>* newNode);
	void printList();
	Node<T1, T2>* getPHead();
	void setPHead(Node<T1, T2>* newHead);
	void setPTail(Node<T1, T2>* newHead);
};