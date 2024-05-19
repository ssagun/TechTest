#include <iostream>
#include <unordered_map>
#include <list>
#include <chrono>
#include <ctime>
#include <thread>
#include <variant>
#include <string>

using namespace std;

template <typename Key>
class LRUCache {
private:
    using Value = std::variant<int, double, string>;

    struct CacheEntry {
        Value value;
        typename list<Key>::iterator position;
        chrono::time_point<chrono::system_clock> timestamp;

        CacheEntry() = default;

        CacheEntry(const Value& val, const chrono::time_point<chrono::system_clock>& time)
            : value(val), timestamp(time) {}
    };

    size_t capacity;
    unordered_map<Key, CacheEntry> cache;
    list<Key> lruList;
    chrono::duration<double> expirationTime;

public:
    LRUCache(size_t cap, double expTime) : capacity(cap), expirationTime(expTime) {}

    void put(const Key& key, const Value& value) {
        if (cache.find(key) != cache.end()) {
            lruList.erase(cache[key].position);
        } else if (cache.size() == capacity) {
            auto lruKey = lruList.back();
            cache.erase(lruKey);
            lruList.pop_back();
        }

        lruList.push_front(key);
        cache[key] = CacheEntry(value, chrono::system_clock::now());
        cache[key].position = lruList.begin();
    }

    Value get(const Key& key) {
        if (cache.find(key) == cache.end()) {
            throw out_of_range("Key not found in cache");
        }

        auto& entry = cache[key];
        lruList.erase(entry.position);
        lruList.push_front(key);
        entry.position = lruList.begin();

        return entry.value;
    }

    void cleanExpiredEntries() {
        while (true) {
            this_thread::sleep_for(chrono::seconds(1)); // Check expiration every 1 second
            auto currentTime = chrono::system_clock::now();
            for (auto it = cache.begin(); it != cache.end();) {
                if ((currentTime - it->second.timestamp) > expirationTime) {
                    lruList.erase(it->second.position);
                    it = cache.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }

    static void printValue(const Value& value) {
        // Use std::visit to handle the variant type
        std::visit([](auto&& arg) { std::cout << arg; }, value);
    }

    void printCacheState() {
        cout << "Current cache state: " << endl;
        for (const auto& key : lruList) {
            cout << "[" << key << ": ";
            printValue(cache[key].value);
            cout << "] ";
        }
        cout << endl;
    }
};

int main() {
    LRUCache<int> cache(3, 5); // Cache with capacity of 3 and expiration time of 5 seconds

    // Start a thread to clean expired entries
    thread cleanupThread(&LRUCache<int>::cleanExpiredEntries, &cache);

    // Adding initial values
    cout << "Adding initial values to cache" << endl;
    cache.put(1, 100); // Storing an int
    cache.put(2, 200.5); // Storing a double
    cache.put(3, "Value3"); // Storing a string
    cache.printCacheState();

    // Accessing some values to update their positions
    try {
        cout << "Accessing key 1 to update its position" << endl;
        cache.get(1);
        cache.printCacheState();
    } catch (const out_of_range& e) {
        cout << "Key not found in cache" << endl;
    }

    // Waiting for 6 seconds to let some entries expire
    cout << "Waiting for 6 seconds to let some entries expire" << endl;
    this_thread::sleep_for(chrono::seconds(6));

    // Checking cache state after expiration
    cout << "Cache state after expiration" << endl;
    cache.printCacheState();

    // Adding new values to test LRU eviction
    cout << "Adding new values to test LRU eviction" << endl;
    cache.put(4, "NewValue1");
    cache.put(5, 500);
    cache.printCacheState();

    // Accessing new values
    try {
        cout << "Accessing key 4: ";
        auto value = cache.get(4);
        LRUCache<int>::printValue(value);
    } catch (const out_of_range& e) {
        cout << "Key not found in cache" << endl;
    }

    // Adding more values to test eviction
    cache.put(6, 500);
    cache.put(7, "FinalValue");

    // Checking cache state after adding new values
    cout << "Final cache state" << endl;
    cache.printCacheState();

    // Keep the main thread alive
    cleanupThread.join();

    return 0;
}
