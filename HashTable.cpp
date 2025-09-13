#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <algorithm>
#include <sstream>
#include <string>

template<typename KEY, typename VALUE, typename HASH = std::hash<KEY>>
class HashTable {
private:
    class HashNode {
    public:
        KEY key;
        VALUE value;

        explicit HashNode(const KEY& key) :key(key), value() {

        }

        HashNode(const KEY& key, const VALUE& value)
            :key(key), value(value) {

        }

        bool operator==(const HashNode& other) const {
            return key == other.key;
        }

        bool operator!=(const HashNode& other) const {
            return key != other.key;
        }

        bool operator==(const KEY& otherkey) const {
            return key == otherkey;
        }

        bool operator!=(const KEY& otherkey) const {
            return key != otherkey;
        }

        void print() const {
            std::cout << key << " " << value << " ";
        }
    };
private:
    using bucket = std::list<HashNode>;
    std::vector<bucket> buckets;
    HASH hashfunction;//哈希函数对象
    size_t tablesize;//哈希表大小，即桶的数量
    size_t numofelements;//哈希表中元素数量
    float maxload = 0.75;//最大负载因子

    size_t hash(const KEY& key) const {//计算键的哈希值
        if (tablesize == 0) {
            return 0;
        }
        return hashfunction(key) % tablesize;
    }

    void rehash(size_t new_size) {
        if (new_size == 0) {
            new_size = 1;
        }
        std::vector<bucket> newbuckets(new_size);
        for (bucket& bk : buckets) {
            for (auto it = bk.begin(); it != bk.end();) {
                size_t new_index = hashfunction(it->key) % new_size;
                newbuckets[new_index].splice(newbuckets[new_index].end(), bk, it++);
            }
        }
        tablesize = new_size;
        buckets = std::move(newbuckets);
    }
public:
    HashTable(size_t size = 10, const HASH& hashfunc = HASH())
        :buckets(size), hashfunction(hashfunc), tablesize(size), numofelements(0) {
        tablesize = (size == 0) ? 1 : size;
        buckets.resize(tablesize);
    }

    void insert(const KEY& key, const VALUE& value) {
        if (static_cast<float>(numofelements + 1) / tablesize > maxload) {
            if (tablesize == 0) {
                tablesize = 1;
            }
            rehash(tablesize * 2);
        }
        size_t index = hash(key);
        bucket& bk = buckets[index];
        auto it = std::find(bk.begin(), bk.end(), key);
        if (it == bk.end()) {
            bk.push_back(HashNode(key, value));
            ++numofelements;
        }
        //else{
        //    it->value=value;
        //}
    }

    void insertkey(const KEY& key) {
        insert(key, VALUE{});
    }

    void erase(const KEY& key) {
        if (tablesize == 0) {
            return;
        }
        size_t index = hash(key);
        bucket& bk = buckets[index];
        auto it = std::find(bk.begin(), bk.end(), key);
        if (it != bk.end()) {
            bk.erase(it);
            --numofelements;
        }
    }

    VALUE* find(const KEY& key) {
        if (tablesize == 0 || buckets.empty()) {
            return nullptr;
        }
        size_t index = hash(key);
        bucket& bk = buckets[index];
        auto it = std::find(bk.begin(), bk.end(), key);
        if (it != bk.end()) {
            return &it->value;
        }
        return nullptr;
    }

    const VALUE* find(const KEY& key) const {
        if (tablesize == 0 || buckets.empty()) {
            return nullptr;
        }
        size_t index = hash(key);
        bucket& bk = buckets[index];
        auto it = std::find(bk.begin(), bk.end(), key);
        if (it != bk.end()) {
            return &it->value;
        }
        return nullptr;
    }

    size_t getsize() const {
        return numofelements;
    }

    void print() {
        if (numofelements == 0) {
            std::cout << "empty" << std::endl;
            return;
        }
        for (const bucket& bk : buckets) {
            for (const HashNode& hn : bk) {
                hn.print();
            }
        }
        std::cout << std::endl;
    }

    void clear() {
        for (auto& bk : buckets) {
            bk.clear();
        }
        this->numofelements = 0;
        if (tablesize > 1) {
            rehash(1);
        }
    }
};

int main(int argc, char* argv[])
{
    HashTable<int, int> gaogao;
    int N;
    std::cin >> N;
    getchar();
    std::string line;
    std::string command;
    while (N--) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        iss >> command;

        int key, value;
        if (command == "insert") {
            iss >> key >> value;
            gaogao.insert(key, value);
        }
        else if (command == "erase") {
            iss >> key;
            gaogao.erase(key);
        }
        else if (command == "find") {
            iss >> key;
            auto res = gaogao.find(key);
            if (res == nullptr) {
                std::cout << "not exist\n";
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
        else if (command == "clear") {
            gaogao.clear();
        }
    }

    return 0;
}