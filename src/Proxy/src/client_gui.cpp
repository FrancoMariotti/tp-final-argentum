//
// Created by agustin on 24/6/20.
//

#include "client_gui.h"

#include <utility>
#include <SDL2/SDL_mixer.h>
#include <Common/OsException.h>
#include "client_sdl_exception.h"
#include "client_sdl_dynamic_renderable.h"
#include "Common/Messages/message_structs.h"

#define FONT_SIZE 14

GUI::GUI(const int screen_width, const int screen_height, BlockingQueue<std::unique_ptr<Message>>& clientEvents) :
    window(screen_width, screen_height),
    font(TTF_OpenFont("../../Proxy/assets/nakula.ttf", FONT_SIZE)),
    audioManager(),
    textureManager(window),
    interface(screen_width, screen_height, "../../Proxy/interfaces/VentanaPrincipal.jpg",window),
    inventory(window, font),
    camera(username, window),
    mouse(camera),
    keyboard(),
    console(window, font),
    world(window),
    playerStats(window, font),
    clientEvents(clientEvents),
    username("NO USERNAME"),
    eventMediator(username, clientEvents, mouse, inventory, console, keyboard) {
    if(!font){
        throw SdlException("Could not open font", TTF_GetError());
    }
    audioManager.playMainMenuMusic(-1);
}

void GUI::setUsername(const std::string &client_username) {
    this->username = client_username;
    //this->camera.setIdToFollow(client_username);
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
    keyboard.movePlayer();
    inventory.use(clientEvents, mouse);
    mouse.use();
    //SDL_Point player_pos = dynamic_playable_renderables.at(username)->getPos();
    SDL_Point player_pos = this->getPlayableCharacter(username)->getPos();
    console.execute();
    camera.move(player_pos);

    audioManager.playRandomAmbientSound(20000);
}

/**Factory de eventos de server??*/
void GUI::updatePlayerPos(std::string id,const int player_x, const int player_y){
    //this->dynamic_playable_renderables[username]->updatePos(player_x, player_y, camera);
    this->getPlayableCharacter(id)->updatePos(player_x, player_y, camera);
    if(id == username){
        audioManager.playSound("step1",0);
    }
}

void GUI::updatePlayerStats(t_stats new_stats) {
    playerStats.update(new_stats);
}

/*Busca en la lista de renderizables dinamicos por id (username o npc_id)*/
void GUI::updateRenderableStats(const std::string &renderable_id, const std::string &effect_id) {
    this->getPlayableCharacter(renderable_id)->addVisualEffect(effect_id);
}

void GUI::updatePlayerEquipment(const equipment_t& equipment) {
    this->getPlayableCharacter(username)->updateEquipment(equipment);
    inventory.updateEquippedItems(equipment);
    if(equipment.armourName == "ghost"){
        audioManager.playSound("death", 0);
    } else {
        audioManager.playSound("equip", 0);
    }
}

void GUI::updateInventory(std::vector<std::string> player_inventory) {
    inventory.update(std::move(player_inventory));
}

void GUI::initStaticRenderables(const std::vector<location_t>& renderables){
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
void GUI::updateRenderables(std::vector<location_t> renderables){
    dynamic_renderables.clear();
    std::cout << "DEBUG: updating renderables" << std::endl;
    auto it = renderables.begin();
    for (; it != renderables.end(); it++) {
        std::string texture_id = textureManager.findTextureId(it->id);
        dynamic_renderables[it->id] = std::unique_ptr <SdlDynamicRenderable>
                (new SdlRenderableNPC(camera.toPixels(it->x),
                        camera.toPixels(it->y), textureManager,
                        texture_id, font, window, audioManager));
    }
}

void GUI::updateRenderablePlayables(std::vector<spawn_playable_character_t> renderables){
    dynamic_playable_renderables.clear();
    auto it = renderables.begin();
    for (; it != renderables.end(); it++) {
        /*Agregar al constructor un t_equipment y la raza por parametro*/
        /*Si limpio los renderizables tambien tengo que updatear los npc*/
        equipment_t equipment{"",it->weaponName, it->armourName, it->shieldName, it->helmetName};
        std::string race = it->race;
        dynamic_playable_renderables[it->username] = std::unique_ptr <SdlDynamicRenderable>
                    (new SdlRenderablePlayable(camera.toPixels(it->x),
                                               camera.toPixels(it->y), textureManager,
                                               it->username, race, equipment, font, window,
                                               audioManager));
        }
}

void GUI::updateRenderablePos(const int new_x, const int new_y, const std::string& renderable_id){
    //this->dynamic_renderables.at(renderable_id)->updatePos(new_x, new_y, camera);
    this->getNPC(renderable_id)->updatePos(new_x, new_y, camera);
}

void GUI::updateRenderablePlayableEquipment(const equipment_t& equipment,
                                            const std::string& renderable_id) {
    this->getPlayableCharacter(renderable_id)->updateEquipment(equipment);
    if(renderable_id == username){
        inventory.updateEquippedItems(equipment);
        if(equipment.armourName == "ghost"){
            audioManager.playSound("death", 0);
        } else {
            audioManager.playSound("equip", 0);
        }
    }
}


void GUI::updateDrops(const std::vector<location_t> &drops) {
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
    auto pc_it = dynamic_playable_renderables.begin();
    while(pc_it != dynamic_playable_renderables.end()){
        pc_it->second->render(camera);
        pc_it++;
    }
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


std::unique_ptr<SdlDynamicRenderable>& GUI::getPlayableCharacter(const std::string& playable_id){
    auto search = dynamic_playable_renderables.find(playable_id);
    if(search == dynamic_playable_renderables.end()){
        throw OSError("<GUI::getPlayableCharacter> "
                      "no se encuentra el playable_id, @param: %s", playable_id.c_str());
    }
    return search->second;
}

std::unique_ptr<SdlDynamicRenderable>& GUI::getNPC(const std::string& renderable_id){
    auto search = dynamic_renderables.find(renderable_id);
    if(search == dynamic_renderables.end()){
        throw OSError("<GUI::getNPC> "
                      "no se encuentra el renderable_id, @param: %s", renderable_id.c_str());
    }
    return search->second;
}


void GUI::disconnect() {
    clientEvents.push(std::unique_ptr<Message> (new Disconnect(this->username)));
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


