//
// Created by agustin on 24/6/20.
//

#include "client_gui.h"

#include <utility>
#include "client_sdl_exception.h"
#include "client_sdl_dynamic_renderable.h"

#define FONT_SIZE 14

GUI::GUI(const int screen_width, const int screen_height, BlockingQueue<std::unique_ptr<Message>>& clientEvents) :
    window(screen_width, screen_height),
    font(TTF_OpenFont("../../Proxy/assets/nakula.ttf", FONT_SIZE)),
    player(32, 64, window),
    inventory(screen_width, screen_height, window, player),
    camera(screen_width, screen_height, player),
    console(screen_width, screen_height, window, font, player),
    world(window),
    clientEvents(clientEvents) {
    if(!font){
        throw SdlException("Could not open font", TTF_GetError());
    }
    this->dynamic_renderables_textures.emplace(std::make_pair("arania",
            SdlTexture(54, 34, "../../Proxy/assets/4093.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("esqueleto",
            SdlTexture(26, 54, "../../Proxy/assets/4080.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("zombie",
            SdlTexture(24, 46, "../../Proxy/assets/4070.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("goblin",
            SdlTexture(24, 36, "../../Proxy/assets/4082.png", window)));

}

void GUI::handleEvents(SDL_Event &event){
    bool is_event_handled = false;
    player.handleEvent(event, is_event_handled);
    console.handleEvent(event, is_event_handled);
    inventory.handleEvents(event, is_event_handled);
}

void GUI::execute(){
    player.move(clientEvents);
    inventory.use(clientEvents);
    console.execute(clientEvents);
    camera.move();
}
/**Factory de eventos de server??*/
void GUI::update(const int player_vel_x,const int player_vel_y){
    player.update(player_vel_y, player_vel_x, camera);
}

void GUI::update(const int vel_x,const int vel_y, const std::string& renderable_id){
    this->dynamic_renderables.at(renderable_id).update(vel_x, vel_y, camera);
}

void GUI::update(std::vector<std::string> player_inventory) {
    inventory.update(std::move(player_inventory));
}

void GUI::addTile(int x, int y, int tile_id) {
    world.add(x, y, tile_id);
}

void GUI::addRenderable(const int x, const int y, const std::string& renderable_id){
    if(renderable_id.find("arania") != std::string::npos){
        dynamic_renderables.emplace(std::make_pair(renderable_id,
                             SdlDynamicRenderable(x , y,
                             dynamic_renderables_textures.at("arania"))));
    } else if (renderable_id.find("esqueleto") != std::string::npos){
        dynamic_renderables.emplace(std::make_pair(renderable_id,
                                   SdlDynamicRenderable(x , y,
                                    dynamic_renderables_textures.at("esqueleto"))));
    } else if (renderable_id.find("zombie") != std::string::npos){
        dynamic_renderables.emplace(std::make_pair(renderable_id,
                                   SdlDynamicRenderable(x , y,
                                    dynamic_renderables_textures.at("zombie"))));
    } else if (renderable_id.find("goblin") != std::string::npos){
        dynamic_renderables.emplace(std::make_pair(renderable_id,
                                   SdlDynamicRenderable(x , y,
                                    dynamic_renderables_textures.at("goblin"))));
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
