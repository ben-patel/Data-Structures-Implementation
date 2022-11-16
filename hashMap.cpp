class MyHashMap {
    
    std::vector<list<pair<int,int>>> map;
    double loadFactor;
    int size;
    int capacity;
    
    int hash(int key) {
        return key % capacity;
    }

    std::list<pair<int,int>>::iterator search(int key) {
        int h = hash(key);
        
        for(std::list<pair<int,int>>::iterator it = map[h].begin(); it != map[h].end(); ++it) {
            if (it->first == key) return it;
        }
      
        return map[h].end();
    }
    
    void rehash() {
        size = 0;
        capacity = max(2, capacity);
        vector<list<pair<int,int>>> old(move(map));
        map = vector<list<pair<int,int>>>(capacity);
        
        for(int i = 0; i < old.size(); i++) {
            for(auto x : old[i]) {
                put(x.first, x.second);
            }
        }
    }
    
public:
    MyHashMap() {
        capacity = 2;
        size = 0;
        loadFactor = 0.75;
        map = vector<list<pair<int,int>>>(capacity);
    }
    
    void put(int key, int value) {
        int h = hash(key);
      
        if(search(key) != map[h].end()) {
            auto it = search(key);
            it->second = value;
            return;
        }
      
        size++;
        map[h].push_back({key,value});
        
        if (size >= loadFactor * capacity) {
            capacity *= 2;
            rehash();
        }
    }
    
    int get(int key) {
        int h = hash(key);
        if (search(key) == map[h].end()) return -1;
        
        return (search(key))->second;
    }
    
    void remove(int key) {
        if (search(key) == map[hash(key)].end()) return;
        
        size--;
        int h = hash(key);
        map[h].erase(search(key));
        
    }
};
