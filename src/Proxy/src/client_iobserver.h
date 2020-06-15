//
// Created by agustin on 15/6/20.
//

#ifndef ARGENTUM_CLIENT_IOBSERVER_H
#define ARGENTUM_CLIENT_IOBSERVER_H


#include <list>

class IObserver {
public:
    virtual void update() = 0;
};

class Subject{
private:
    std::list<IObserver*> observers;
public:
    virtual void attach(IObserver* observer){
        observers.push_back(observer);
    }
    virtual void detach(IObserver* observer){
        observers.remove(observer);
    }
    virtual void notify(){
        std::list<IObserver*>::iterator iterator = observers.begin();
        while(iterator != observers.end()){
            (*iterator)->update();
        }
    }
};


#endif //ARGENTUM_CLIENT_IOBSERVER_H
