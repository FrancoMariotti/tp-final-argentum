//
// Created by agustin on 8/5/20.
//

#ifndef TP2CLION_BLOCKING_QUEUE_H
#define TP2CLION_BLOCKING_QUEUE_H

#include <mutex>
#include <queue>
#include <condition_variable>

class ClosedQueueException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Queue is Closed";
    }
};

template <class T>
class BlockingQueue {
    private:
        std::mutex m;
        std::queue<T> queue;
        std::condition_variable cond_var;
        bool is_close;

    public:
        BlockingQueue() : is_close(false){};

        BlockingQueue(const BlockingQueue& other) = delete;

        /*Agrega @param element a la queue y notifica a todos los hilos*/
        void push(T element){
            std::unique_lock<std::mutex> lock(m);
            this->queue.push(element);
            cond_var.notify_all();
        }

        /*Remueve y devuelve el primer elemento de la queue
         * Si la queue esta vacia, pone en espera al hilo*/
        T pop(){
            std::unique_lock<std::mutex> lock(m);
            while (queue.empty()){
                if (this->is_close){
                    throw ClosedQueueException();
                }
                cond_var.wait(lock);
            }
            T element = queue.front();
            queue.pop();
            return element;

        }

        /*is_close pasa a ser false y notifica a todos los hilos*/
        void close(){
            std::unique_lock<std::mutex> lock(m);
            this->is_close = true;
            this->cond_var.notify_all();

        }

        ~BlockingQueue() = default;
};



#endif //TP2CLION_BLOCKING_QUEUE_H
