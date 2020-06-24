//
// Created by agustin on 24/6/20.
//

#include "client_gui.h"
#include "client_sdl_exception.h"
#include "client_sdl_dynamic_renderable.h"

#define FONT_SIZE 14

GUI::GUI(const int screen_width, const int screen_height, BlockingQueue<std::unique_ptr<Message>>& clientEvents) :
    window(screen_width, screen_height),
    font(TTF_OpenFont("../../Proxy/assets/nakula.ttf", FONT_SIZE)),
    player(screen_width / 2,screen_height / 2,window),
    inventory(screen_width, screen_height, window, player),
    camera(screen_width, screen_height, player),
    console(screen_width, screen_height, window, font, player),
    world(window),
    clientEvents(clientEvents) {
    if(!font){
        throw SdlException("Could not open font", TTF_GetError());
    }
}

void GUI::handleEvents(SDL_Event &event){
    //bool event_handled = false;
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
    player.update(player_vel_y, player_vel_x, camera);
}

void GUI::update(const int vel_x,const int vel_y, const std::string& renderable_id){
    this->dynamic_renderables.at(renderable_id).update(vel_x, vel_y, camera);
}

void GUI::addTile(int x, int y, const std::string &tile_id) {
    world.add(x, y, tile_id);
}

void GUI::addRenderable(const int x, const int y, const std::string& renderable_id){
    if(renderable_id.find("arania") != std::string::npos){
        std::string texture_id = "4093";
        int width = 54;
        int height = 34;
        this->dynamic_renderables.emplace(std::make_pair(renderable_id,
                SdlDynamicRenderable(x, y, width, height, texture_id, window)));
    } else if (renderable_id.find("esqueleto") != std::string::npos) {
        std::string texture_id = "4080";
        int width = 26;
        int height = 54;
        this->dynamic_renderables.emplace(std::make_pair(renderable_id,
                 SdlDynamicRenderable(x, y, width, height, texture_id, window)));
    } else if (renderable_id.find("zombie") != std::string::npos) {
        std::string texture_id = "4070";
        int width = 24;
        int height = 46;
        this->dynamic_renderables.emplace(std::make_pair(renderable_id,
                 SdlDynamicRenderable(x, y, width, height, texture_id, window)));
    } else if (renderable_id.find("goblin") != std::string::npos) {
        std::string texture_id = "4082";
        int width = 24;
        int height = 40;
        this->dynamic_renderables.emplace(std::make_pair(renderable_id,
                SdlDynamicRenderable(x, y, width, height, texture_id, window)));
    }
}

void GUI::addItem(const std::string &item_id) {
    inventory.addItem(item_id);
}

void GUI::render(){
    //Limpio pantalla
    window.fill(0xFF, 0xFF, 0xFF, 0xFF);

    //Render objects
    world.render(camera);
    player.render(camera);
    inventory.render();
    console.render();

    //Renderizo dinamicos
    std::map<std::string, SdlDynamicRenderable>::iterator iterator = dynamic_renderables.begin();
    while(iterator != dynamic_renderables.end()){
        iterator->second.render(camera);
        iterator++;
    }

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
