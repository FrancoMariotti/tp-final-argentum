//
// Created by agustin on 24/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_DYNAMIC_RENDERABLE_H
#define ARGENTUM_CLIENT_SDL_DYNAMIC_RENDERABLE_H


#include "client_sdl_texture_manager.h"
#include "common_message_structs.h"

class SdlTexture;
class SdlCamera;
class DynamicRenderable {
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

public:
    DynamicRenderable(int x, int y, SdlTextureManager &textureManager);
    virtual void updatePos(int new_x, int new_y, SdlCamera &camera);
    virtual void updateEquipment(const equipment_t& equipment) = 0;
    virtual void render(const SdlCamera& camera) = 0;
    virtual ~DynamicRenderable() = default;

protected:
    void startAnimation();
    void endAnimationIfComplete();
};


class RenderableNPC : public DynamicRenderable {
private:
    const std::string texture_id;
public:
    RenderableNPC(int x, int y, SdlTextureManager &textureManager,
                         std::string texture_id);

    void updateEquipment(const equipment_t& equipment) override;

    void render(const SdlCamera& camera) override;
};

class RenderablePlayable : public DynamicRenderable{
private:
    std::string username;
    SdlTextureManager::t_player_appearance t_appearance;

public:
    RenderablePlayable(int x, int y, SdlTextureManager &textureManager);

    void updateEquipment(const equipment_t& equipment) override ;

    void render(const SdlCamera& camera) override;

    int getPosX() const;

    int getPosY() const;
};

#endif //ARGENTUM_CLIENT_SDL_DYNAMIC_RENDERABLE_H
