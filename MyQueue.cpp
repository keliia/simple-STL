#include <iostream>
#include <deque>
#include <string>
#include <sstream>

template<typename type, typename container = std::deque<type>>
class MyQueue {
private:
    container data;
public:
    void push(const type& value) {
        data.push_back(value);
    }

    void pop() {
        if (!data.empty()) {
            data.pop_front();
        }
        else {
            throw std::runtime_error("Queue is empty");
        }
    }

    type& front() {
        if (!data.empty()) {
            return data.front();
        }
        else {
            throw std::runtime_error("Queue is empty");
        }
    }

    type& back() {
        if (!data.empty()) {
            return data.back();
        }
        else {
            throw std::runtime_error("Queue is empty");
        }
    }

    bool empty() {
        return data.empty();
    }

    size_t size() {
        return data.size();
    }
};

int main(int argc, char* argv[])
{
    MyQueue<int> gaogao;
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
        else if (command == "front") {
            try {
                std::cout << gaogao.front() << std::endl;
            }
            catch (const std::runtime_error& e) {

            }
        }
        else if (command == "back") {
            try {
                std::cout << gaogao.back() << std::endl;
            }
            catch (const std::runtime_error& e) {

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