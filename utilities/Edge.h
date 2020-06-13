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

struct KruskalEdge {
	KruskalEdge() = default;
	KruskalEdge(int from, int to, int weight) : from(from), to(to), weight(weight) {}

	int from;
	int to;
	int weight;

	bool operator==(const KruskalEdge &edge) const {
		return  weight == edge.weight;
	}

	bool operator<(const KruskalEdge &edge) const {
		return weight < edge.weight;
	}

	bool operator>(const KruskalEdge &edge) const {
		return weight > edge.weight;
	}

	bool operator!=(const KruskalEdge &edge) const {
		return weight != edge.weight;
	}



};
