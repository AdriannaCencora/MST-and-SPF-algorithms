#pragma once

#include <memory>
#include <string>
#include <random>

#include "DynamicArray.h"

template <class T>
class Heap {
private:
	int size{};
	std::unique_ptr<DynamicArray<T>> heapArray{};

public:
	Heap() : heapArray(std::make_unique<DynamicArray<T>>()) {}
	Heap(int size) : size(size), heapArray(std::make_unique<DynamicArray<T>>()) {}
	~Heap() {}

	void insert(T value) {
		heapArray->insert(heapArray->getSize(), value);

		fixUp(heapArray->getSize() - 1);

		++size;
	}

	void fixUp(int indexFound) {

		int currentNode = indexFound;
		int parent = (currentNode - 1) / 2;

		while (currentNode != 0 and (*heapArray)[currentNode] < (*heapArray)[parent]) {
			heapArray->swapElements(currentNode, parent);
			currentNode = parent;
			parent = (currentNode - 1) / 2;
		}


	}

	void fixDown(int indexFound) {

		 int parentIndex = indexFound;
		 int leftChildIndex = 2 * indexFound + 1;
		 int rightChildIndex = 2 * indexFound + 2;
		 int swapChildIndex;

		 while (leftChildIndex < heapArray->getSize()  and rightChildIndex < heapArray->getSize()) {


			 swapChildIndex = ((*heapArray)[leftChildIndex] > (*heapArray)[rightChildIndex]) ? leftChildIndex : rightChildIndex;

			 if ((*heapArray)[swapChildIndex] < (*heapArray)[parentIndex]) {

				 heapArray->swapElements(parentIndex, swapChildIndex);
				 parentIndex = swapChildIndex;
			 }
			 leftChildIndex = 2 * parentIndex + 1;
			 rightChildIndex = 2 * parentIndex + 2;
		}


	}

	void remove(T value) {

		int indexFound;

		for (int i{0}; i < heapArray->getSize(); i++) {

			if((*heapArray)[i] == value ) {
				indexFound = i;
				break;
			}
		}

		bool isBigger;
		(*heapArray)[heapArray->getSize() -1] > (*heapArray)[indexFound] ? isBigger = true : isBigger = false;

		heapArray->swapElements(indexFound, heapArray->getSize() -1);
		heapArray->remove(heapArray->getSize() -1);

	//	std::cout << "Before fix" << std::endl;
	//	print();
	//
		if (isBigger)
			fixUp(indexFound);
		else
			fixDown(indexFound);

		--size;

	}

	T popElement() {
		T element = (*heapArray)[0];

		heapArray->swapElements(0, heapArray->getSize() -1);
		heapArray->remove(heapArray->getSize() -1);
		fixDown(0);
		--size;

		return element;
	}

	bool search(T value) {

		if (value > (*heapArray)[0])
			return false;

		return heapArray->search(value);
	}

	void print() {

		printTree(std::string(""), std::string(""), 0);

		heapArray->print();
	}

	int getSize() const {

		return size;
	}

	bool isEmpty() const {
		return size == 0;
	}

	void printTree(const std::string& sMiddle, const std::string &sBefore, int currNode) {
		std::string s;

		if (currNode < heapArray->getSize()) {
			s = sMiddle;
			if (sBefore == (std::string(1, (char)47) + std::string(1, (char)126)))
				s[s.length() - 2] = ' ';
			printTree(s + (char)124 + " ", (std::string(1, (char)47)) + std::string(1, (char)126), 2 * currNode + 2);

			s = s.substr(0, sMiddle.length() - 2);

			std::cout << s << sBefore << (*heapArray)[currNode] << std::endl;

			s = sMiddle;

			if (sBefore == (std::string(1, (char)92)) + std::string(1, (char)126))
				s[s.length() - 2] = ' ';

			printTree(s + (char)124 + " ", (std::string(1, (char)92)) + std::string(1, (char)126), 2 * currNode + 1);
	}
	}

	void clearStructure() {
		heapArray->clearStructure();
	}

};
