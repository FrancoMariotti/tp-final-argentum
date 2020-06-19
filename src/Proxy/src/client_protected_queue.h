//
// Created by agustin on 19/6/20.
//

#ifndef ARGENTUM_CLIENT_PROTECTED_QUEUE_H
#define ARGENTUM_CLIENT_PROTECTED_QUEUE_H


#include <mutex>
#include <queue>

template <class T>
class ProtectedQueue {
private:
    std::mutex m;
    std::queue<T> queue;
    bool is_close;

public:
    ProtectedQueue() : is_close(false){};

    ProtectedQueue(const ProtectedQueue& other) = delete;

    void push(T element){
        std::unique_lock<std::mutex> lock(m);
        this->queue.push(element);
    }

    /*Remueve y devuelve el primer elemento de la queue
     * Si la queue esta vacia, DEVUELVE BASURA */
    T popIfHasAnElement(){
        std::unique_lock<std::mutex> lock(m);
        T element;
        if(!queue.empty()){
            element = queue.front();
            queue.pop();
        }
        return element;
    }

    void close(){
        std::unique_lock<std::mutex> lock(m);
        this->is_close = true;
    }

    ~ProtectedQueue() = default;

};


#endif //ARGENTUM_CLIENT_PROTECTED_QUEUE_H
