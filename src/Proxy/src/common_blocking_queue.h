//
// Created by agustin on 8/5/20.
//

#ifndef TP2CLION_BLOCKING_QUEUE_H
#define TP2CLION_BLOCKING_QUEUE_H

#include <mutex>
#include <queue>
#include <condition_variable>
#include "common_closedqueue_exception.h"

#include <iostream>

//DELETE
typedef struct t_command{
    std::string command;
    int x;
    int y;
}t_command;


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
            this->queue.push(std::move(element));
            cond_var.notify_all();
        }

        /*Remueve y devuelve el primer elemento de la queue
         * Si la queue esta vacia, pone en espera al hilo*/
        T pop(){
            std::unique_lock<std::mutex> lock(m);
            while (queue.empty()){
                if (this->is_close){
                    throw ClosedQueueException();
                    //return NULL;
                }
                cond_var.wait(lock);
            }
            T element = std::move(queue.front());
            queue.pop();
            return element;

        }

        /*is_close pasa a ser false y notifica a todos los hilos*/
        void close(){
            std::unique_lock<std::mutex> lock(m);
            this->is_close = true;
            this->cond_var.notify_all();

        }

        /*Eliminar cuando implementemos los hilos*/
        /*WARNING: NO PREGUNTAR ESTADO A UN RECURSO PROTEGIDO, CRITICAL SECTION*/
        bool isEmpty() const{
            return queue.empty();
        }

        ~BlockingQueue() = default;

    void testShow() {
        std::cout << queue.size() << std::endl;
    }
};



#endif //TP2CLION_BLOCKING_QUEUE_H
