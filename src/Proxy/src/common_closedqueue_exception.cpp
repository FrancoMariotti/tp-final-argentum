//
// Created by agustin on 20/6/20.
//

#include "common_closedqueue_exception.h"
const char *ClosedQueueException::what() const noexcept {
    return "Queue is Closed";
}
