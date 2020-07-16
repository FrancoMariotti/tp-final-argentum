//
// Created by agustin on 24/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_DYNAMIC_RENDERABLE_H
#define ARGENTUM_CLIENT_SDL_DYNAMIC_RENDERABLE_H


#include "client_sdl_texture_manager.h"
#include "common_message_structs.h"
#include "client_sdl_text.h"
#include "client_sdl_bar.h"
#include "client_sdl_effect.h"
#include "client_sdl_audio_manager.h"

class SdlTexture;
class SdlCamera;
class SdlDynamicRenderable {
protected:
    int pos_x;
    int pos_y;
    int old_x, old_y;
    int of_x, of_y;
    int animation_frame;
    bool is_moving;
    SdlTextureManager& textureManager;
    SdlAudioManager& audioManager;
    SdlTextureManager::e_body_orientation body_or;
    SdlTextureManager::e_head_orientation head_or;
    SdlText tag;
    SdlBar healthBar;
    std::vector<SdlEffect> effects;
public:
    SdlDynamicRenderable(int x, int y, SdlTextureManager &textureManager, const SdlWindow &window,
                         TTF_Font *font, std::string s_tag, SDL_Color color,
                         SdlAudioManager &audioManager);
    virtual void addVisualEffect(const std::string& effect_id);
    void updatePos(int new_x, int new_y, SdlCamera &camera);
    virtual void updateEquipment(const equipment_t& equipment) = 0;
    virtual void render(const SdlCamera& camera) = 0;
    int getPosX() const;
    int getPosY() const;
    SDL_Point getPos() const;
    virtual ~SdlDynamicRenderable() = default;

protected:
    void startAnimation();
    void endAnimationIfComplete();
    void renderEffects(const SdlCamera &camera);

};


class SdlRenderableNPC : public SdlDynamicRenderable {
private:
    const std::string texture_id;
public:
    SdlRenderableNPC(int x, int y, SdlTextureManager &textureManager,
            std::string texture_id, TTF_Font *font, const SdlWindow &window,
                     SdlAudioManager &audioManager);

    void updateEquipment(const equipment_t& equipment) override;

    void render(const SdlCamera& camera) override;
};

class SdlRenderablePlayable : public SdlDynamicRenderable{
private:
    std::string username;
    const std::string RACE;
    SdlTextureManager::t_player_appearance t_appearance;
public:
    SdlRenderablePlayable(int x, int y, SdlTextureManager &textureManager,
                          const std::string& username, const std::string& race,
                          const equipment_t& equipment, TTF_Font *font, const SdlWindow &window,
                          SdlAudioManager &audioManager);

    void updateEquipment(const equipment_t& equipment) override ;

    void render(const SdlCamera& camera) override;

};

#endif //ARGENTUM_CLIENT_SDL_DYNAMIC_RENDERABLE_H
