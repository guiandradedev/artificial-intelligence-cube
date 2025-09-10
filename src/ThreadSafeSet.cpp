#include <unordered_set>
#include <mutex>
#include <memory>
#include <vector>

template <typename T>
class ThreadSafeSet{
private:
    std::unordered_set<T> set;
    mutable std::mutex mutex;

public:
    bool insert(const T& value){
        std::lock_guard<std::mutex> lock(mutex);
        auto result = set.insert(value);
        return result.second; // true if the value was inserted, false if it was already present
    }

    void erase(const T& value){
        std::lock_guard<std::mutex> lock(mutex);
        set.erase(value);
    }
};


template<typename T>
class ThreadSafeVector {
private:
    std::vector<T> vec;
    std::mutex mtx;
public:
    void push_back(T item) {
        std::lock_guard<std::mutex> lock(mtx);
        vec.push_back(item);
    }

    std::vector<T> to_vector() {
        std::lock_guard<std::mutex> lock(mtx);
        return vec;
    }

    void clear() {
        std::lock_guard<std::mutex> lock(mtx);
        vec.clear();
    }
};