#include <queue>
#include <mutex>
#include <memory>

template <typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue;
    mutable std::mutex mutex;

public:
    void insert(T node){
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(node);
    }

    T remove(){
        std::lock_guard<std::mutex> lock(mutex);
        if(queue.empty()){
            return nullptr; // or throw an exception
        }
        T node = queue.front();
        queue.pop();
        return node;
    }

    bool try_remove(T& node){
        std::lock_guard<std::mutex> lock(mutex);
        if(queue.empty()){
            return false;
        }
        node = queue.front();
        queue.pop();
        return true;
    }

    bool isEmpty() const {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }
};