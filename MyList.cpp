#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

template<typename type>
class MyList {
private:
    struct Node {
        type data;
        Node* prev;
        Node* next;

        Node(const type& value = type(), Node* p = nullptr, Node* n = nullptr)
            :data(value), prev(p), next(n) {

        }
    };
private:
    Node* head;
    Node* tail;
    size_t size;
public:
    MyList() :head(nullptr), tail(nullptr), size(0) {}

    ~MyList() {
        clear();
    }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    void push_back(const type& value) {
        Node* n = new Node(value, tail, nullptr);
        if (tail != nullptr) {
            tail->next = n;
        }
        else {
            head = n;
        }
        tail = n;
        ++size;
    }

    void push_front(const type& value) {
        Node* n = new Node(value, nullptr, head);
        if (head != nullptr) {
            head->prev = n;
        }
        else {
            tail = n;
        }
        head = n;
        ++size;
    }

    size_t get_size() {
        return size;
    }

    size_t get_size() const {
        return size;
    }

    void pop_back() {
        if (size > 0) {
            if (head == tail) {
                delete tail;
                head = nullptr;
                tail = nullptr;
            }
            else {
                tail = tail->prev;
                delete tail->next;
                tail->next = nullptr;
            }
            --size;
        }
        else {
            throw std::runtime_error("不能从空链表删除元素!");
        }
    }

    void pop_front() {
        if (size > 0) {
            if (head == tail) {
                delete head;
                head = nullptr;
                tail = nullptr;
            }
            else {
                head = head->next;
                delete head->prev;
                head->prev = nullptr;
            }
            --size;
        }
        else {
            throw std::runtime_error("不能从空链表删除元素!");
        }
    }

    void remove(const type& value) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == value) {
                Node* n = temp;
                temp = temp->next;
                if (n != head && n != tail) {
                    n->prev->next = n->next;
                    n->next->prev = n->prev;
                }
                else if (n == head && n == tail) {
                    head = nullptr;
                    tail = nullptr;
                }
                else if (n == head) {
                    head = head->next;
                    head->prev = nullptr;
                }
                else if (n == tail) {
                    tail = tail->prev;
                    tail->next = nullptr;
                }
                delete n;
                n = nullptr;
                --size;
            }
            else {
                temp = temp->next;
            }
        }
    }

    Node* begin() {
        return head;
    }

    Node* end() {
        return nullptr;
    }

    const Node* begin() const {
        return head;
    }

    const Node* end() const {
        return nullptr;
    }

    void print() const {
        if (size == 0) {
            std::cout << "empty";
        }
        for (auto it = begin(); it != end(); it = it->next) {
            std::cout << it->data;
            if (it != tail) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    type& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("下标越界!");
        }
        Node* n = head;
        for (size_t i = 0; i != index; ++i) {
            if (n == nullptr) {
                throw std::runtime_error("下标越界!");
            }
            n = n->next;
        }
        if (n == nullptr) {
            throw std::runtime_error("下标越界!");
        }
        return n->data;
    }

    const type& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("下标越界!");
        }
        const Node* n = head;
        for (size_t i = 0; i != index; ++i) {
            if (n == nullptr) {
                throw std::runtime_error("下标越界!");
            }
            n = n->next;
        }
        if (n == nullptr) {
            throw std::runtime_error("下标越界!");
        }
        return n->data;
    }
private:
    template<typename form>
    friend std::ostream& operator<<(std::ostream& stream, const MyList<form>& list);
};

template<typename form>
std::ostream& operator<<(std::ostream& stream, const MyList<form>& list) {
    if (list.get_size() == 0) {
        stream << "empty";
    }
    for (auto it = list.begin(); it != list.end(); it = it->next) {
        stream << it->data;
        if (it->next != list.end()) {
            stream << " ";
        }
    }
    stream << std::endl;
    return stream;
}

int main(int argc, char* argv[])
{
    int N;
    std::cin >> N;
    getchar();

    std::string str;
    MyList<int> gaogao;

    while (N--) {
        std::getline(std::cin, str);
        std::istringstream iss(str);

        std::string command;
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
            catch (const std::runtime_error& e) {

            }
        }
        else if (command == "pop_front") {
            try {
                gaogao.pop_front();
            }
            catch (const std::runtime_error& e) {

            }
        }
        else if (command == "remove") {
            int value;
            iss >> value;
            gaogao.remove(value);
        }
        else if (command == "clear") {
            gaogao.clear();
        }
        else if (command == "size") {
            std::cout << gaogao.get_size() << std::endl;
        }
        else if (command == "get") {
            size_t index;
            if (!(iss >> index)) {
                std::cout << -1 << std::endl;
                continue;
            }
            try {
                std::cout << gaogao[index] << std::endl;
            }
            catch (const std::out_of_range& e) {
                std::cout << -1 << std::endl;
            }
            catch (const std::runtime_error& e) {
                std::cout << -1 << std::endl;
            }
        }
        else if (command == "print") {
            gaogao.print();
        }
    }

    return 0;
}