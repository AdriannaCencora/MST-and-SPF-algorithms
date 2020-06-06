#pragma once

class DisjointSet {
	public:
		DisjointSet(int size);
		~DisjointSet();

		int findSet(int toFind);
		void makeUnion(int first, int second);

	private:
		int *parent;
		int *rank;
		int size;
};
