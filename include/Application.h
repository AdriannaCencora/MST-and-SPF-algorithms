#pragma once

#include <memory>

#include "AdjencyMatrix.h"

class Application {
	public:
    Application() = default;

    ~Application() = default;

	void run();


	private:
	std::unique_ptr<AdjencyMatrix> adjencyMatrix;

	char problemChosen{};
	char operationChosen{};
    bool isRunning{true};

    void displayMSTMenu();
    void displayShortestPathMenu();
    void displayMenu();

	void MSToperation();
	void shortestPathOperation();

};
