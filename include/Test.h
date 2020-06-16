#include <iostream>
#include <string>

#include <fstream>
#include <sstream>

class Test {
	public:
		void runTests();

	private:
		std::ofstream file;
		std::string filename = "Tests";
		static const int densityArraySize = 3;
		static const int vertexArraySize = 7;
		int repeatTest = 100;

		int densityTable[densityArraySize] = {20, 60, 99};
		int vertexCountTable[vertexArraySize] = {50, 100, 150, 200, 250, 300, 350};

		void testPrim();
		void testKruskal();
		void testDijkstra();
		void testBellmanFord();

		void saveToFile(std::string algorithm, std::string representation, int density, int vertexCount, double totalTime);
		void saveToFile(std::string message);
};

