#include <iostream>
#include <string>

#include "Application.h"

using namespace std;

void Application::displayMSTMenu() {
	cout << endl;
	cout << "MST" << endl;
	cout << "Pick a number." << endl;
    cout << "1. Read data from file." << endl;
	cout << "2. Fill in random numbers." << endl;
	cout << "3. Print." << endl;
	cout << "4. Prim's algorithm." <<  endl;
	cout << "5. Kruskal's algorithm." << endl;
	cout << "0. Exit" << endl << endl;

}

void Application::displayShortestPathMenu() {
	cout << endl;
	cout << "SHORTEST PATH PROBLEM" << endl;
	cout << "Pick a number." << endl;
    cout << "1. Read data from file." << endl;
	cout << "2. Fill in random numbers." << endl;
	cout << "3. Print." << endl;
	cout << "4. Dijkstra's algorithm." <<  endl;
	cout << "5. Ford-Bellman algorithm." << endl;
	cout << "0. Exit" << endl << endl;

}

void Application::displayMenu() {
	cout << endl;
	cout << "Choose problem to solve." << endl;
	cout << "1. Minimum spanning tree problem." << endl;
	cout << "2. Shortest path problem." << endl;
	cout << "0. Exit" << endl << endl;

}

void Application::run() {


	while(isRunning) {
		displayMenu();
		cin >> problemChosen;

		switch (problemChosen) {
			case '0':
				{
					isRunning = false;
					break;
				}
			case '1':
				{
					MSToperation();
					break;
				}
			case '2':
				{
					shortestPathOperation();
					break;
				}
			default:
				{
					cout << "wrooong number, next time choose better!" << endl << endl;
					break;
				}

		}

	}
}

void Application::MSToperation() {

	adjacencyMatrix = std::make_unique<AdjacencyMatrix>(true);
	adjacencyList = std::make_unique<AdjacencyList>(true);

	bool stop{false};

	while (!stop) {
		displayMSTMenu();
		cin >> operationChosen;

		switch (operationChosen) {
			case '0':
				{
					stop = true;
					break;
				}
			case '1':
				{
					std::string fileName;
					std::cout << "Filename: " << std::endl;
					cin >> fileName;

					adjacencyMatrix->readFromFile(fileName);
					adjacencyMatrix->printMatrix();

					adjacencyList->readFromFile(fileName);
					adjacencyList->printList();

					break;
				}
			case '2':
				{
					adjacencyMatrix->fillWithRandomData(11, 60);
					adjacencyMatrix->printMatrix();

					adjacencyList->fillWithRandomData(11,60);
					adjacencyList->printList();

					break;
				}
			case '3':
				{
					adjacencyMatrix->printMatrix();
					adjacencyList->printList();
					break;
				}
			case '4':
				{
					adjacencyMatrix->executePrimsAlgorithm();
					adjacencyList->executePrimsAlgorithm();
					break;
				}
			case '5':
				{
					adjacencyMatrix->executeKruskalsAlgorithm();
					adjacencyList->executeKruskalsAlgorithm();
					break;
				}
			default:
				{
					cout << "wrooong number, next time choose better!" << endl << endl;
					break;
				}

		}
	}

}

void Application::shortestPathOperation() {
	bool stop{false};

	adjacencyMatrix = std::make_unique<AdjacencyMatrix>(false);
	adjacencyList = std::make_unique<AdjacencyList>(false);

	while (!stop) {
		displayShortestPathMenu();
		cin >> operationChosen;

		switch (operationChosen) {
			case '0':
				{
					stop = true;
					break;
				}
			case '1':
				{
					std::string fileName;
					std::cout << "Filename: " << std::endl;
					cin >> fileName;

					adjacencyMatrix->readFromFile(fileName);
					adjacencyMatrix->printMatrix();

					adjacencyList->readFromFile(fileName);
					adjacencyList->printList();

					break;
				}
			case '2':
				{
					adjacencyMatrix->fillWithRandomData(11, 60);
					adjacencyMatrix->printMatrix();

					adjacencyList->fillWithRandomData(11,60);
					adjacencyList->printList();
					break;
				}
			case '3':
				{
					adjacencyMatrix->printMatrix();
					adjacencyList->printList();
					break;
				}
			case '4':
				{
					adjacencyMatrix->executeDijkstraAlgorithm();
					adjacencyList->executeDijkstraAlgorithm();
					break;
				}
			case '5':
				{
					adjacencyMatrix->executeFordBellmanAlgorithm();
					adjacencyList->executeFordBellmanAlgorithm();
					break;
				}
			default:
				{
					cout << "wrooong number, next time choose better!" << endl << endl;
					break;
				}

		}
	}

}


