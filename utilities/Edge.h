struct Edge {
	Edge() = default;
	Edge(int first, int second) : first(first), second(second) {}

	int first;
	int second;


	bool operator==(const Edge &edge) const {
		return first == edge.first;
	}

	bool operator<(const Edge &edge) const {
		return first < edge.first;
	}

	bool operator>(const Edge &edge) const {
		return first > edge.first;
	}

	bool operator!=(const Edge &edge) const {
		return first != edge.first;
	}

};
