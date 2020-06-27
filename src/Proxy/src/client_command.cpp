#include <iostream>
#include "client_command.h"
#include "common_proxy_socket.h"
#include "common_message.h"

void Use::operator()(BlockingQueue<std::unique_ptr<Message>>& clientEvents, int i) {
    clientEvents.push(std::unique_ptr<Message> (
            new UseItem(i)));

}


ConsoleCommand::ConsoleCommand(const std::string command, int x, int y) :
    command(command),
    player_x(x),
    player_y(y)
    {}

void ConsoleCommand::operator()(BlockingQueue<std::unique_ptr<Message>> &clientEvents, int i) {
    std::cout << "console command" << std::endl;
    clientEvents.push(std::unique_ptr<Message> (new ExecuteCommand(command)));
}
