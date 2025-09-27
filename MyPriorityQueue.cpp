#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

template<typename type, typename Compare = std::less<type>>
class MyPriorityQueue {
private:
    using container = std::vector<type>;
    container data;
    Compare comp;
public:
    MyPriorityQueue() = default;

    MyPriorityQueue(const container& c) :data(c) {
        std::make_heap(data.begin(), data.end(), comp);
    }

    void push(const type& value) {
        data.push_back(value);
        std::push_heap(data.begin(), data.end(), comp);
    }

    void pop() {
        if (!empty()) {
            std::pop_heap(data.begin(), data.end(), comp);
            data.pop_back();
        }
        else {
            throw std::runtime_error("Priority queue is empty");
        }
    }

    type& top() {
        if (!empty()) {
            return data.front();
        }
        else {
            throw std::runtime_error("Priority queue is empty");
        }
    }

    const type& top() const {
        if (!empty()) {
            return data.front();
        }
        else {
            throw std::runtime_error("Priority queue is empty");
        }
    }

    size_t size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }

    void clear() noexcept {
        data.clear();
    }
};

int main(int argc, char* argv[])
{
    MyPriorityQueue<int> gaogao;
    int N;
    std::cin >> N;
    getchar();

    std::string line;
    int value;
    while (N--) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        if (command == "push") {
            iss >> value;
            gaogao.push(value);
        }
        else if (command == "pop") {
            try {
                gaogao.pop();
            }
            catch (const std::runtime_error& e) {

            }
        }
        else if (command == "top") {
            try {
                std::cout << gaogao.top() << std::endl;
            }
            catch (const std::runtime_error& e) {
                std::cout << "null" << std::endl;
            }
        }
        else if (command == "empty") {
            std::cout << (gaogao.empty() ? "true" : "false") << std::endl;
        }
        else if (command == "size") {
            std::cout << gaogao.size() << std::endl;
        }
    }

    return 0;
}