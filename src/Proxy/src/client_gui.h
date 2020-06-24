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

class SdlDynamicRenderable;
class GUI {
private:
    SdlWindow window;
    TTF_Font* font;

    SdlPlayer player;
    SdlInventory inventory;
    SdlCamera camera;
    SdlConsole console;
    SdlWorld world;
    std::map<std::string, SdlDynamicRenderable> dynamic_renderables;

    BlockingQueue<std::unique_ptr<Message>>& clientEvents;
public:
    GUI(int screen_width, int screen_height, BlockingQueue<std::unique_ptr<Message>>& clientEvents);

    void handleEvents(SDL_Event &event);

    void execute();

    void update();

    void update(int player_vel_x, int player_vel_y);

    void render();

    ~GUI();

    void addTile(int x, int y, const std::string &tile_id);

    void addItem(const std::string &item_id);

    void update(const int vel_x, const int vel_y, const std::string &renderable_id);

    void addNpc(const int x, const int y, const std::string &npc_id);
};


#endif //ARGENTUM_CLIENT_GUI_H
