//
// Created by agustin on 20/6/20.
//

#include "ClosedQueueException.h"
const char *ClosedQueueException::what() const noexcept {
    return "Queue is Closed";
}
