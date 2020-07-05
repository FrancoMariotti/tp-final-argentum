//
// Created by agustin on 25/5/20.
//

#ifndef TP3CLION_SERVER_THREAD_H
#define TP3CLION_SERVER_THREAD_H


#include <thread>

class Thread {
private:
    std::thread thread;
protected:
    bool finished;
public:
    Thread();
    virtual void start();
    void join();
    virtual void run() = 0;
    virtual ~Thread();
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
    Thread(Thread&& other) noexcept;
    Thread& operator=(Thread&& other) noexcept;

    bool isDead() const;
};



#endif //TP3CLION_SERVER_THREAD_H
