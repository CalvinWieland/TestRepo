#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <limits>
#include <ios>

template<typename T1, typename T2>
class Node {
private:
	T1 command;
	T2 description;
	Node<T1, T2>* pNext;
public:
	Node(T1 D1 = "*", T2 D2 = "*", Node<T1, T2>* newNext = nullptr);
	//NOTE: Node gets destructed in ~List()
	//setters
	void setCommand(T1 command);
	void setDescription(T2 description);
	//getters
	T1 getCommand();
	T2 getDescription();
	Node<T1, T2>* getNextPtr();


	void setNextPtr(Node<T1, T2>* newPtr);
};

//constructor
template<typename T1, typename T2>
Node<T1, T2>::Node(T1 D1, T2 D2, Node<T1, T2>* newNext) {
	this->command = D1;
	this->description = D2;

	this->pNext = newNext;
}

//getters
template<typename T1, typename T2>
Node<T1, T2>* Node<T1, T2>::getNextPtr() {
	return this->pNext;
}

template<typename T1, typename T2>
T1 Node<T1, T2>::getCommand() {
	return this->command;
}

template<typename T1, typename T2>
T2 Node<T1, T2>::getDescription() {
	return this->description;
}

//setters
template<typename T1, typename T2>
void Node<T1, T2>::setCommand(T1 command) {
	this->command = command;
}

template<typename T1, typename T2>
void Node<T1, T2>::setDescription(T2 description) {
	this->description = description;
}

template<typename T1, typename T2>
void Node<T1, T2>::setNextPtr(Node<T1, T2>* newPtr) {
	this->pNext = newPtr;
}