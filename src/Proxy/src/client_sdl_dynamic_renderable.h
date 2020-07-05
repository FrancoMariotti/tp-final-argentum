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

class SdlTexture;
class SdlCamera;
class SdlDynamicRenderable {
protected:
    int pos_x;
    int pos_y;
    int old_x, old_y;
    int animation_frame;
    bool is_moving;
    const int MAX_FRAMES = 4;
    SdlTextureManager& textureManager;
    SdlTextureManager::e_body_orientation body_or;
    SdlTextureManager::e_head_orientation head_or;
    SdlText tag;
    SdlBar healthBar;
    SdlEffect effect;
public:
    SdlDynamicRenderable(int x, int y, SdlTextureManager &textureManager, const SdlWindow &window,
                         TTF_Font *font, const std::string s_tag, const SDL_Color color);
    virtual void updatePos(int new_x, int new_y, SdlCamera &camera);
    virtual void updateEquipment(const equipment_t& equipment) = 0;
    virtual void render(const SdlCamera& camera) = 0;
    virtual ~SdlDynamicRenderable() = default;

protected:
    void startAnimation();
    void endAnimationIfComplete();
};


class SdlRenderableNPC : public SdlDynamicRenderable {
private:
    const std::string texture_id;
public:
    SdlRenderableNPC(const int x, const int y, SdlTextureManager &textureManager,
                     const std::string texture_id, TTF_Font *font, const SdlWindow &window);

    void updateEquipment(const equipment_t& equipment) override;

    void render(const SdlCamera& camera) override;
};

class SdlRenderablePlayable : public SdlDynamicRenderable{
private:
    std::string username;
    SdlTextureManager::t_player_appearance t_appearance;

public:
    SdlRenderablePlayable(int x, int y, SdlTextureManager &textureManager,
                          const std::string username, TTF_Font *font, const SdlWindow &window);

    void updateEquipment(const equipment_t& equipment) override ;

    void render(const SdlCamera& camera) override;

    int getPosX() const;

    int getPosY() const;
};

#endif //ARGENTUM_CLIENT_SDL_DYNAMIC_RENDERABLE_H
