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

class SdlDynamicRenderable;
class GUI {
private:
    SdlWindow window;
    TTF_Font* font;

    SdlPlayer player;
    SdlInventory inventory;
    SdlCamera camera;
    SdlMouse mouse;
    SdlConsole console;
    SdlWorld world;
    SdlStats playerStats;
    std::map<std::string, SdlDynamicRenderable> dynamic_renderables;
    std::map<std::string, SdlTexture> dynamic_renderables_textures;

    BlockingQueue<std::unique_ptr<Message>>& clientEvents;
public:
    GUI(int screen_width, int screen_height, BlockingQueue<std::unique_ptr<Message>>& clientEvents);

    void handleEvents(SDL_Event &event);

    void execute();

    void update(int player_vel_x, int player_vel_y);

    void update(int vel_x, int vel_y, const std::string &renderable_id);

    void update(std::vector<std::string> player_inventory);

    void render();

    void addTile(int x, int y, int tile_id);

    void addItem(const std::string &item_id);

    void addRenderable(const int x, const int y, const std::string &renderable_id);

    ~GUI();

    void update(t_stats new_stats);
};


#endif //ARGENTUM_CLIENT_GUI_H
