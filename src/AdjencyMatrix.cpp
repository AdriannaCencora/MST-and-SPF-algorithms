#include <climits>
#include <random>
#include <fstream>
#include <iomanip>
#include <queue>
#include "AdjencyMatrix.h"

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


void AdjencyMatrix::executePrimAlgorithm() {
	std::priority_queue< std::pair<int, int>, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > priorityQueue;
	int mst [numberOfVertices];		//the cheapest cost of a connection to vertex v
	int parents [numberOfVertices];	//edges providing that cheapest connection
	bool visited [numberOfVertices];	//

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
	for(int i{1}; i < numberOfVertices; i++) {
		std::cout << "Edge: " << parents[i] << " - " << i << ", weight: " << mst[i] << std::endl;
		finalCost += mst[i];
	}

	std::cout << "Cost: " << finalCost << std::endl;

}

