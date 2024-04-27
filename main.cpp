#include <iostream>

template<typename T>
class MyStack {
public:
	//IMPLEMENTING THE RULE OF 5
	MyStack() {
		capacity = 5;
		size = 0;
		data = new T[capacity];
		std::cout << "Default constructor" << std::endl;
	}
	
	MyStack(const MyStack& obj) {
		std::cout << "Copy constructor" << std::endl;
		//1. delete previous data
		//2. resize
		//3. copy variables
		//4. resize data stack
		//5. copy data to stack
		if (obj.capacity > this->capacity) {
			delete[] this->data;
			this->capacity = obj.capacity;
			this->data = new T[this->capacity];
			this->size = obj.size;
		}
		// it is possible to have previous data of the stack after we resize it
		// but we don't process it
		// we just treat it like empty space, aka "garbage"
		for (size_t i = 0; i < obj.size; i++) {
			this->data[i] = obj.data[i];
		}

	}
	MyStack(MyStack&& other) noexcept {
		std::cout << "Move constructor" << std::endl;
		delete[] data;
		this->data = other.data;
		this->size = other.size;
		this->capacity = other.capacity;
		other.data = nullptr;
		other.size = 0;
		other.capacity = 0;
	}
	~MyStack() {
		std::cout << "Destructor" << std::endl;
		delete[] data;
	}

	MyStack& operator=(const MyStack& rhs) {
		std::cout << "Copy assignment operator" << std::endl;
		if (this != &rhs) {
			//1. delete previous data
			//2. resize
			//3. copy variables
			//4. resize data stack
			//5. copy data to stack
			if (rhs.capacity > this->capacity) {
				delete[] this->data;
				this->capacity = rhs.capacity;
				this->size = rhs.size;
				this->data = new T[this->capacity];
				
			}
			// it is possible to have previous data of the stack after we resize it
			// but we don't process it
			// we just treat it like empty space, aka "garbage"
			for (size_t i = 0; i < rhs.size; i++) {
				this->data[i] = rhs.data[i];
			}
		}
		return *this;
	}
	MyStack& operator=(MyStack&& rhs) noexcept {
		std::cout << "Move assignment operator" << std::endl;
		if (this != &rhs) {
			delete[] this->data;
			this->data = rhs.data;
			this->size = rhs.size;
			this->capacity = rhs.capacity;
			rhs.data = nullptr;
			rhs.size = 0;
			rhs.capacity = 0;
		}
		return *this;
	}
	void push(const T& value) {
		if (capacity > size) {
			data[size] = value;
			
		}
		else {
			capacity = capacity + 5;
			T* tempData = new T[capacity];
			for (size_t i = 0; i < size; i++) {
				tempData[i] = data[i];
			}
			delete[] data;
			data = tempData;
			data[size] = value;
		}
		size++;
	}
	T pop() {
		if (size) {
			return data[--size];
		}
		else {
			std::cerr << "Stack is empty" << std::endl;
            return 0;
		}
	}
	size_t getSize() {
		return size;
	}
	size_t getCapacity() {
		return capacity;
	}

private:
	T* data = nullptr;
	size_t capacity;
	size_t size;
};



int main() {
	MyStack<int> testStack;
		testStack.push(1);
		testStack.push(2);
		testStack.push(3);
		testStack.push(4);
		testStack.push(5);
		testStack.push(6);
		testStack.push(7);
		MyStack<int> newStack;
        newStack = std::move(testStack);
		while (newStack.getSize()) {
			std::cout << newStack.pop();
		}
        std::cout << std::endl;
		testStack.push(11);
		testStack.push(12);
		testStack.push(13);
		testStack.push(14);
		testStack.push(15);
		testStack.push(16);
		testStack.push(17);

        while (testStack.getSize()) {
			std::cout << testStack.pop();
		}
		std::cout << std::endl;
	
	int *i = nullptr;
	delete i;
	return 0;
}