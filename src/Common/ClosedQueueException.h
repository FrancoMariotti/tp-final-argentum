//
// Created by agustin on 20/6/20.
//

#ifndef ARGENTUM_CLOSEDQUEUEEXCEPTION_H
#define ARGENTUM_CLOSEDQUEUEEXCEPTION_H


#include <exception>

class ClosedQueueException : public std::exception {
public:
    const char* what() const noexcept override;

};


#endif //ARGENTUM_CLOSEDQUEUEEXCEPTION_H
