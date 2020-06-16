#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"

#include "Test.h"
#include <memory>
#include <chrono>

using namespace std;

void Test::runTests() {
	testPrim();
	testKruskal();
	testDijkstra();
	testBellmanFord();
}

void Test::saveToFile(std::string message)
{
	file.open(filename, std::ios::out | std::ios::app);
	if (file.good())
		file << message << endl;
	else {
			cout << "Test file error occured!" << endl;
		}
	file.close();
}

void Test::saveToFile(std::string algorithm, std::string representation, int density, int vertexCount, double totalTime) {
	std::string message = "";
	message.append(algorithm + "\t");
	message.append(representation + "\t");
	message.append(std::to_string(density) + "\t");
	message.append(std::to_string(vertexCount) + "\t");
	message.append(std::to_string(totalTime));
	this->saveToFile(message);
}

void Test::testPrim() {


	std::unique_ptr<AdjacencyMatrix> adjMatrix;
	std::unique_ptr<AdjacencyList> adjList;


	adjMatrix = std::make_unique<AdjacencyMatrix>(true);
	adjList = std::make_unique<AdjacencyList>(true);

	chrono::high_resolution_clock::time_point startTime;
	chrono::high_resolution_clock::time_point endTime;
	double totalTime = 0;

	cout << "Matrix testing" << endl;

	for (int densityIndex = 0; densityIndex < densityArraySize; densityIndex++) {

		cout << "Density: " << densityTable[densityIndex] << endl;

		for (int vertexCountIndex = 0; vertexCountIndex < vertexArraySize; vertexCountIndex++) {
			cout << "Vertex count: " << vertexCountTable[vertexCountIndex] << endl;
			totalTime = 0;

			for (int i = 0; i < repeatTest; i++) {
				adjMatrix->fillWithRandomData(vertexCountTable[vertexCountIndex], densityTable[densityIndex]);
				startTime = chrono::high_resolution_clock::now();
				adjMatrix->executePrimsAlgorithm();
				endTime = chrono::high_resolution_clock::now();

				double currTime = (double)std::chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
				totalTime += currTime;
				cout << "Progress: " << i <<  "(" << currTime << ")";
			}

			cout << endl;

			saveToFile("Prim", "matrix", densityTable[densityIndex], vertexCountTable[vertexCountIndex],totalTime/repeatTest);

		}
	}

	saveToFile("-------------------------------");


	totalTime = 0;

	cout << "List testing" << endl;

	for (int densityIndex = 0; densityIndex < densityArraySize; densityIndex++) {

		cout << "Density: " << densityTable[densityIndex] << endl;

		for (int vertexCountIndex = 0; vertexCountIndex < vertexArraySize; vertexCountIndex++) {
			cout << "Vertex count: " << vertexCountTable[vertexCountIndex] << endl;
			totalTime = 0;

			for (int i = 0; i < repeatTest; i++) {
				adjList->fillWithRandomData(vertexCountTable[vertexCountIndex], densityTable[densityIndex]);
				startTime = chrono::high_resolution_clock::now();
				adjList->executePrimsAlgorithm();
				endTime = chrono::high_resolution_clock::now();

				double currTime = (double)std::chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
				totalTime += currTime;
				cout << "Progress: " << i <<  "(" << currTime << ")";
			}

			cout << endl;

			saveToFile("Prim", "list", densityTable[densityIndex], vertexCountTable[vertexCountIndex],totalTime/repeatTest);

		}
	}

		saveToFile("-------------------------------");


}


void Test::testKruskal() {

	std::unique_ptr<AdjacencyMatrix> adjMatrix;
	std::unique_ptr<AdjacencyList> adjList;


	adjMatrix = std::make_unique<AdjacencyMatrix>(true);
	adjList = std::make_unique<AdjacencyList>(true);

	chrono::high_resolution_clock::time_point startTime;
	chrono::high_resolution_clock::time_point endTime;
	double totalTime = 0;

	cout << "Matrix testing" << endl;

	for (int densityIndex = 0; densityIndex < densityArraySize; densityIndex++) {

		cout << "Density: " << densityTable[densityIndex] << endl;

		for (int vertexCountIndex = 0; vertexCountIndex < vertexArraySize; vertexCountIndex++) {
			cout << "Vertex count: " << vertexCountTable[vertexCountIndex] << endl;
			totalTime = 0;

			for (int i = 0; i < repeatTest; i++) {
				adjMatrix->fillWithRandomData(vertexCountTable[vertexCountIndex], densityTable[densityIndex]);
				startTime = chrono::high_resolution_clock::now();
				adjMatrix->executeKruskalsAlgorithm();
				endTime = chrono::high_resolution_clock::now();

				double currTime = (double)std::chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
				totalTime += currTime;
				cout << "Progress: " << i <<  "(" << currTime << ")";
			}

			cout << endl;

			saveToFile("Kruskal", "matrix", densityTable[densityIndex], vertexCountTable[vertexCountIndex],totalTime/repeatTest);

		}
	}

	saveToFile("-------------------------------");


	totalTime = 0;

	cout << "List testing" << endl;

	for (int densityIndex = 0; densityIndex < densityArraySize; densityIndex++) {

		cout << "Density: " << densityTable[densityIndex] << endl;

		for (int vertexCountIndex = 0; vertexCountIndex < vertexArraySize; vertexCountIndex++) {
			cout << "Vertex count: " << vertexCountTable[vertexCountIndex] << endl;
			totalTime = 0;

			for (int i = 0; i < repeatTest; i++) {
				adjList->fillWithRandomData(vertexCountTable[vertexCountIndex], densityTable[densityIndex]);
				startTime = chrono::high_resolution_clock::now();
				adjList->executeKruskalsAlgorithm();
				endTime = chrono::high_resolution_clock::now();

				double currTime = (double)std::chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
				totalTime += currTime;
				cout << "Progress: " << i <<  "(" << currTime << ")";
			}

			cout << endl;

			saveToFile("Kruskal", "list", densityTable[densityIndex], vertexCountTable[vertexCountIndex],totalTime/repeatTest);

		}
	}

		saveToFile("-------------------------------");



}


void Test::testDijkstra() {
	std::unique_ptr<AdjacencyMatrix> adjMatrix;
	std::unique_ptr<AdjacencyList> adjList;


	adjMatrix = std::make_unique<AdjacencyMatrix>(false);
	adjList = std::make_unique<AdjacencyList>(false);

	chrono::high_resolution_clock::time_point startTime;
	chrono::high_resolution_clock::time_point endTime;
	double totalTime = 0;

	cout << "Matrix testing" << endl;

	for (int densityIndex = 0; densityIndex < densityArraySize; densityIndex++) {

		cout << "Density: " << densityTable[densityIndex] << endl;

		for (int vertexCountIndex = 0; vertexCountIndex < vertexArraySize; vertexCountIndex++) {
			cout << "Vertex count: " << vertexCountTable[vertexCountIndex] << endl;
			totalTime = 0;

			for (int i = 0; i < repeatTest; i++) {
				adjMatrix->fillWithRandomData(vertexCountTable[vertexCountIndex], densityTable[densityIndex]);
				startTime = chrono::high_resolution_clock::now();
				adjMatrix->executeDijkstraAlgorithm();
				endTime = chrono::high_resolution_clock::now();

				double currTime = (double)std::chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
				totalTime += currTime;
				cout << "Progress: " << i <<  "(" << currTime << ")";
			}

			cout << endl;

			saveToFile("Dijkstra", "Matrix", densityTable[densityIndex], vertexCountTable[vertexCountIndex],totalTime/repeatTest);

		}
	}

	saveToFile("-------------------------------");


	totalTime = 0;

	cout << "List testing" << endl;

	for (int densityIndex = 0; densityIndex < densityArraySize; densityIndex++) {

		cout << "Density: " << densityTable[densityIndex] << endl;

		for (int vertexCountIndex = 0; vertexCountIndex < vertexArraySize; vertexCountIndex++) {
			cout << "Vertex count: " << vertexCountTable[vertexCountIndex] << endl;
			totalTime = 0;

			for (int i = 0; i < repeatTest; i++) {
				adjList->fillWithRandomData(vertexCountTable[vertexCountIndex], densityTable[densityIndex]);
				startTime = chrono::high_resolution_clock::now();
				adjList->executeDijkstraAlgorithm();
				endTime = chrono::high_resolution_clock::now();

				double currTime = (double)std::chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
				totalTime += currTime;
				cout << "Progress: " << i <<  "(" << currTime << ")";
			}

			cout << endl;

			saveToFile("Dijkstra", "list", densityTable[densityIndex], vertexCountTable[vertexCountIndex],totalTime/repeatTest);

		}
	}

		saveToFile("-------------------------------");



}


void Test::testBellmanFord() {
	std::unique_ptr<AdjacencyMatrix> adjMatrix;
	std::unique_ptr<AdjacencyList> adjList;


	adjMatrix = std::make_unique<AdjacencyMatrix>(false);
	adjList = std::make_unique<AdjacencyList>(false);

	chrono::high_resolution_clock::time_point startTime;
	chrono::high_resolution_clock::time_point endTime;
	double totalTime = 0;

	cout << "Matrix testing" << endl;

	for (int densityIndex = 0; densityIndex < densityArraySize; densityIndex++) {

		cout << "Density: " << densityTable[densityIndex] << endl;

		for (int vertexCountIndex = 0; vertexCountIndex < vertexArraySize; vertexCountIndex++) {
			cout << "Vertex count: " << vertexCountTable[vertexCountIndex] << endl;
			totalTime = 0;

			for (int i = 0; i < repeatTest; i++) {
				adjMatrix->fillWithRandomData(vertexCountTable[vertexCountIndex], densityTable[densityIndex]);
				startTime = chrono::high_resolution_clock::now();
				adjMatrix->executeFordBellmanAlgorithm();
				endTime = chrono::high_resolution_clock::now();

				double currTime = (double)std::chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
				totalTime += currTime;
				cout << "Progress: " << i <<  "(" << currTime << ")";
			}

			cout << endl;

			saveToFile("Bellman", "Matrix", densityTable[densityIndex], vertexCountTable[vertexCountIndex],totalTime/repeatTest);

		}
	}

	saveToFile("-------------------------------");


	totalTime = 0;

	cout << "List testing" << endl;

	for (int densityIndex = 0; densityIndex < densityArraySize; densityIndex++) {

		cout << "Density: " << densityTable[densityIndex] << endl;

		for (int vertexCountIndex = 0; vertexCountIndex < vertexArraySize; vertexCountIndex++) {
			cout << "Vertex count: " << vertexCountTable[vertexCountIndex] << endl;
			totalTime = 0;

			for (int i = 0; i < repeatTest; i++) {
				adjList->fillWithRandomData(vertexCountTable[vertexCountIndex], densityTable[densityIndex]);
				startTime = chrono::high_resolution_clock::now();
				adjList->executeFordBellmanAlgorithm();
				endTime = chrono::high_resolution_clock::now();

				double currTime = (double)std::chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
				totalTime += currTime;
				cout << "Progress: " << i <<  "(" << currTime << ")";
			}

			cout << endl;

			saveToFile("Bellman", "list", densityTable[densityIndex], vertexCountTable[vertexCountIndex],totalTime/repeatTest);

		}
	}

		saveToFile("-------------------------------");





}
