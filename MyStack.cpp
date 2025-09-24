#include <iostream>
#include <deque>
#include <stdexcept>
#include <sstream>
#include <string>

template<typename type>
class MyStack {
private:
    std::deque<type> data;
public:
    void push(const type& value) {
        data.push_back(value);
    }

    void pop() {
        if (!data.empty()) {
            data.pop_back();
        }
        else {
            throw std::runtime_error("Stack is empty");
        }
    }

    type& top() {
        if (!data.empty()) {
            return data.back();
        }
        else {
            throw std::runtime_error("Stack is empty");
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
    MyStack<int> gaogao;
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