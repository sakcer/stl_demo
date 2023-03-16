#include "hash_fun.hpp"
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace myHash {

template <typename K, typename V>
class HashNode {
  public:
    K               _key;
    V               _val;
    HashNode<K, V>* _next;

    HashNode(K key, V val)
        : _key(key), _val(val), _next(NULL) {}
};

template <typename K, typename V>
class HashMap {
  public:
    std::vector<HashNode<K, V>*> _hashmap;
    int                          _size;

    HashMap() {}

    HashMap(int size)
        : _size(size) {
        _hashmap.resize(size);
        for (int i = 0; i < size; i++) {
            _hashmap[i] = new HashNode<K, V>(*new K, *new V);
        }
    }

    bool insert(K key, V val) {
        HashFun hash_fn;
        size_t  idx = hash_fn(key) % _size;

        auto iterator = _hashmap[idx];
        while (iterator->_next) {
            iterator = iterator->_next;
        }
        iterator->_next = new HashNode<K, V>(key, val);
        return true;
    }

    V find(K key) {
        HashFun hash_fn;
        size_t  idx = hash_fn(key) % _size;

        auto iterator = _hashmap[idx];
        while (iterator->_next) {
            if (iterator->_next->_key == key) {
                return iterator->_next->_val;
            }
            iterator = iterator->_next;
        }
        return {};
    }
};
}  // namespace myHash

using namespace myHash;
using namespace std;
int main() {
    cout << "init" << endl;
    HashMap<string, string> map(1);

    std::hash<char*> f;

    HashFun fun;

    cout << fun.operator()<string>("key") << endl;
    if (!map.insert("key", "val")) {
        cout << "ERROR" << endl;
        return -1;
    }

    cout << map.find("key") << endl;
    if (!map.insert("hello", "who")) {
        cout << "ERROR" << endl;
        return -1;
    }
    cout << map.find("key") << endl;
    cout << map.find("hello") << endl;
}

// dev