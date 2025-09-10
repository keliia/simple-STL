#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <algorithm>

template<typename type>
class MyDeque {
private:
    type* elements;
    size_t size;
    size_t capacity;
    size_t front_index;//当前队头元素位置
    size_t back_index;//下一个要插入的位置

public:
    MyDeque() :elements(nullptr), size(0), capacity(0), front_index(0), back_index(0) {

    }

    MyDeque(const MyDeque& other)
        :size(other.size), capacity(other.capacity), front_index(0), back_index(other.size) {
        elements = new type[capacity];
        if (other.front_index == 0) {
            std::copy(other.elements, other.elements + size, elements);
        }
        else if (other.front_index > other.back_index) {
            std::copy(other.elements + other.front_index, other.elements + other.capacity, elements);
            std::copy(other.elements, other.elements + other.back_index, elements + other.capacity - other.front_index);
        }
        else {
            std::copy(other.elements + other.front_index, other.elements + other.back_index, elements);
        }
    }

    MyDeque& operator=(const MyDeque& other) {
        if (this != &other) {
            delete[] elements;
            size = other.size;
            capacity = other.capacity;
            front_index = 0;
            back_index = size;
            elements = new type[capacity];
            if (other.front_index == 0) {
                std::copy(other.elements, other.elements + size, elements);
            }
            else if (other.front_index > other.back_index) {
                std::copy(other.elements + other.front_index, other.elements + other.capacity, elements);
                std::copy(other.elements, other.elements + other.back_index, elements + other.capacity - other.front_index);
            }
            else {
                std::copy(other.elements + other.front_index, other.elements + other.back_index, elements);
            }
        }
        return *this;
    }

    ~MyDeque() {
        delete[] elements;
    }

    void push_back(const type& value) {
        if (size == capacity) {
            reserve();
        }
        elements[back_index] = value;
        back_index = (back_index + 1) % capacity;
        ++size;
    }

    void push_front(const type& value) {
        if (size == capacity) {
            reserve();
        }
        front_index = (front_index - 1 + capacity) % capacity;
        elements[front_index] = value;
        ++size;
    }

    void pop_back() {
        if (size == 0) {
            throw std::out_of_range("Deque is empty!");
        }
        back_index = (back_index - 1 + capacity) % capacity;
        --size;
    }

    void pop_front() {
        if (size == 0) {
            throw std::out_of_range("Deque is empty!");
        }
        front_index = (front_index + 1) % capacity;
        --size;
    }

    size_t getsize() {
        return size;
    }

    const size_t getsize() const {
        return size;
    }

    void clear() {
        front_index = 0;
        back_index = 0;
        size = 0;
    }

    type& operator[](const size_t& index) {
        if (index >= size) {
            throw std::out_of_range("Out of range!");
        }
        return elements[(front_index + index) % capacity];
    }

    const type& operator[](const size_t& index) const {
        if (index >= size) {
            throw std::out_of_range("Out of range!");
        }
        return elements[(front_index + index) % capacity];
    }
private:
    void reserve() {
        size_t new_capacity = capacity == 0 ? 1 : 2 * capacity;
        type* new_elements = new type[new_capacity];
        if (front_index == 0) {
            std::copy(elements, elements + size, new_elements);
        }
        else {
            std::copy(elements + front_index, elements + capacity, new_elements);
            std::copy(elements, elements + back_index, new_elements + capacity - front_index);
        }
        delete[] elements;
        elements = new_elements;
        capacity = new_capacity;
        front_index = 0;
        back_index = size;
    }
};

int main(int argc, char* argv[])
{
    int N;
    std::cin >> N;
    getchar();

    std::string line;
    std::string command;

    MyDeque<int> gaogao;
    while (N--) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        iss >> command;
        if (command == "push_back") {
            int value;
            iss >> value;
            gaogao.push_back(value);
        }
        else if (command == "push_front") {
            int value;
            iss >> value;
            gaogao.push_front(value);
        }
        else if (command == "pop_back") {
            try {
                gaogao.pop_back();
            }
            catch (const std::out_of_range& e) {

            }
        }
        else if (command == "pop_front") {
            try {
                gaogao.pop_front();
            }
            catch (const std::out_of_range& e) {

            }
        }
        else if (command == "clear") {
            gaogao.clear();
        }
        else if (command == "size") {
            std::cout << gaogao.getsize() << std::endl;
        }
        else if (command == "get") {
            int index;
            iss >> index;
            try {
                std::cout << gaogao[index] << std::endl;
            }
            catch (const std::out_of_range& e) {

            }
        }
        else if (command == "print") {
            if (gaogao.getsize() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            for (size_t i = 0; i != gaogao.getsize(); ++i) {
                std::cout << gaogao[i];
                if (i != gaogao.getsize() - 1) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    }

    return 0;
}