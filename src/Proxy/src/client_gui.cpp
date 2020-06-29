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
    this->dynamic_renderables_textures.emplace(std::make_pair("spider",
            SdlTexture(54, 34, "../../Proxy/assets/spiderSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("skeleton",
            SdlTexture(26, 54, "../../Proxy/assets/skeletonSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("zombie",
            SdlTexture(24, 46, "../../Proxy/assets/zombieSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("goblin",
            SdlTexture(24, 36, "../../Proxy/assets/goblinSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("axe",
            SdlTexture(22, 48, "../../Proxy/items/sAxe.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("plate armor",
              SdlTexture(24, 46, "../../Proxy/items/sIronArmour.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("human head",
              SdlTexture(24, 46, "../../Proxy/assets/2001.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("iron helmet",
          SdlTexture(18, 18, "../../Proxy/items/ironHelmetSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("iron shield",
          SdlTexture(25, 44, "../../Proxy/items/ironShieldSprite.png", window)));

}

void GUI::handleEvents(SDL_Event &event){
    bool is_event_handled = false;
    player.handleEvent(event, is_event_handled);
    console.handleEvent(event, is_event_handled);
    inventory.handleEvent(event, is_event_handled);
    mouse.handleEvent(event,is_event_handled);
}

void GUI::execute(){
    player.move(clientEvents);
    inventory.use(clientEvents);
    console.execute(clientEvents, mouse, camera, inventory, player);
    camera.move();
}
/**Factory de eventos de server??*/
void GUI::updatePlayerPos(const int player_x, const int player_y){
    player.update(player_x, player_y, camera);
}

void GUI::updateRenderablesPos(const int new_x, const int new_y, const std::string& renderable_id){
    this->dynamic_renderables.at(renderable_id)->update(new_x, new_y, camera);
}

void GUI::updateInventory(std::vector<std::string> player_inventory) {
    inventory.update(std::move(player_inventory));
}

void GUI::updatePlayerStats(t_stats new_stats) {
    playerStats.update(new_stats);
}

void GUI::addFloorTile(int x, int y, int tile_id) {
    world.addFloorTile(x, y, tile_id);
}

void GUI::addObstacleTile(int x, int y, int tile_id) {
    world.addObstacleTile(x, y, tile_id);
}

/*Itera @param renderables y busca el id de textura que corresponde con el id del renderizable y lo agrega al map
 * con key: id y value: puntero a SdlDynamicRenderable*/
void GUI::updateRenderables(std::vector<spawn_character_t> renderables){
    dynamic_renderables.clear();
    auto it = renderables.begin();
    for(; it != renderables.end(); it++) {
        std::string texture_id = "player";
        for(auto & renderable_id : RENDERABLES_TEXTURES_ID){
            if(it->id.find(renderable_id) != std::string::npos){
                texture_id = renderable_id;
            }
        }
        if(texture_id != "player"){
            dynamic_renderables[it->id] = std::unique_ptr <SdlDynamicRenderable>
                    (new SdlDynamicRenderable(it->x ,it->y,
                            dynamic_renderables_textures.at(texture_id)));

        } else {
            dynamic_renderables.insert(std::make_pair(it->id,
                  std::unique_ptr<SdlDynamicRenderable> (new SdlPlayableCharacter(it->x , it->y,
                  dynamic_renderables_textures.at("plate armor"),
                  dynamic_renderables_textures.at("human head"),
                  dynamic_renderables_textures.at("iron helmet"),
                  dynamic_renderables_textures.at("axe"),
                  dynamic_renderables_textures.at("iron shield")))));
        }
    }
}

void GUI::render(){
    //Limpio pantalla
    window.fill(0xFF, 0xFF, 0xFF, 0xFF);

    //Render objects
    renderWorld();
    //Renderizo dinamicos
    auto iterator = dynamic_renderables.begin();
    while(iterator != dynamic_renderables.end()){
        iterator->second->render(camera);
        iterator++;
    }
    player.render(camera);
    inventory.render();
    console.render();
    playerStats.render();


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
}
