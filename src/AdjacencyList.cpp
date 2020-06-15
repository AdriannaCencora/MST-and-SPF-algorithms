#include <climits>
#include <random>
#include <fstream>
#include <iomanip>

#include "AdjacencyList.h"
#include "DisjointSet.h"
#include "Heap.h"

void AdjacencyList::initialize() {

	adjacencyList = new DoubleLinkedList<Edge>[numberOfVertices];

	srand (time(NULL));
}

void AdjacencyList::addEdge(int from, int to, int value) {

	adjacencyList[from].insertBack(Edge(to, value));
	numberOfEdges++;

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

int AdjacencyList::getCurrentDensity() {
	int maxEdgeAmount = numberOfVertices * (numberOfVertices - 1);

	if(isMST)
		maxEdgeAmount /= 2;

	return (int)(((float)numberOfEdges / (float)maxEdgeAmount) * 100);
}

bool AdjacencyList::findEdge(int from, int to) {
	adjacencyList[from].setCurrentNodeToHead();

	while(adjacencyList[from].hasNodes()) {
		auto nodeData = adjacencyList[from].getNodeData();

		if(nodeData.first == to)
			return true;
	}

	return false;
}

void AdjacencyList::fillWithRandomData(int givenNumberOfVertices, int density) {

	int weightRange = 100;
	int weightBase = 1;
	clear();

	numberOfVertices = givenNumberOfVertices;

	std::cout <<  numberOfVertices << std::endl;

	initialize();

	//dummy mst TODO: improve method
	for(int i{1}; i < numberOfVertices; i++) {
		int weight = rand() % weightRange + weightBase;
		addEdge(0, i, weight);
	}

	std::cout << "getCurrentDensity: " << getCurrentDensity() << std::endl;
	std::cout << "Density: " << density << std::endl;
	while (getCurrentDensity() < density) {
	std::cout << "getCurrentDensity: " << getCurrentDensity() << std::endl;
		int from = rand() % numberOfVertices;
		int to = rand() % numberOfVertices;
		int weight = rand() % weightRange + weightBase;
		std::cout << "from: " << from << " to: " <<  to <<  std::endl;
		printList();
		if (from == to) {
			std::cout << " if (from == to): ";
			std::cout << "from: " << from << " to: " <<  to <<  std::endl;
			continue;
		}

		if (findEdge(from, to)) {
			std::cout << " findEdge(from, to): ";
			std::cout << "from: " << from << " to: " <<  to <<  std::endl;
			continue;
		}

		addEdge(from, to, weight);

	}

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
		while(adjacencyList[u].hasNodes()) {

			auto nodeData = adjacencyList[u].getNodeData();
			int v = nodeData.first;
			int weight = nodeData.second;

			if (!visited[v] and weight < mst[v]) {
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
	DisjointSet disjointSet(numberOfVertices);
	Heap<KruskalEdge> priorityQueue;
	int finalCost{0};

	//prepare and sort
	for (int u{0}; u < numberOfVertices; u++) {

		adjacencyList[u].setCurrentNodeToHead();

		 while(adjacencyList[u].hasNodes()) {
			auto nodeData = adjacencyList[u].getNodeData();
			int dest = nodeData.first;
			int weight = nodeData.second;
			priorityQueue.insert(KruskalEdge(u, dest, weight));

		 }
	}


	std::cout << std::endl << "KRUSKAL'S ALGORITHM - ADJACENCY LIST" << std::endl;
	while(!priorityQueue.isEmpty()) {
		auto edge = priorityQueue.popElement();
		int u = edge.from;
		int v = edge.to;

		if (disjointSet.findSet(u) != disjointSet.findSet(v)) {
			int min = edge.weight;
			int firstSet = u;
			int secondSet = v;

			disjointSet.makeUnion(firstSet, secondSet);

			std::cout << "Edge: " << firstSet << " - " << secondSet << ", weight: " << min << std::endl;

			finalCost += min;

		}
	}

	std::cout << "Cost: " << finalCost << std::endl;
}

void AdjacencyList::printParents(int *parents, int vertex) {
	if (parents[vertex] == -1)
		return;
	printParents(parents, parents[vertex]);
	std::cout << " -> " <<  vertex;

}

void AdjacencyList::executeDijkstraAlgorithm() {
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

		adjacencyList[u].setCurrentNodeToHead();
		while(adjacencyList[u].hasNodes()) {
			auto nodeData = adjacencyList[u].getNodeData();
			int v = nodeData.first;
			int weight = nodeData.second;

			if(!visited[v] and distances[v] > (distances[u] + weight)) {
				distances[v] = distances[u] + weight;
				parents[v] = u;
				priorityQueue.insert(Edge(distances[v], v));
			}
		}
	}

	std::cout << std::endl << "DIJKSTRA'S ALGORITHM - ADJACENCY LIST" << std::endl;

	for (int i{0}; i < numberOfVertices; i++) {
		std::cout << "Path: " << sourceVertex;

		if (distances[i] != INT_MAX) {
			printParents(parents, i);
			std::cout << " weight: " << distances[i] << std::endl;
		}
	}


}

void AdjacencyList::executeFordBellmanAlgorithm() {
	int distances [numberOfVertices];
	int parents [numberOfVertices];

	for(int i{0}; i < numberOfVertices; i++) {
		distances[i] = INT_MAX;
		parents[i] = -1;
	}

	distances[sourceVertex] = 0;
	bool changed = true;

	for(int i{0}; i < numberOfVertices - 1; i++) {
		for (int u{0}; u < numberOfVertices; u++) {

			if (distances[u] == INT_MAX)
				continue;

			adjacencyList[u].setCurrentNodeToHead();
			while(adjacencyList[u].hasNodes()) {
				auto nodeData = adjacencyList[u].getNodeData();
				int v = nodeData.first;
				int weight = nodeData.second;

				if(distances[v] > (distances[u] + weight)) {
					distances[v] = distances[u] + weight;
					parents[v] = u;
					changed = true;
				}
			}
		}

		if(!changed)
			break;

		changed = false;
	}

		for (int u{0}; u < numberOfVertices; u++) {

			if (distances[u] == INT_MAX)
				continue;

			while(adjacencyList[u].hasNodes()) {
				auto nodeData = adjacencyList[u].getNodeData();
				int v = nodeData.first;
				int weight = nodeData.second;

				if (distances[v] > (distances[u] + weight)) {
					std::cout << "Graph contains a negative-weight cycle." << std::endl;
					return;
				}
			}
		}

	std::cout << std::endl << "BELLMAN-FORD'S ALGORITHM - ADJACENCY LIST" << std::endl;

	for (int i{0}; i < numberOfVertices; i++) {
		std::cout << "Path: " << sourceVertex;

		if (distances[i] != INT_MAX) {
			printParents(parents, i);
			std::cout << " weight: " << distances[i] << std::endl;
		}
	}



}
