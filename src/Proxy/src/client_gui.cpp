//
// Created by agustin on 24/6/20.
//

#include "client_gui.h"

#define FONT_SIZE 14

GUI::GUI(const int screen_width, const int screen_height, BlockingQueue<std::unique_ptr<Message>>& clientEvents) :
    window(screen_width, screen_height),
    font(TTF_OpenFont("../../Proxy/assets/nakula.ttf", FONT_SIZE)),
    player(screen_width / 2,screen_height / 2,window),
    inventory(screen_width, screen_height, window, player),
    camera(screen_width, screen_height, player),
    console(screen_width, screen_height, window, font, player),
    world(window),
    clientEvents(clientEvents)
    {}

void GUI::handleEvents(SDL_Event &event){
    player.handleEvent(event);
    console.handleEvents(event);
    inventory.handleEvents(event);
}

void GUI::execute(){
    player.move(clientEvents);
    inventory.use(clientEvents);
    console.execute(clientEvents);
    camera.move();
}

void GUI::update(const int player_vel_x,const int player_vel_y){
    player.update(player_vel_x, player_vel_y);
}

void GUI::addTile(int x, int y, const std::string &id) {
    world.add(x, y, id);
}

void GUI::addItem(const std::string &id) {
    inventory.addItem(id);
}

void GUI::render(){
    //Limpio pantalla
    window.fill(0xFF, 0xFF, 0xFF, 0xFF);

    //Render objects
    world.render(camera);
    player.render(camera);
    inventory.render();
    console.render();

    //Update screen
    window.render();
}

GUI::~GUI(){
    if(font){
        TTF_CloseFont(font);
    }
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}
