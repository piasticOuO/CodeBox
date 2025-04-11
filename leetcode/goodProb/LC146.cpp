#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key, value;
    std::shared_ptr<Node> nxt, prv;
    Node(int key = 0, int value = 0) : key(key), value(value), nxt(nullptr), prv(nullptr) {}
};

class LRUList {
private:
    std::shared_ptr<Node> head, tail;
    std::unordered_map<int, std::shared_ptr<Node>> hashtable;
public:
    LRUList() : head(nullptr), tail(nullptr) {}
    void push_back(int key,int value) {
        std::shared_ptr<Node> node = std::make_shared<Node>(key, value);
        node->nxt = tail;
        if (tail != nullptr) tail->prv = node;
        tail = node;
        if (head == nullptr) head = node;
        hashtable[key] = node;
    }
    void remove(int key) {
        auto it = hashtable.find(key);
        assert(it != hashtable.end());
        std::shared_ptr<Node> node = it -> second;
        if (node->nxt != nullptr) {
            node->nxt->prv = node->prv;
        }
        if (node->prv != nullptr) {
            node->prv->nxt = node->nxt;
        }
        if (head == node) {
            head = node->prv;
        }
        if (tail == node) {
            tail = node->nxt;
        }
        hashtable.erase(it);
    }
    int get(int key) {
        auto it = hashtable.find(key);
        if (it == hashtable.end()) return -1;
        return it -> second -> value;
    }
    int size() const {
        return hashtable.size();
    }
    void pop_front() {
        remove(head->key);
    }
};

class LRUCache {
public:
    LRUCache(int capacity) : capacity (capacity) {}
    
    int get(int key) {
        int value = list.get(key);
        if (value != -1) {
            list.remove(key);
            list.push_back(key, value);
        }
        return value;
    }
    
    void put(int key, int value) {
        int value_ = list.get(key);
        if (value_ != -1) {
            list.remove(key);
        }
        list.push_back(key, value);
        if (list.size() > capacity) {
            list.pop_front();
        }
    }
public:
    LRUList list;
    int capacity;
};
    
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
