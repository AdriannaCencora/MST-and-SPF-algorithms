#pragma once

#include <memory>

#include "AdjacencyMatrix.h"
#include "AdjacencyList.h"

class Application {
	public:
    Application() = default;
    ~Application() = default;

	void run();


	private:
	std::unique_ptr<AdjacencyMatrix> adjacencyMatrix;
	std::unique_ptr<AdjacencyList> adjacencyList;

	char problemChosen{};
	char operationChosen{};
    bool isRunning{true};

    void displayMSTMenu();
    void displayShortestPathMenu();
    void displayMenu();

	void MSToperation();
	void shortestPathOperation();

};
