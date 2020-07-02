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
    textureManager(window),
    interface(screen_width, screen_height, "../../Proxy/interfaces/VentanaPrincipal.jpg",window),
    player(textureManager),
    inventory(screen_width, screen_height, window),
    camera(screen_width, screen_height, player),
    mouse(camera),
    keyboard(),
    console(screen_width, screen_height, window, font),
    world(window),
    playerStats(screen_width, screen_height, window, font),
    clientEvents(clientEvents) {
    if(!font){
        throw SdlException("Could not open font", TTF_GetError());
    }

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
}
/**Factory de eventos de server??*/
void GUI::updatePlayerPos(const int player_x, const int player_y){
    player.updatePos(player_x, player_y, camera);
}

void GUI::updatePlayerStats(t_stats new_stats) {
    playerStats.update(new_stats);
}

void GUI::updatePlayerEquipment(const equipment_t& equipment) {
    player.updateEquipment(equipment);
}

void GUI::updateInventory(std::vector<std::string> player_inventory) {
    inventory.update(std::move(player_inventory));
}

/*Itera @param renderables y busca el id de textura que corresponde con el id del renderizable y lo agrega al map
 * con key: id y value: puntero a DynamicRenderable*/
void GUI::updateRenderables(std::vector<spawn_character_t> renderables){
    dynamic_renderables.clear();
    /**Test para dibujar otro jugador*/
    dynamic_renderables["player123"] = std::unique_ptr <DynamicRenderable>
            (new RenderablePlayable(camera.toPixels(10), camera.toPixels(10), textureManager));
    auto it = renderables.begin();
    for(; it != renderables.end(); it++) {
        std::string texture_id = textureManager.findTextureId(it->id);
        if (texture_id != "player"){
            dynamic_renderables[it->id] = std::unique_ptr <DynamicRenderable>
                    (new RenderableNPC(camera.toPixels(it->x), camera.toPixels(it->y), textureManager,
                                       texture_id));
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


void GUI::updateDrops(const std::vector<std::string> &drops) {
    world.updateDrops(drops);
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
    //interface.render(0,0);
    playerStats.render();

    //Update screen
    window.render();
}

void GUI::renderWorld() {
    world.render(camera);
    //world.renderFloor(camera);
    //world.renderObstacles(camera);
    //world.renderDrops(inventory, camera);
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

