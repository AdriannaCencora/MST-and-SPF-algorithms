#include <climits>
#include <cstdlib>
#include <fstream>
#include <iomanip>

#include "AdjacencyMatrix.h"
#include "DisjointSet.h"
#include "Heap.h"
#include "Edge.h"

void AdjacencyMatrix::initialize() {

	adjacencyMatrix = new int*[numberOfVertices];

	for (int i{0}; i < numberOfVertices; i++) {
		adjacencyMatrix[i] = new int[numberOfVertices];
	}

	for (int i{0}; i < numberOfVertices; i++) {
		for (int j{0}; j < numberOfVertices; j++) {
			adjacencyMatrix[i][j] = 0;
		}
	}

	srand (time(NULL));
}

void AdjacencyMatrix::addEdge(int from, int to, int value) {
	adjacencyMatrix[from][to] = value;
	numberOfEdges++;

	if (isMST)
		adjacencyMatrix[to][from] = value;
}


void AdjacencyMatrix::printMatrix() {

	std::cout << std::endl << "ADJACENCY MATRIX" << std::endl;
	for (int i{0}; i < numberOfVertices; i++) {
		for (int j{0}; j < numberOfVertices; j++) {
			std::cout << std::setw(5) << adjacencyMatrix[i][j];
		}
		std::cout << std::endl;
	}
}

void AdjacencyMatrix::readFromFile(std::string fileName) {

	clear();

	int targetNumberOfEdges;

	std::fstream inputFile;
	inputFile.open(fileName, std::ios::in);

	if (!inputFile.is_open()) {
		std::cerr << "File couldn't be opened!" << std::endl;
		return;
	}

	inputFile >> targetNumberOfEdges;
	inputFile >> numberOfVertices;

	initialize();

	if (!isMST)
		inputFile >> sourceVertex;


	while (inputFile) {
		int startVertex, endVertex, weight;

		inputFile >> startVertex >> endVertex >> weight;
		addEdge(startVertex, endVertex, weight);
	}

	inputFile.close();
}

int AdjacencyMatrix::getCurrentDensity() {
	int maxEdgeAmount = numberOfVertices * (numberOfVertices - 1);

	if(isMST)
		maxEdgeAmount /= 2;

	return (int)(((float)numberOfEdges / (float)maxEdgeAmount) * 100);
}

bool AdjacencyMatrix::findEdge(int from, int to) {
	if (adjacencyMatrix[from][to] != 0)
		return true;
	return false;
}


void AdjacencyMatrix::fillWithRandomData(int givenNumberOfVertices, int density) {

	int weightRange = 100;
	int weightBase = 1;

	clear();

	numberOfVertices = givenNumberOfVertices;

	initialize();

	//dummy mst TODO: improve method
	for(int i{1}; i < numberOfVertices; i++) {
		int weight = rand() % weightRange + weightBase;
		addEdge(0, i, weight);
	}

	while (getCurrentDensity() < density) {
		int from = rand() % numberOfVertices;
		int to = rand() % numberOfVertices;
		int weight = rand() % weightRange + weightBase;

		if (from == to) {
			continue;
		}

		if (findEdge(from, to)) {
			continue;
		}

		addEdge(from, to, weight);

	}

}

void AdjacencyMatrix::clear() {

	if (adjacencyMatrix != nullptr) {
		for (int i {0}; i < numberOfVertices; i++) {
			delete[] adjacencyMatrix[i];
		}

		delete[] adjacencyMatrix;
	}

	numberOfEdges = 0;
	numberOfVertices = 0;
	adjacencyMatrix = nullptr;
}


void AdjacencyMatrix::executePrimsAlgorithm() {
	Heap<Edge> priorityQueue;
	int mst [numberOfVertices];		//the cheapest cost of a connection to vertex v
	int parents [numberOfVertices];	//edges providing that cheapest connection
	bool visited [numberOfVertices];

	for(int i{0}; i < numberOfVertices; i++) {
		mst[i] = INT_MAX;
		parents[i] = -1;
		visited[i] = false;
	}

	priorityQueue.insert(Edge(0,0));
	mst[0] = 0;

	while (!priorityQueue.isEmpty()) {
		int u = priorityQueue.popElement().second;

		visited[u] = true;

		for (int v = 0; v < numberOfVertices; v++) {
			if(adjacencyMatrix[u][v] and !visited[v] and adjacencyMatrix[u][v] < mst[v]) {
				mst[v] = adjacencyMatrix[u][v];
				priorityQueue.insert(Edge(mst[v], v));
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

void AdjacencyMatrix::executeKruskalsAlgorithm() {
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
				if(adjacencyMatrix[u][v] and (disjointSet.findSet(u) != disjointSet.findSet(v)) and (adjacencyMatrix[u][v] < min)) {
					min = adjacencyMatrix[u][v];
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

void AdjacencyMatrix::printParents(int *parents, int vertex) {
	if (parents[vertex] == -1)
		return;
	printParents(parents, parents[vertex]);
	std::cout << " -> " <<  vertex;

}


void AdjacencyMatrix::executeDijkstraAlgorithm() {
	Heap<Edge> priorityQueue;
	int distances [numberOfVertices];
	int parents [numberOfVertices];
	bool visited [numberOfVertices];

	for(int i{0}; i < numberOfVertices; i++) {
		distances[i] = INT_MAX;
		parents[i] = -1;
		visited[i] = false;
	}

	priorityQueue.insert(Edge(0, sourceVertex));
	distances[sourceVertex] = 0;

	while(!priorityQueue.isEmpty()) {
		int u = priorityQueue.popElement().second;

		visited[u] = true;

		for(int v{0}; v < numberOfVertices; v++) {
			if (adjacencyMatrix[u][v] and !visited[v] and distances[v] > (distances[u] + adjacencyMatrix[u][v]) and distances[u] != INT_MAX) {
				distances[v] = distances[u] + adjacencyMatrix[u][v];
				parents[v] = u;
				priorityQueue.insert(Edge(distances[v], v));
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

void AdjacencyMatrix::executeFordBellmanAlgorithm() {
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
				if (adjacencyMatrix[u][v] and distances[u] != INT_MAX and distances[v] > (distances[u] + adjacencyMatrix[u][v])) {
					distances[v] = distances[u] + adjacencyMatrix[u][v];
					parents[v] = u;
				}
			}

		}
	}


	for (int v{0}; v < numberOfVertices; v++) {
		for (int u{0}; u < numberOfVertices; u++) {
			if (adjacencyMatrix[u][v] and distances[v] > (distances[u] + adjacencyMatrix[u][v])) {
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
