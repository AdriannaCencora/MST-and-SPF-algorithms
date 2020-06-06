#pragma once

#include <iostream>
#include <vector>
#include <string>

class AdjencyMatrix {
	public:
		AdjencyMatrix() = default;
		AdjencyMatrix(bool isMST) : isMST(isMST) {}
		~AdjencyMatrix() = default;

		void readFromFile(std::string fileName);
		void fillWithRandomData(int numberOfVertices, int density);
		void printMatrix();

	private:
		int numberOfVertices;
		int numberOfEdges;
		int sourceVertex;

		//MST - graph is not directed.
		//Shortest path - graph is directed. Also file contains source vertex.
		bool isMST;

		int** adjencyMatrix;

		void initialize();
		void addEdge(int from, int to, int value);
		void clear();
};