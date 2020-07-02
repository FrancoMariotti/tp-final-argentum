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

class DynamicRenderable;
class GUI {
private:
    SdlWindow window;
    TTF_Font* font;
    SdlTextureManager textureManager;
    SdlTexture interface;
    SdlPlayer player;
    SdlInventory inventory;
    SdlCamera camera;
    SdlMouse mouse;
    SdlKeyboard keyboard;
    SdlConsole console;
    SdlWorld world;
    SdlStats playerStats;
    std::map<std::string, std::unique_ptr<DynamicRenderable>> dynamic_renderables;

    BlockingQueue<std::unique_ptr<Message>>& clientEvents;
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
    void updateRenderables(std::vector<spawn_character_t> renderables);
    void updateRenderablePos(int new_x, const int new_y, const std::string &renderable_id);
    void updateRenderablePlayableEquipment(const equipment_t &equipment, const std::string &renderable_id);
    void updateDrops(const std::vector<std::string> &drops);

    void render();

    void renderWorld();

    ~GUI();

};


#endif //ARGENTUM_CLIENT_GUI_H
