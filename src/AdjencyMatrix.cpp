#include <climits>
#include <random>
#include <fstream>
#include <iomanip>
#include <queue>
#include "AdjencyMatrix.h"
#include "DisjointSet.h"

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
	std::priority_queue< std::pair<int, int>, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > priorityQueue;
	int mst [numberOfVertices];		//the cheapest cost of a connection to vertex v
	int parents [numberOfVertices];	//edges providing that cheapest connection
	bool visited [numberOfVertices];

	for(int i{0}; i < numberOfVertices; i++) {
		mst[i] = INT_MAX;
		parents[i] = -1;
		visited[i] = false;
	}

	priorityQueue.push(std::make_pair(0,0));
	mst[0] = 0;

	while (!priorityQueue.empty()) {
		int u = priorityQueue.top().second;
		priorityQueue.pop();

		visited[u] = true;

		for (int v = 0; v < numberOfVertices; v++) {
			if(adjencyMatrix[u][v] and !visited[v] and adjencyMatrix[u][v] < mst[v]) {
				mst[v] = adjencyMatrix[u][v];
				priorityQueue.push(std::make_pair(mst[v], v));
				parents[v] = u;
			}
		}
	}

	int finalCost{0};

	std::cout << "PRIM'S ALGORITH - ADJACENCY MATRIX" << std::endl;
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

		std::cout << "KRUSKAL'S ALGORITH - ADJACENCY MATRIX" << std::endl;
		std::cout << "Edge: " << firstSet << " - " << secondSet << ", weight: " << min << std::endl;

		finalCost += min;
		edgesCounter++;
	}

	std::cout << "Cost: " << finalCost << std::endl;
}

void AdjencyMatrix::executeDijkstraAlgorithm() {
	std::priority_queue< std::pair<int, int>, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > priorityQueue;
	int distances [numberOfVertices];
	int parents [numberOfVertices];
	bool visited [numberOfVertices];

	for(int i{0}; i < numberOfVertices; i++) {
		distances[i] = INT_MAX;
		parents[i] = -1;
		visited[i] = false;
	}

	priorityQueue.push(std::make_pair(0, sourceVertex));
	distances[sourceVertex] = 0;

	while(!priorityQueue.empty()) {
		int u = priorityQueue.top().second;
		priorityQueue.pop();

		visited[u] = true;

		for(int v{0}; v < numberOfVertices; v++) {
			if (adjencyMatrix[u][v] and !visited[v] and distances[v] > (distances[u] + adjencyMatrix[u][v]) and distances[u] != INT_MAX) {
				distances[v] = distances[u] + adjencyMatrix[u][v];
				parents[v] = u;
				priorityQueue.push(std::make_pair(distances[v], v));
			}
		}

	}

	std::cout << "DIJKSTRA'S ALGORITH - ADJACENCY MATRIX" << std::endl;

}

void AdjencyMatrix::executeFordBellmanAlgorithm() {

}
