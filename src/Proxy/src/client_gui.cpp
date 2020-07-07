//
// Created by agustin on 24/6/20.
//

#include "client_gui.h"

#include <utility>
#include <SDL2/SDL_mixer.h>
#include "client_sdl_exception.h"
#include "client_sdl_dynamic_renderable.h"
#include "common_message_structs.h"

#define FONT_SIZE 14

GUI::GUI(const int screen_width, const int screen_height, BlockingQueue<std::unique_ptr<Message>>& clientEvents) :
    window(screen_width, screen_height),
    font(TTF_OpenFont("../../Proxy/assets/nakula.ttf", FONT_SIZE)),
    timer(),
    audioManager(),
    textureManager(window),
    interface(screen_width, screen_height, "../../Proxy/interfaces/VentanaPrincipal.jpg",window),
    player(0, 0, textureManager, "franco", font, window, audioManager),
    inventory(screen_width, screen_height, window, font),
    camera(screen_width, screen_height, player),
    mouse(camera),
    keyboard(),
    console(screen_width, screen_height, window, font),
    world(window),
    playerStats(screen_width, screen_height, window, font),
    clientEvents(clientEvents),
    eventMediator(clientEvents, player, mouse){
    if(!font){
        throw SdlException("Could not open font", TTF_GetError());
    }
    audioManager.playMainMenuMusic(-1);
}

void GUI::setWorldDimensions(int w, int h) {
    world.setDimensions(w,h);
}

void GUI::addWorldLayer(std::vector<int> data, const int init) {
    this->world.addLayer(std::move(data), init);
}


void GUI::handleEvents(SDL_Event &event){
    bool is_event_handled = false;
    keyboard.handleEvent(event, is_event_handled);
    console.handleEvent(event, is_event_handled);
    inventory.handleEvent(event, is_event_handled);
    mouse.handleEvent(event,is_event_handled);
}

void GUI::execute(){
    keyboard.movePlayer(clientEvents);
    console.execute(clientEvents, mouse, camera, player);
    inventory.use(clientEvents, mouse);
    mouse.use(clientEvents);
    camera.move();

    timer.incrementFrames();
    audioManager.playRandomAmbientSound(10000);
}

/**Factory de eventos de server??*/
void GUI::updatePlayerPos(const int player_x, const int player_y){
    player.updatePos(player_x, player_y, camera);
    audioManager.playSound("step1",0);
}

void GUI::updatePlayerStats(t_stats new_stats) {
    playerStats.update(new_stats);
}

/*Busca en la lista de renderizables dinamicos por id (username o npc_id)*/
void GUI::updateRenderableStats(std::string renderable_id, std::string effect_id) {
    //if(rednerable_id == this->username
    player.updateStats(effect_id);
    //else
    //dynamic_renderables.at(renderable_id)->updateStats(effect_id);
}

void GUI::updatePlayerEquipment(const equipment_t& equipment) {
    player.updateEquipment(equipment);
    inventory.updateEquippedItems(equipment);
    if(equipment.armourName == "ghost"){
        audioManager.playSound("death", 0);
    } else {
        audioManager.playSound("equip", 0);
    }
}

void GUI::updateInventory(std::vector<std::string> player_inventory) {
    inventory.update(std::move(player_inventory), eventMediator);
}

void GUI::initStaticRenderables(const std::vector<spawn_character_t>& renderables){
    for(auto it = renderables.begin(); it != renderables.end(); it++){
        static_renderables.push_back(std::unique_ptr<SdlDynamicRenderable>
                (new SdlRenderableNPC(camera.toPixels(it->x),
                                      camera.toPixels(it->y),
                                      textureManager, it->id, font,
                                      window, audioManager)));
    }
}

/*Itera @param renderables y busca el id de textura que corresponde con el id del renderizable y lo agrega al map
 * con key: id y value: puntero a SdlDynamicRenderable*/
void GUI::updateRenderables(std::vector<spawn_character_t> renderables){
    dynamic_renderables.clear();
    auto it = renderables.begin();
    for (; it != renderables.end(); it++) {
        std::string texture_id = textureManager.findTextureId(it->id);
        if (texture_id != "player"){
            dynamic_renderables[it->id] = std::unique_ptr <SdlDynamicRenderable>
                    (new SdlRenderableNPC(camera.toPixels(it->x),
                            camera.toPixels(it->y), textureManager,
                            texture_id, font, window, audioManager));
        }
    }
}

void GUI::updateRenderablePos(const int new_x, const int new_y, const std::string& renderable_id){
    this->dynamic_renderables.at(renderable_id)->updatePos(new_x, new_y, camera);
}

void GUI::updateRenderablePlayableEquipment(const equipment_t& equipment,
                                            const std::string& renderable_id) {
    this->dynamic_renderables.at(renderable_id)->updateEquipment(equipment);
}


void GUI::updateDrops(const std::vector<spawn_character_t> &drops) {
    world.updateDrops(drops);
}

void GUI::updateConsoleOutput(std::vector<std::string> console_outputs) {
    console.updateOutput(std::move(console_outputs), audioManager);
}

void GUI::render(){
    //Limpio pantalla
    window.fill(0xFF, 0xFF, 0xFF, 0xFF);

    renderWorld();
    //renderizo estaticos
    auto iterator = static_renderables.begin();
    while(iterator != static_renderables.end()){
        (*iterator)->render(camera);
        iterator++;
    }
    //Renderizo dinamicos
    auto it = dynamic_renderables.begin();
    while(it != dynamic_renderables.end()){
        it->second->render(camera);
        it++;
    }
    player.render(camera);
    inventory.render();
    console.render();
    //interface.render(0,0);
    playerStats.render();

    //Update screen
    window.render();

}

void GUI::renderWorld() {
    world.render(camera);
    world.renderDrops(inventory, camera);
}

GUI::~GUI(){
    if(font){
        TTF_CloseFont(font);
    }
    //Quit SDL subsystems
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


