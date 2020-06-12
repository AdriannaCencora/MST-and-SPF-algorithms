#include <iostream>
#include <random>

template <class T>
class DynamicArray {
private:
	int size{};
	int capacity{};
	std::unique_ptr<T[]> data{};

public:

	DynamicArray() : capacity(4), data(std::make_unique<T[]>(capacity)) {}
	DynamicArray(int size) : size(size), capacity(size*2), data(std::make_unique<T[]>(capacity)) {}

	~DynamicArray() {}

	void insert(int position, T value) {


		if (position == 0)
			insertFront(value);

		else if (position == size)
			insertBack(value);

		else if (position < 0 or position > size)
			throw std::bad_alloc();

		else
			insertAtPosition(position, value);

	}

	void remove(int position) {

		if (position < 0 or position >= size or (getSize() == 0)) {
			throw std::bad_alloc();
		}

		for (int i{position}; i < (size -1); ++i) {
			data[i] = data[i + 1];
		}

		size--;
	}

	bool search(T value) {

		for (int position{0}; position < size; ++position) {
			if (data[position] == value)
				return true;
		}

		return false;
	}

//	void print() {
//
//		std::cout <<  std::endl << "Dynamic array elements are: " << std::endl;
//
//		for (int i{0}; i < size; i++) {
//			std::cout << data[i] << " ";
//		}
//
//		std::cout << std::endl;
//	}


	void insertFront(T value) {

		if (size == capacity) {
			resize(capacity * 2);
		}

		if (getSize() != 0) {
			for(int position{size-1}; position >= 0; --position) {
				data[position + 1] = data[position];
			}
		}

		data[0] = value;
		++size;
	}

	void insertBack(T value) {
		if (size == capacity) {
			resize(capacity * 2);
		}

		data[size] = value;
		++size;
	}

	void resize(int newCapacity) {

		std::unique_ptr<T[]> dataCopy = std::make_unique<T[]>(newCapacity);

		for(int position{0}; position < size; ++position) {
			dataCopy[position] = data[position];
		}

		capacity = newCapacity;
		reassign(std::move(dataCopy));
	}



	void reassign(std::unique_ptr<T[]> newData) {
		data.reset();
		data = std::move(newData);
	}

	void insertAtPosition(int position, T value) {
		if (size == capacity) {
				resize(capacity * 2);
			}

		ror(position);

		data[position] = value;
		++size;

	}
	void ror(int position) {

		for (int i{size}; i > position; --i) {
			data[i] = data[i-1];
		}
	}

	int getSize() const {
		return size;
	}

	int getCapacity() const {
		return capacity;
	}

	int getDataAt(int position) const {
		return data[position];
	}

	void swapElements(int first, int second) {
		T tmp;
		tmp = data[first];
		data[first] = data[second];
		data[second] = tmp;

	}

	void clearStructure() {
		size = 0;
	}

	T operator[](int position) {
		return data[position];
	}

};
