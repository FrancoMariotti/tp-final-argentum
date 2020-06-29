//
// Created by agustin on 24/6/20.
//

#include "client_gui.h"

#include <utility>
#include "client_sdl_exception.h"
#include "client_sdl_dynamic_renderable.h"
#include "common_message_structs.h"

#define FONT_SIZE 14

GUI::GUI(const int screen_width, const int screen_height, BlockingQueue<std::unique_ptr<Message>>& clientEvents) :
    window(screen_width, screen_height),
    font(TTF_OpenFont("../../Proxy/assets/nakula.ttf", FONT_SIZE)),
    player(32, 64, window),
    inventory(screen_width, screen_height, window),
    camera(screen_width, screen_height, player),
    mouse(camera),
    console(screen_width, screen_height, window, font),
    world(window),
    playerStats(screen_width, screen_height, window, font),
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
    this->dynamic_renderables_textures.emplace(std::make_pair("hacha",
            SdlTexture(22, 48, "../../Proxy/items/16025.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("armadura de placas",
              SdlTexture(24, 46, "../../Proxy/items/79.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("cabeza",
              SdlTexture(24, 46, "../../Proxy/assets/2001.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("casco de hierro",
          SdlTexture(18, 18, "../../Proxy/items/18007.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("escudo de hierro",
          SdlTexture(25, 44, "../../Proxy/items/20002.png", window)));

}

void GUI::handleEvents(SDL_Event &event){
    bool is_event_handled = false;
    player.handleEvent(event, is_event_handled);
    console.handleEvent(event, is_event_handled);
    inventory.handleEvents(event, is_event_handled);
    mouse.handleEvent(event,is_event_handled);
}

void GUI::execute(){
    player.move(clientEvents);
    inventory.use(clientEvents);
    console.execute(clientEvents, mouse, camera, inventory, player);
    camera.move();
}
/**Factory de eventos de server??*/
void GUI::update(const int player_vel_x,const int player_vel_y){
    player.update(player_vel_y, player_vel_x, camera);
}

void GUI::update(const int vel_x,const int vel_y, const std::string& renderable_id){
    this->dynamic_renderables.at(renderable_id)->update(vel_x, vel_y, camera);
}

void GUI::update(std::vector<std::string> player_inventory) {
    inventory.update(std::move(player_inventory));
}

void GUI::update(t_stats new_stats) {
    playerStats.update(new_stats);
}
/*
void GUI::addTile(int x, int y, int tile_id) {
    world.add(x, y, tile_id);
}
*/

void GUI::addFloorTile(int x, int y, int tile_id) {
    world.addFloorTile(x, y, tile_id);
}

void GUI::addObstacleTile(int x, int y, int tile_id) {
    world.addObstacleTile(x, y, tile_id);
}

void GUI::addRenderable(const int x, const int y, const std::string& renderable_id){
    if(renderable_id.find("arania") != std::string::npos){
        dynamic_renderables.insert(std::make_pair(renderable_id, std::unique_ptr <SdlDynamicRenderable>
                                     (new SdlDynamicRenderable(x ,y,
                                             dynamic_renderables_textures.at("arania")))));

    } else if (renderable_id.find("esqueleto") != std::string::npos){
        dynamic_renderables.insert(std::make_pair(renderable_id,
                                   std::unique_ptr<SdlDynamicRenderable> (new SdlDynamicRenderable(x , y,
                                    dynamic_renderables_textures.at("esqueleto")))));
    } else if (renderable_id.find("zombie") != std::string::npos){
        dynamic_renderables.insert(std::make_pair(renderable_id,
                                         std::unique_ptr<SdlDynamicRenderable>
                                              (new SdlDynamicRenderable(x , y,
                                               dynamic_renderables_textures.at("zombie")))));
    } else if (renderable_id.find("goblin") != std::string::npos){
        dynamic_renderables.insert(std::make_pair(renderable_id,
                                  std::unique_ptr<SdlDynamicRenderable> (new SdlDynamicRenderable(x , y,
                                    dynamic_renderables_textures.at("goblin")))));
    } else {
        dynamic_renderables.insert(std::make_pair(renderable_id,
                                  std::unique_ptr<SdlDynamicRenderable> (new SdlPlayableCharacter(x , y,
                                      dynamic_renderables_textures.at("armadura de placas"),
                                      dynamic_renderables_textures.at("cabeza"),
                                      dynamic_renderables_textures.at("casco de hierro"),
                                      dynamic_renderables_textures.at("hacha"),
                                      dynamic_renderables_textures.at("escudo de hierro")
                                  ))));
    }
}

void GUI::addItem(const std::string &item_id) {
    inventory.addItem(item_id);
}

void GUI::render(){
    //Limpio pantalla
    window.fill(0xFF, 0xFF, 0xFF, 0xFF);

    //Render objects
    renderWorld();
    player.render(camera);
    inventory.render();
    console.render();
    playerStats.render();

    //Renderizo dinamicos
    auto iterator = dynamic_renderables.begin();
    while(iterator != dynamic_renderables.end()){
        iterator->second->render(camera);
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

void GUI::renderWorld() {
    world.renderFloor(camera);
    world.renderObstacles(camera);
    //Update Screen
    //window.render();
}
