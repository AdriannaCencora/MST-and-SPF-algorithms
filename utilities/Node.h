struct Node {
	Node() = default;
	Node(int first, int second) : first(first), second(second) {}

	int first;
	int second;


	bool operator==(const Node &node) const {
		return first == node.first;
	}

	bool operator<(const Node &node) const {
		return first < node.first;
	}

	bool operator>(const Node &node) const {
		return first > node.first;
	}

	bool operator!=(const Node &node) const {
		return first != node.first;
	}

};
