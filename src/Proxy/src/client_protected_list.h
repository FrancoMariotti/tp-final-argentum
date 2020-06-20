//
// Created by agustin on 19/6/20.
//

#ifndef ARGENTUM_CLIENT_PROTECTED_LIST_H
#define ARGENTUM_CLIENT_PROTECTED_LIST_H


#include <mutex>
#include <list>

#include <iostream>
template <class T>
class ProtectedList {
private:
    std::mutex m;
    std::list<T> list;
    bool is_close;

public:
    ProtectedList() : is_close(false){};

    ProtectedList(const ProtectedList& other) = delete;

    void push(T element){
        std::unique_lock<std::mutex> lock(m);
        this->list.push_back(std::move(element));
    }

    /*Mueve tdo el contenido de @member list a una nueva lista y la devuelve*/
    std::list<T> consume(){
        std::unique_lock<std::mutex> lock(m);
        std::list<T> new_list(std::move(list));
        return std::move(new_list);
    }

    void close(){
        std::unique_lock<std::mutex> lock(m);
        this->is_close = true;
    }

    ~ProtectedList() = default;

    void testShow() {
        for(auto & msg : list){
            std::cout << msg->getId() << std::endl;
        }
        std::cout << list.size() << std::endl;
    }
};


#endif //ARGENTUM_CLIENT_PROTECTED_LIST_H
