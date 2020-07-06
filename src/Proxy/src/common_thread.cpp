#include <utility>
#include "common_thread.h"

Thread::Thread():finished(false) {}

Thread::~Thread() = default;

void Thread::start() {
    thread = std::thread(&Thread::run, this);
}

bool Thread::isDead() const {
    return this->finished;
}

void Thread::join() {
    thread.join();
}

Thread::Thread(Thread&& other) noexcept {
    this->thread = std::move(other.thread);
}

Thread& Thread::operator=(Thread&& other) noexcept {
    this->thread = std::move(other.thread);
    return *this;
}
