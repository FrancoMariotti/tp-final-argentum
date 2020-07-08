#include "client_command.h"
#include "common_message.h"

void UseItemCommand::operator()(BlockingQueue<std::unique_ptr<Message>>& clientEvents, int i) {
    clientEvents.push(std::unique_ptr<Message> (
            new UseItem(i)));
}
