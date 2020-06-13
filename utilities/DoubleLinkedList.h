#pragma once

#include <random>

template <class T>
class DoubleLinkedList {

public:
	struct Node {
		Node(T nodeData) : data(nodeData) {}

		T data{};
		Node* next{nullptr};
		Node* prev{nullptr};
	};

private:
	Node* currentNode{nullptr};
	Node* head{nullptr};
	Node* tail{nullptr};
	size_t size{};

public:

	DoubleLinkedList() {}
	DoubleLinkedList(int size) : size(size) {}
	~DoubleLinkedList() {}

	void insert(int position, T value) {

		if (position == 0)
			insertFront(value);

		else if (position == size)
			insertBack(value);

		else if (position < 0 or position > size)
			throw std::invalid_argument("Out of range.");

		else
			insertAtPosition(position, value);
	}

	void insertFront(T value) {

		Node* newNode = new Node(value);

		if (isEmpty()) {
			head = newNode;
			tail = newNode;
		}

		else {
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}

		++size;

	}

	void insertBack(T value)  {

		Node* newNode = new Node(value);

		if (isEmpty()) {
			head = newNode;
			tail = newNode;
		}
		else if (size == 1) {
			head->next = newNode;
			newNode->prev = head;
			tail = newNode;
		}

		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}

		++size;

	}

	void insertAtPosition(int position, T value) {
		findNodeAtPosition(position);
		Node* newNode = new Node(value);

		newNode->next = currentNode;
		newNode->prev = currentNode->prev;
		newNode->prev->next = newNode;
		currentNode->prev = newNode;

		++size;

	}

	void remove(T value) {

		findNodeByValue(value);

		if (currentNode == nullptr)
			std::cout << std::endl << "Node doesn't exist" << std::endl;

		else if (size == 1) {
			tail = nullptr;
			head = nullptr;
			--size;
		}

		else if (currentNode == head) {
			currentNode->next->prev = nullptr;
			head = currentNode->next;
			--size;
		}

		else if (currentNode == tail) {
			currentNode->prev->next = nullptr;
			tail = currentNode->prev;
			--size;
		}


		else {
			currentNode->prev->next = currentNode->next;
			currentNode->next->prev = currentNode->prev;
			--size;

		}

	}


	bool search(T value) {
		findNodeByValue(value);

		if (currentNode != nullptr) {
			return true;
		}

		return false;

	}

	int getSize() const {
		return size;
	}

	void print() {

		currentNode = head;

		while (currentNode != nullptr) {
			std::cout<< currentNode->data.first << ": " <<  currentNode->data.second << ", " ;
			currentNode = currentNode->next;
		}

		std::cout <<  std::endl;

	}

	bool hasNodes() {
		 if (currentNode != nullptr)
			 return true;

		 return false;
	}

	T getNodeData() {
		if (currentNode != nullptr) {
			T nodeData = currentNode->data;
			currentNode = currentNode->next;
			return nodeData;
		}
		return T();
	}

	void setCurrentNodeToHead() {
		currentNode = head;
	}

	bool isEmpty() {
		return size==0;
	}

	void findNodeAtPosition(int position) {

		if(isEmpty())
			currentNode = nullptr;

		else {
			currentNode = head;

			for(int i{0}; i <= position and currentNode != nullptr; i++) {
				if (i != position)
					currentNode = currentNode->next;
			}
		}
	}

	void findNodeByValue(T value) {

		currentNode = head;

		while(currentNode != nullptr and currentNode->data != value) {
				currentNode = currentNode->next;
			}


	}
	void clearStructure() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

};
