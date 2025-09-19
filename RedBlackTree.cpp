#include <iostream>
#include <sstream>
#include <string>

template<typename KEY, typename VALUE>
class RedBlackTree {
private:
    enum class colour {
        RED, BLACK
    };

    struct Node {
        KEY key;
        VALUE value;
        colour color;
        Node* left;
        Node* right;
        Node* parent;

        Node(const KEY& k, const VALUE& v, colour c, Node* p = nullptr) :key(k), value(v), color(c), left(nullptr), right(nullptr), parent(p) {

        }

        Node() :color(colour::BLACK), left(nullptr), right(nullptr), parent(nullptr) {

        }
    };
private:
    Node* root;
    Node* nil;
    size_t size;

    Node* find(const KEY& key) {
        Node* cmpNode = root;
        while (cmpNode != nil) {
            if (key < cmpNode->key) {
                cmpNode = cmpNode->left;
            }
            else if (key > cmpNode->key) {
                cmpNode = cmpNode->right;
            }
            else {
                return cmpNode;
            }
        }
        return nil;
    }

    void leftRotate(Node* node) {
        Node* r_son = node->right;
        node->right = r_son->left;
        if (r_son->left != nil) {
            r_son->left->parent = node;
        }

        r_son->parent = node->parent;
        if (node->parent == nil) {
            root = r_son;
        }
        else if (node->parent->left == node) {
            node->parent->left = r_son;
        }
        else {
            node->parent->right = r_son;
        }

        r_son->left = node;
        node->parent = r_son;
    }

    void rightRotate(Node* node) {
        Node* l_son = node->left;
        node->left = l_son->right;
        if (l_son->right != nil) {
            l_son->right->parent = node;
        }

        l_son->parent = node->parent;
        if (node->parent == nil) {
            root = l_son;
        }
        else if (node->parent->left == node) {
            node->parent->left = l_son;
        }
        else {
            node->parent->right = l_son;
        }

        l_son->right = node;
        node->parent = l_son;
    }

    void insertFixup(Node* target) {
        while (target->parent != nil && target->parent->color == colour::RED) {//父亲红，爷爷黑
            if (target->parent->parent->left == target->parent) {//父亲是左节点
                Node* uncle = target->parent->parent->right;
                if (uncle != nil && uncle->color == colour::RED) {//叔叔红
                    target->parent->color = colour::BLACK;
                    uncle->color = colour::BLACK;
                    target->parent->parent->color = colour::RED;
                    target = target->parent->parent;
                }
                else {//叔叔黑
                    if (target == target->parent->right) {
                        target = target->parent;
                        leftRotate(target);
                    }
                    target->parent->color = colour::BLACK;
                    target->parent->parent->color = colour::RED;
                    rightRotate(target->parent->parent);
                }
            }
            else {//父亲是右节点
                Node* uncle = target->parent->parent->left;
                if (uncle != nil && uncle->color == colour::RED) {//叔叔红
                    target->parent->color = colour::BLACK;
                    uncle->color = colour::BLACK;
                    target->parent->parent->color = colour::RED;
                    target = target->parent->parent;
                }
                else {
                    if (target == target->parent->left) {//叔叔黑
                        target = target->parent;
                        rightRotate(target);
                    }
                    target->parent->color = colour::BLACK;
                    target->parent->parent->color = colour::RED;
                    leftRotate(target->parent->parent);
                }
            }
        }
        root->color = colour::BLACK;
    }

    void insertNode(const KEY& key, const VALUE& value) {
        Node* newNode = new Node(key, value, colour::RED);
        newNode->left = nil;
        newNode->right = nil;

        Node* cmpNode = root;
        Node* parent = nil;

        while (cmpNode != nil) {
            parent = cmpNode;
            if (key > cmpNode->key) {
                cmpNode = cmpNode->right;
            }
            else if (key < cmpNode->key) {
                cmpNode = cmpNode->left;
            }
            else {
                delete newNode;
                return;
            }
        }

        if (parent == nil) {
            root = newNode;
        }
        else if (key < parent->key) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }

        newNode->parent = parent;
        ++size;

        insertFixup(newNode);
    }

    void inorderTraversal(Node* node) const {//中序遍历
        if (node != nil) {
            inorderTraversal(node->left);
            std::cout << node->key << " " << node->value << " ";
            inorderTraversal(node->right);
        }
    }

    void replaceNode(Node* targetNode, Node* newNode) {
        if (targetNode == nil) {
            return;
        }
        if (targetNode->parent == nil) {
            root = newNode;
        }
        else if (targetNode == targetNode->parent->left) {
            targetNode->parent->left = newNode;
        }
        else {
            targetNode->parent->right = newNode;
        }

        if (newNode != nil) {
            newNode->parent = targetNode->parent;
        }
    }

    Node* findminimumNode(Node* node) {
        while (node->left != nil) {
            node = node->left;
        }
        return node;
    }

    void removeFixup(Node* node) {
        while (node != root && node->color == colour::BLACK) {
            if (node == node->parent->left) {
                Node* sibling = node->parent->right;
                if (getcolor(sibling) == colour::RED) {//兄弟红
                    setcolour(sibling, colour::BLACK);//父兄变色，向双黑旋转
                    setcolour(node->parent, colour::RED);
                    leftRotate(node->parent);
                    sibling = node->parent->right;//新兄弟（原兄弟子）一定为黑
                }
                //下面为兄弟黑的两种情况（有红孩儿和没有红孩儿）
                if (getcolor(sibling->left) == colour::BLACK && getcolor(sibling->right) == colour::BLACK) {//两黑孩
                    setcolour(sibling, colour::RED);
                    node = node->parent;//双黑上移
                    if (getcolor(node) == colour::RED) {
                        setcolour(node, colour::BLACK);
                        node = root;
                    }
                }
                else {//兄弟有红孩儿
                    if (getcolor(sibling->right) == colour::BLACK) {//RL转RR
                        setcolour(sibling->left, colour::BLACK);
                        setcolour(sibling, colour::RED);
                        rightRotate(sibling);
                        sibling = node->parent->right;
                    }
                    //RR，兄弟右孩子是红孩儿
                    setcolour(sibling, getcolor(node->parent));//parent颜色
                    setcolour(node->parent, colour::BLACK);
                    setcolour(sibling->right, colour::BLACK);//sibling颜色
                    leftRotate(node->parent);
                    node = root;
                }
            }
            else {
                Node* sibling = node->parent->left;
                if (getcolor(sibling) == colour::RED) {
                    setcolour(sibling, colour::BLACK);
                    setcolour(node->parent, colour::RED);
                    rightRotate(node->parent);
                    sibling = node->parent->left;
                }
                if (getcolor(sibling->left) == colour::BLACK && getcolor(sibling->right) == colour::BLACK) {
                    setcolour(sibling, colour::RED);
                    node = node->parent;
                    if (getcolor(node) == colour::RED) {
                        setcolour(node, colour::BLACK);
                        node = root;
                    }
                }
                else {
                    if (getcolor(sibling->left) == colour::BLACK) {
                        setcolour(sibling->right, colour::BLACK);
                        setcolour(sibling, colour::RED);
                        leftRotate(sibling);
                        sibling = node->parent->left;
                    }
                    setcolour(sibling, getcolor(node->parent));
                    setcolour(node->parent, colour::BLACK);
                    setcolour(sibling->left, colour::BLACK);
                    rightRotate(node->parent);
                    node = root;
                }
            }
        }
        setcolour(node, colour::BLACK);
    }

    colour getcolor(Node* node) {
        return node->color;
    }

    void setcolour(Node* node, colour color) {
        node->color = color;
    }

    void deleteNode(Node* del) {
        Node* rep = del;
        Node* child = nil;
        colour original = del->color;

        if (del->left == nil) {
            child = del->right;
            replaceNode(del, del->right);
        }
        else if (del->right == nil) {
            child = del->left;
            replaceNode(del, del->left);
        }
        else {
            rep = findminimumNode(del->right);
            original = rep->color;
            child = rep->right;

            if (rep != del->right) {
                replaceNode(rep, rep->right);
                rep->right = del->right;
                rep->right->parent = rep;
            }
            else {
                child->parent = rep; // 确保child的父指针正确
            }

            replaceNode(del, rep);
            rep->left = del->left;
            rep->left->parent = rep;
            rep->color = del->color;
        }

        if (original == colour::BLACK) {
            removeFixup(child);
        }

        delete del;
        --size;
    }
public:
    RedBlackTree() :size(0) {
        nil = new Node();
        nil->parent = nil;
        nil->left = nil;
        nil->right = nil;
        root = nil;
    }

    void insert(const KEY& key, const VALUE& value) {
        insertNode(key, value);
    }

    void remove(const KEY& key) {
        Node* nodeToBeRemoved = find(key);
        if (nodeToBeRemoved != nil) {
            deleteNode(nodeToBeRemoved);
        }
    }

    VALUE* at(const KEY& key) {
        Node* ans = find(key);
        if (ans != nil) {
            return &ans->value;
        }
        return nullptr;
    }

    size_t getsize() {
        return size;
    }

    bool empty() {
        return size == 0;
    }

    void print() {
        if (size == 0) {
            std::cout << "empty" << std::endl;
        }
        else {
            inorderTraversal(root);
            std::cout << std::endl;
        }
    }

    void clear() {
        deleteTree(root);
        root = nil;
        size = 0;
    }

    ~RedBlackTree() {
        deleteTree(root);
        delete nil;
    }
private:
    void deleteTree(Node* node) {
        if (node != nil) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
};

int main(int argc, char* argv[])
{
    int N;
    std::cin >> N;
    getchar();

    std::string line;
    RedBlackTree<int, int> gaogao;

    while (N--) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        int key, value;
        if (command == "insert") {
            iss >> key >> value;
            gaogao.insert(key, value);
        }
        else if (command == "remove") {
            iss >> key;
            gaogao.remove(key);
        }
        else if (command == "at") {
            iss >> key;
            int* res = gaogao.at(key);
            if (res == nullptr) {
                std::cout << "not exist" << std::endl;
            }
            else {
                std::cout << *res << std::endl;
            }
        }
        else if (command == "size") {
            std::cout << gaogao.getsize() << std::endl;
        }
        else if (command == "print") {
            gaogao.print();
        }
    }

    return 0;
}