#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <stdexcept>

template <typename type>
class MyVector {
private:
    type* elements;
    size_t capacity;//数组容量
    size_t size;//数组中元素的个数
private:
    void reserve(size_t new_capacity) {
        if (new_capacity <= capacity) {
            return;
        }
        type* new_elements = new type[new_capacity];
        std::copy(elements, elements + size, new_elements);
        delete[] elements;
        elements = new_elements;
        capacity = new_capacity;
    }
public:
    MyVector() :elements(nullptr), capacity(0), size(0) {

    };

    ~MyVector() {
        delete[] elements;
    }

    MyVector(const MyVector<type>& other)
        :capacity(other.capacity), size(other.size) {
        elements = new type[capacity];
        std::copy(other.elements, other.elements + size, elements);
    }

    MyVector& operator=(const MyVector<type>& other) {//运算符重载
        if (this != &other) {
            delete[] elements;
            capacity = other.capacity;
            size = other.size;
            elements = new type[capacity];
            std::copy(other.elements, other.elements + size, elements);
        }
        return *this;
    }

    void push_back(const type& data) {
        if (size == capacity) {
            size_t new_capacity = (capacity == 0) ? 1 : 2 * capacity;
            reserve(new_capacity);
        }
        elements[size++] = data;
    }

    size_t get_size() {
        return size;
    }

    size_t get_capacity() {
        return capacity;
    }

    type& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("索引越界!");
        }
        return elements[index];
    }

    const type& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("索引越界!");
        }
        return elements[index];
    }

    void insert(size_t index, const type& data) {
        if (index >= size) {
            throw std::out_of_range("索引越界!");
        }
        if (size == capacity) {
            size_t new_capacity = (capacity == 0) ? 1 : 2 * capacity;
            reserve(new_capacity);
        }
        for (size_t i = size; i != index; --i) {
            elements[i] = elements[i - 1];
        }
        elements[index] = data;
        ++size;
    }

    void pop_back() {
        if (size > 0) {
            --size;
        }
    }

    void clear() {
        size = 0;
    }

    type* begin() {
        return elements;
    }

    type* end() {
        return elements + size;
    }

    const type* begin() const {
        return elements;
    }

    const type* end() const {
        return elements + size;
    }

    void traverse() {
        if (size == 0) {
            std::cout << "empty" << std::endl;
        }
        else {
            for (type* it = begin(); it != end(); ++it) {
                std::cout << *it;
                if (it != end() - 1) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    }

    void print() const {
        if (size == 0) {
            std::cout << "empty" << std::endl;
        }
        else {
            for (size_t i = 0; i != size; ++i) {
                std::cout << elements[i];
                if (i != size - 1) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    }
};

int main(int argc, char* argv[])
{
    int N;
    std::cin >> N;
    getchar();

    std::string line;
    MyVector<int> gaogao;

    while (N--) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        if (command == "push") {
            int num;
            iss >> num;
            gaogao.push_back(num);
        }
        else if (command == "size") {
            std::cout << gaogao.get_size() << std::endl;
        }
        else if (command == "get") {
            int index;
            iss >> index;
            try {
                std::cout << gaogao[index] << std::endl;
            }
            catch (const std::out_of_range& e) {
                std::cout << -1 << std::endl;
            }
        }
        else if (command == "insert") {
            int index, data;
            iss >> index >> data;
            gaogao.insert(index, data);
        }
        else if (command == "pop") {
            gaogao.pop_back();
        }
        else if (command == "clear") {
            gaogao.clear();
        }
        else if (command == "print") {
            gaogao.print();
        }
        else if (command == "iterator") {
            gaogao.traverse();
        }
        else if (command == "foreach") {
            if (gaogao.get_size() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            for (const auto& element : gaogao)
            {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}