#pragma once

#include <iostream>
#include <string>

class AdjacencyMatrix {
	public:
		AdjacencyMatrix() = default;
		AdjacencyMatrix(bool isMST) : isMST(isMST) {}
		~AdjacencyMatrix() = default;

		void readFromFile(std::string fileName);
		void fillWithRandomData(int numberOfVertices, int density);
		void printMatrix();

		void executePrimsAlgorithm();
		void executeKruskalsAlgorithm();

		void executeDijkstraAlgorithm();
		void executeFordBellmanAlgorithm();

		int getCurrentDensity();
		bool findEdge(int from, int to);
	private:
		int numberOfVertices;
		int numberOfEdges;
		int sourceVertex = 0;

		//MST - graph is not directed.
		//Shortest path - graph is directed. Also file contains source vertex.
		bool isMST;

		int** adjacencyMatrix;

		void initialize();
		void addEdge(int from, int to, int value);
		void clear();
		void printParents(int *parents, int vertex);
};
