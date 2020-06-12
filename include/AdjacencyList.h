#pragma once

#include <iostream>

class AdjacencyList {
	public:
		void readFromFile(std::string fileName);
		void fillWithRandomData(int numberOfVertices, int density);
		void printMatrix();

		void executePrimsAlgorithm();
		void executeKruskalsAlgorithm();

		void executeDijkstraAlgorithm();
		void executeFordBellmanAlgorithm();

	private:
		int numberOfVertices;
		int numberOfEdges;
		int sourceVertex;
};
