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
    std::map<std::string, std::unique_ptr<SdlDynamicRenderable>> dynamic_renderables;
    std::map<std::string, SdlTexture> dynamic_renderables_textures;

    typedef struct t_sprite_dimensions{
        int x;
        int y;
        std::string id;
    }t_sprite_dimensions;

    const std::vector<std::string> RENDERABLES_TEXTURES_ID{"goblin","skeleton","zombie","spider"};

    BlockingQueue<std::unique_ptr<Message>>& clientEvents;
public:
    GUI(int screen_width, int screen_height, BlockingQueue<std::unique_ptr<Message>>& clientEvents);

    void handleEvents(SDL_Event &event);

    void execute();

    void updatePlayerPos(const int player_x, const int player_y);

    void updateRenderablesPos(const int new_x, const int new_y,const std::string &renderable_id);

    void updateRenderables(std::vector<spawn_character_t> renderables);

    void updateInventory(std::vector<std::string> player_inventory);

    void updatePlayerStats(t_stats new_stats);

    void addFloorTile(int x, int y, int tile_id);

    void addObstacleTile(int x, int y, int tile_id);

    void render();

    void renderWorld();

    ~GUI();

    void setWorldDimensions(int w, int h);

    void updateDrops(const std::vector<std::string> &drops);

    void addWorldLayer(std::vector<int> data, const int init);
};


#endif //ARGENTUM_CLIENT_GUI_H
