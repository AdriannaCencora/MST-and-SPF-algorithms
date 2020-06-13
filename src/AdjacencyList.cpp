#include <climits>
#include <random>
#include <fstream>
#include <iomanip>

#include "AdjacencyList.h"
#include "DisjointSet.h"
#include "Heap.h"

void AdjacencyList::initialize() {

	adjacencyList = new DoubleLinkedList<Edge>[numberOfVertices];

}

void AdjacencyList::addEdge(int from, int to, int value) {

	adjacencyList[from].insertBack(Edge(to, value));

	if (isMST)
		adjacencyList[to].insertBack(Edge(from, value));

}

void AdjacencyList::printList() {

	std::cout << std::endl << "ADJACENCY LIST" << std::endl;
	for(int i{0}; i < numberOfVertices; i++) {
		std::cout << "Vertex[" << i << "]: ";
		adjacencyList[i].print();
		std::cout << std::endl;
	}
}

void AdjacencyList::readFromFile(std::string fileName) {
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

void AdjacencyList::fillWithRandomData(int numberOfVertices, int density) {

	//TODO: IMPLEMENT ME
	const int upperRange = 150;
	std::random_device seed;
	std::mt19937 randomGenerator(seed());
	std::uniform_int_distribution<> transform(1, upperRange);

}

void AdjacencyList::clear() {
	if (adjacencyList != nullptr) {
		for (int i {0}; i < numberOfVertices; i++) {
			adjacencyList[i].clearStructure();
		}

		delete[] adjacencyList;
	}

	numberOfEdges = 0;
	numberOfVertices = 0;
	adjacencyList = nullptr;
}

void AdjacencyList::executePrimsAlgorithm() {
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

	while(!priorityQueue.isEmpty()) {
		int u = priorityQueue.popElement().second;
		visited[u] = true;

		adjacencyList[u].setCurrentNodeToHead();
		while(adjacencyList[u].hasNextNode()) {

			int v = adjacencyList[u].getNextNode().first;
			int weight = adjacencyList[u].getNextNode().second;

			if (visited[v] == false and weight < mst[v]) {
				mst[v] = weight;
				parents[v] = u;
				priorityQueue.insert(Edge(mst[v], v));
			}
		}
	}

	int finalCost{0};

	std::cout << "PRIM'S ALGORITHM - ADJACENCY LIST" << std::endl;
	for(int i{1}; i < numberOfVertices; i++) {
		std::cout << "Edge: " << parents[i] << " - " << i << ", weight: " << mst[i] << std::endl;
		finalCost += mst[i];
	}

	std::cout << "Cost: " << finalCost << std::endl;

}

void AdjacencyList::executeKruskalsAlgorithm() {

}

void AdjacencyList::executeDijkstraAlgorithm() {}
void AdjacencyList::executeFordBellmanAlgorithm() {}
