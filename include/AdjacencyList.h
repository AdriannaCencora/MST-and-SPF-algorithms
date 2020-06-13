#pragma once

#include <iostream>
#include <string>

#include "Edge.h"
#include "DoubleLinkedList.h"

class AdjacencyList {
	public:
		AdjacencyList() = default;
		AdjacencyList(bool isMST) : isMST(isMST) {}
		~AdjacencyList() = default;

		void readFromFile(std::string fileName);
		void fillWithRandomData(int numberOfVertices, int density);
		void printList();

		void executePrimsAlgorithm();
		void executeKruskalsAlgorithm();

		void executeDijkstraAlgorithm();
		void executeFordBellmanAlgorithm();

	private:
		int numberOfVertices;
		int numberOfEdges;
		int sourceVertex;
		//MST - graph is not directed.
		//Shortest path - graph is directed. Also file contains source vertex.
		bool isMST;

		DoubleLinkedList<Edge>* adjacencyList;

		void initialize();
		void addEdge(int from, int to, int value);
		void clear();
//		void printParents(int *parents, int vertex);
};
