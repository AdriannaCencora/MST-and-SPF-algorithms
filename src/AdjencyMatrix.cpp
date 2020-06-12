#include <climits>
#include <random>
#include <fstream>
#include <iomanip>
#include <queue>

#include "AdjencyMatrix.h"
#include "DisjointSet.h"
#include "Heap.h"
#include "Node.h"

void AdjencyMatrix::initialize() {

	adjencyMatrix = new int*[numberOfVertices];

	for (int i{0}; i < numberOfVertices; i++) {
		adjencyMatrix[i] = new int[numberOfVertices];
	}

	for (int i{0}; i < numberOfVertices; i++) {
		for (int j{0}; j < numberOfVertices; j++) {
			adjencyMatrix[i][j] = 0;
		}
	}

}

void AdjencyMatrix::addEdge(int from, int to, int value) {
	adjencyMatrix[from][to] = value;

	if (isMST)
		adjencyMatrix[to][from] = value;
}


void AdjencyMatrix::printMatrix() {

	for (int i{0}; i < numberOfVertices; i++) {
		for (int j{0}; j < numberOfVertices; j++) {
			std::cout << std::setw(5) << adjencyMatrix[i][j];
		}
		std::cout << std::endl;
	}
}

void AdjencyMatrix::readFromFile(std::string fileName) {

	clear();

	std::fstream inputFile;
	inputFile.open(fileName, std::ios::in);

	if (!inputFile.is_open()) {
		std::cerr << "File couldn't be opened!" << std::endl;
		return;
	}

	inputFile >> numberOfEdges;
	inputFile >> numberOfVertices;

	initialize();

	if (!isMST)
		inputFile >> sourceVertex;

	int edgesCounter = 0;

	while (edgesCounter < numberOfEdges and inputFile) {
		int startVertex, endVertex, weight;

		inputFile >> startVertex >> endVertex >> weight;
		addEdge(startVertex, endVertex, weight);
		edgesCounter++;
	}

	inputFile.close();
}


void AdjencyMatrix::fillWithRandomData(int numberOfVertices, int density) {

	//TODO: IMPLEMENT ME
	const int upperRange = 150;
	std::random_device seed;
	std::mt19937 randomGenerator(seed());
	std::uniform_int_distribution<> transform(1, upperRange);

}

void AdjencyMatrix::clear() {

	if (adjencyMatrix != nullptr) {
		for (int i {0}; i < numberOfVertices; i++) {
			delete[] adjencyMatrix[i];
		}

		delete[] adjencyMatrix;
	}

	numberOfEdges = 0;
	numberOfVertices = 0;
	adjencyMatrix = nullptr;
}


void AdjencyMatrix::executePrimsAlgorithm() {
	Heap<Node> priorityQueue;
	int mst [numberOfVertices];		//the cheapest cost of a connection to vertex v
	int parents [numberOfVertices];	//edges providing that cheapest connection
	bool visited [numberOfVertices];

	for(int i{0}; i < numberOfVertices; i++) {
		mst[i] = INT_MAX;
		parents[i] = -1;
		visited[i] = false;
	}

	priorityQueue.insert(Node(0,0));
	mst[0] = 0;

	while (!priorityQueue.isEmpty()) {
		int u = priorityQueue.popElement().second;

		visited[u] = true;

		for (int v = 0; v < numberOfVertices; v++) {
			if(adjencyMatrix[u][v] and !visited[v] and adjencyMatrix[u][v] < mst[v]) {
				mst[v] = adjencyMatrix[u][v];
				priorityQueue.insert(Node(mst[v], v));
				parents[v] = u;
			}
		}
	}

	int finalCost{0};

	std::cout << "PRIM'S ALGORITHM - ADJACENCY MATRIX" << std::endl;
	for(int i{1}; i < numberOfVertices; i++) {
		std::cout << "Edge: " << parents[i] << " - " << i << ", weight: " << mst[i] << std::endl;
		finalCost += mst[i];
	}

	std::cout << "Cost: " << finalCost << std::endl;

}

void AdjencyMatrix::executeKruskalsAlgorithm() {
	DisjointSet disjointSet(numberOfVertices);

	int finalCost{0};
	int edgesCounter{0};

	std::cout << "KRUSKAL'S ALGORITHM - ADJACENCY MATRIX" << std::endl;

	while (edgesCounter < numberOfVertices - 1) {
		int min = INT_MAX;
		int firstSet{-1};
		int secondSet{-1};

		for(int u{0}; u < numberOfVertices; u++) {
			for(int v{0}; v < numberOfVertices; v++) {
				if(adjencyMatrix[u][v] and (disjointSet.findSet(u) != disjointSet.findSet(v)) and (adjencyMatrix[u][v] < min)) {
					min = adjencyMatrix[u][v];
					firstSet = u;
					secondSet = v;
				}
			}
		}

		disjointSet.makeUnion(firstSet, secondSet);

		std::cout << "Edge: " << firstSet << " - " << secondSet << ", weight: " << min << std::endl;

		finalCost += min;
		edgesCounter++;
	}

	std::cout << "Cost: " << finalCost << std::endl;
}

void AdjencyMatrix::printParents(int *parents, int vertex) {
	if (parents[vertex] == -1)
		return;
	printParents(parents, parents[vertex]);
	std::cout << " -> " <<  vertex;

}


void AdjencyMatrix::executeDijkstraAlgorithm() {
	Heap<Node> priorityQueue;
	int distances [numberOfVertices];
	int parents [numberOfVertices];
	bool visited [numberOfVertices];

	for(int i{0}; i < numberOfVertices; i++) {
		distances[i] = INT_MAX;
		parents[i] = -1;
		visited[i] = false;
	}

	priorityQueue.insert(Node(0, sourceVertex));
	distances[sourceVertex] = 0;

	while(!priorityQueue.isEmpty()) {
		int u = priorityQueue.popElement().second;

		visited[u] = true;

		for(int v{0}; v < numberOfVertices; v++) {
			if (adjencyMatrix[u][v] and !visited[v] and distances[v] > (distances[u] + adjencyMatrix[u][v]) and distances[u] != INT_MAX) {
				distances[v] = distances[u] + adjencyMatrix[u][v];
				parents[v] = u;
				priorityQueue.insert(Node(distances[v], v));
			}
		}

	}

	std::cout << "DIJKSTRA'S ALGORITHM - ADJACENCY MATRIX" << std::endl;

	for (int i{0}; i < numberOfVertices; i++) {
		std::cout << "Path: " << sourceVertex;

		if (distances[i] != INT_MAX) {
			printParents(parents, i);
			std::cout << " weight: " << distances[i] << std::endl;
		}
	}

}

void AdjencyMatrix::executeFordBellmanAlgorithm() {
	int distances [numberOfVertices];
	int parents [numberOfVertices];

	for(int i{0}; i < numberOfVertices; i++) {
		distances[i] = INT_MAX;
		parents[i] = -1;
	}

	distances[sourceVertex] = 0;

	for (int i{0}; i < numberOfVertices - 1; i++) {
		for (int v{0}; v < numberOfVertices; v++) {
			for (int u{0}; u < numberOfVertices; u++) {
				if (adjencyMatrix[u][v] and distances[u] != INT_MAX and distances[v] > (distances[u] + adjencyMatrix[u][v])) {
					distances[v] = distances[u] + adjencyMatrix[u][v];
					parents[v] = u;
				}
			}

		}
	}


	for (int v{0}; v < numberOfVertices; v++) {
		for (int u{0}; u < numberOfVertices; u++) {
			if (adjencyMatrix[u][v] and distances[v] > (distances[u] + adjencyMatrix[u][v])) {
				std::cout << "Graph contains a negative-weight cycle." << std::endl;
				return;
			}
		}
	}

	std::cout << "BELLMAN-FORD'S ALGORITHM - ADJACENCY MATRIX" << std::endl;

	for (int i{0}; i < numberOfVertices; i++) {
		std::cout << "Path: " << sourceVertex;

		if (distances[i] != INT_MAX) {
			printParents(parents, i);
			std::cout << " weight: " << distances[i] << std::endl;
		}
	}


}
