#include "List.h"

template class List<std::string, std::string>;

template<typename T1, typename T2>
List<T1, T2>::List(Node<T1, T2>* pHead) {
	this->pHead = pHead;
	this->pTail = pHead;
}

//precondition: commandTitle exists
template<typename T1, typename T2>
void List<T1, T2>::removeNode(T1 commandTitle) {
	Node<T1, T2>* pPrev = nullptr;
	Node<T1, T2>* pCur = this->pHead;

	while (pCur->getCommand() != commandTitle) {
		pPrev = pCur;
		pCur = pCur->getNextPtr();
	}

	if (pPrev == nullptr && pCur->getNextPtr() == nullptr) {
		this->setPTail(nullptr);
		this->setPHead(nullptr);
	}
	else if (pPrev == nullptr && pCur->getNextPtr() != nullptr) {
		this->setPHead(pCur->getNextPtr());
	}
	else if (pCur->getNextPtr() == nullptr && pPrev != nullptr) {
		pPrev->setNextPtr(nullptr);
		this->setPTail(pPrev);
	}
	else {
		pPrev->setNextPtr(pCur->getNextPtr());
	}
	delete pCur;
}

template<typename T1, typename T2>
void List<T1, T2>::setPHead(Node<T1, T2>* newHead) {
	this->pHead = newHead;
}

template<typename T1, typename T2>
void List<T1, T2>::setPTail(Node<T1, T2>* newHead) {
	this->pTail = newHead;
}

template<typename T1, typename T2>
Node<T1, T2>* List<T1, T2>::getPHead() {
	return this->pHead;
}

template<typename T1, typename T2>
List<T1, T2>::~List() {
	deleteList();
}

template<typename T1, typename T2>
void List<T1, T2>::deleteList() {
	Node<T1, T2>* pCur;
	while (pHead != nullptr) {
		pCur = this->pHead->getNextPtr();
		delete pHead;
		pHead = pCur;
	}
}

template<typename T1, typename T2>
void List<T1, T2>::loadData() {
	std::ifstream infile;
	char lineString[150];
	char storeString1[20];
	char storeString2[150];
	int charIndex = 0;
	int newIndex = 0;

	int numRuns = 0;

	infile.open("../commands.csv");

	if (!infile.is_open()) {
        	std::cout << "The file didn't open properly.";
    	}

	infile.getline(lineString, 150);

	//run until commands.csv runs out of data
	while (!infile.eof() && charIndex < 100) {
		//make a new node for insert
		Node<T1, T2>* newData = new Node<T1, T2>;
		numRuns++;
		
		charIndex = 0;
		
		while (lineString[charIndex] != ',' && charIndex < 150) {
			storeString1[charIndex] = lineString[charIndex];
			charIndex++;
		}
		storeString1[charIndex] = '\0';

		charIndex += 3;

		newIndex = 0;
		while (lineString[charIndex] != '\"' && charIndex < 150) {
			storeString2[newIndex] = lineString[charIndex];
			charIndex++;
			newIndex++;
		}
		storeString2[newIndex] = '\0';

		newData->setCommand(storeString1);
		newData->setDescription(storeString2);

		this->insertAtFront(newData);

		infile.getline(lineString, 150);
	}
	infile.close();
}

template<typename T1, typename T2>
void List<T1, T2>::insertAtBack(Node<T1, T2>* newNode) {
	if (this->pHead == nullptr || this->pHead->getCommand() == "*") {
		this->pHead = newNode;
		this->pTail = newNode;
	}
	else {
		this->pTail->setNextPtr(newNode);
		this->pTail = this->pTail->getNextPtr();
	}
}

template<typename T1, typename T2>
void List<T1, T2>::insertAtFront(Node<T1, T2>* newNode) {
	if (this->pHead == nullptr || this->pHead->getCommand() == "*") {
		this->pHead = newNode;
		this->pTail = newNode;
	}
	else {
		Node<T1, T2>* pTemp = this->pHead;
		this->pHead = newNode;
		this->pHead->setNextPtr(pTemp);
	}
}

template<typename T1, typename T2>
void List<T1, T2>::printList() {
	Node<T1, T2>* pCur = this->pHead;

	while (pCur != nullptr) {
		std::cout << "Command: " << pCur->getCommand() << std::endl;
		std::cout << "Description: " << pCur->getDescription() << std::endl;
		pCur = pCur->getNextPtr();
	}
}