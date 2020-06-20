//
// Created by agustin on 20/6/20.
//

#ifndef ARGENTUM_COMMON_CLOSEDQUEUE_EXCEPTION_H
#define ARGENTUM_COMMON_CLOSEDQUEUE_EXCEPTION_H


#include <exception>

class ClosedQueueException : public std::exception {
public:
    const char* what() const noexcept override;

};


#endif //ARGENTUM_COMMON_CLOSEDQUEUE_EXCEPTION_H
