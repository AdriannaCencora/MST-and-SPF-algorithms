#include "DisjointSet.h"

DisjointSet::DisjointSet(int size) {
	size = size;
	parent = new int [size];
	rank = new int [size];

	for (int i{0}; i < size; i++) {
		rank[i] = 0;
		parent[i] = i;
	}

}

DisjointSet::~DisjointSet() {
	delete[] parent;
	delete[] rank;
}

int DisjointSet::findSet(int toFind) {
	if(toFind != parent[toFind])
		parent[toFind] = findSet(parent[toFind]);

	return parent[toFind];
}

void DisjointSet::makeUnion(int first, int second) {
	first = findSet(first);
	second = findSet(second);

	if (rank[first] > rank[second])
		parent[second] = first;
	else
		parent[first] = second;

	if (rank[first] == rank[second])
		rank[first]++;

}
