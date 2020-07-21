#ifndef ARGENTUM_CLIENT_GUI_H
#define ARGENTUM_CLIENT_GUI_H


#include "client_sdl_player.h"
#include "client_sdl_inventory.h"
#include "client_sdl_console.h"
#include "client_sdl_world.h"
#include "client_sdl_window.h"
#include "client_sdl_stats.h"
#include "Common/Messages/message_structs.h"
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
    SdlAudioManager audioManager;
    SdlTextureManager textureManager;
    SdlTexture interface;
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
    std::string username;
    EventMediator eventMediator;
public:
    GUI(int screen_width, int screen_height, BlockingQueue<std::unique_ptr<Message>>& clientEvents);
    void setWorldDimensions(int w, int h);
    void addWorldLayer(std::vector<int> data, int init);
    void handleEvents(SDL_Event &event);
    void execute();
    void updatePlayerPos(const std::string &id, const int player_x, const int player_y);
    void updatePlayerEquipment(const equipment_t& equipment);
    void updatePlayerStats(t_stats new_stats);
    void updateInventory(std::vector<std::string> player_inventory);
    /*Inicializa los NPC comerciantes que no se mueven durante el juego*/
    void initStaticRenderables(const std::vector<location_t>& renderables);
    /*Actualiza los NPC que se encuentran vivos, eliminando lso que estan muertos*/
    void updateRenderables(std::vector<location_t> renderables);
    /**/
    void updateRenderablePos(int new_x, const int new_y, const std::string &renderable_id);
    void updateRenderablePlayableEquipment(const equipment_t &equipment, const std::string &renderable_id);
    void updateDrops(const std::vector<location_t> &drops);
    void render();
    void renderWorld();
    void updateConsoleOutput(std::vector<std::string> console_outputs);
    void updateRenderableStats(const std::string &renderable_id, const std::string &effect_id);
    void updateRenderablePlayables(std::vector<spawn_playable_character_t> renderables);
    void setUsername(const std::string &client_username);
    //std::string getUsername();
    void disconnect();
    ~GUI();


private:
    std::unique_ptr<SdlDynamicRenderable>& getPlayableCharacter(const std::string& playable_id);
    std::unique_ptr<SdlDynamicRenderable> &getNPC(const std::string &renderable_id);
};


#endif //ARGENTUM_CLIENT_GUI_H
