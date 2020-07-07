//
// Created by agustin on 24/6/20.
//

#ifndef ARGENTUM_CLIENT_GUI_H
#define ARGENTUM_CLIENT_GUI_H


#include "client_sdl_player.h"
#include "client_sdl_inventory.h"
#include "client_sdl_console.h"
#include "client_sdl_world.h"
#include "client_sdl_window.h"
#include "client_sdl_stats.h"
#include "common_message_structs.h"
#include "client_sdl_mouse.h"
#include "client_sdl_keyboard.h"
#include "client_sdl_audio_manager.h"
#include "client_sdl_timer.h"
#include "client_sdl_dynamic_renderable.h"
#include "client_event_mediator.h"

class SdlDynamicRenderable;
class GUI {
private:
    SdlWindow window;
    TTF_Font* font;
    SdlTimer timer;
    SdlAudioManager audioManager;
    SdlTextureManager textureManager;
    SdlTexture interface;
    SdlRenderablePlayable player;
    SdlInventory inventory;
    SdlCamera camera;
    SdlMouse mouse;
    SdlKeyboard keyboard;
    SdlConsole console;
    SdlWorld world;
    SdlStats playerStats;
    std::map<std::string, std::unique_ptr<SdlDynamicRenderable>> dynamic_renderables;
    std::map<std::string, std::unique_ptr<SdlDynamicRenderable>> dynamic_playable_renderables;
    std::vector<std::unique_ptr<SdlDynamicRenderable>> static_renderables;
    BlockingQueue<std::unique_ptr<Message>>& clientEvents;
    EventMediator eventMediator;
public:
    GUI(int screen_width, int screen_height, BlockingQueue<std::unique_ptr<Message>>& clientEvents);
    void setWorldDimensions(int w, int h);
    void addWorldLayer(std::vector<int> data, int init);
    void handleEvents(SDL_Event &event);
    void execute();
    void updatePlayerPos(int player_x, int player_y);
    void updatePlayerEquipment(const equipment_t& equipment);
    void updatePlayerStats(t_stats new_stats);
    void updateInventory(std::vector<std::string> player_inventory);
    /*Inicializa los NPC comerciantes que no se mueven durante el juego*/
    void initStaticRenderables(const std::vector<spawn_character_t>& renderables);
    /*Actualiza los NPC que se encuentran vivos, eliminando lso que estan muertos*/
    void updateRenderables(std::vector<spawn_character_t> renderables);
    /**/
    void updateRenderablePos(int new_x, const int new_y, const std::string &renderable_id);
    void updateRenderablePlayableEquipment(const equipment_t &equipment, const std::string &renderable_id);
    void updateDrops(const std::vector<spawn_character_t> &drops);
    void render();
    void renderWorld();

    ~GUI();

    void updateConsoleOutput(std::vector<std::string> console_outputs);

    void updateRenderableStats(std::string renderable_id, std::string effect_id);

    void updateRenderablePlayables(std::vector<spawn_playable_character_t> renderables);
};


#endif //ARGENTUM_CLIENT_GUI_H
