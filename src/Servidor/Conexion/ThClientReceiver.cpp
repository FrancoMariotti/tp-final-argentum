//
// Created by franco on 5/7/20.
//

#include "ThClientReceiver.h"

ThClientReceiver::ThClientReceiver(Socket client, BlockingQueue <Message> &messages) {

}

void ThClientReceiver::start() {
    Thread::start();
}

void ThClientReceiver::run() {

}

void ThClientReceiver::stop() {

}
