//
// Created by agustin on 12/6/20.
//

#include "client_sdl_button.h"
#include "Common/common_proxy_socket.h"
#include "Common/Messages/Message.h"
#include "client_sdl_inventory.h"

SdlButton::SdlButton(SdlTexture &buttonTexture, SdlTexture &outlineTexture, TTF_Font *font, const SdlWindow &window,
                     const std::string texture_id) :
        left_click(0),
        right_click(0),
        sprite_locked(false),
        is_equipped(false),
        texture_id(texture_id),
        position{0,0},
        outline_sprite(OUTLINE_SPRITE_MOUSE_OUT),
        buttonSpriteSheetTexture(buttonTexture),
        outlineTexture(outlineTexture),
        buttonText(0,0," ", font, window, SDL_Color{0,0xFF,0,0xFF})
        {
    this->width = buttonTexture.getWidth();
    this->height = buttonTexture.getHeight();
    for (int i = 0; i < OUTLINE_SPRITE_TOTAL - 1; ++i) {
        this->outline_sprite_clips.push_back(SDL_Rect{(i+1) * 32, 32, 32, 32});
    }
    this->outline_sprite_clips.push_back(SDL_Rect{ 32, 0, 32, 32});
}

SdlButton::SdlButton(SdlButton &&other) noexcept :
    left_click(0),
    right_click(0),
    sprite_locked(false),
    is_equipped(false),
    texture_id(other.texture_id),
    position{other.position.x, other.position.y},
    outline_sprite(OUTLINE_SPRITE_MOUSE_OUT),
    buttonSpriteSheetTexture(other.buttonSpriteSheetTexture),
    outlineTexture(other.outlineTexture),
    buttonText(std::move(other.buttonText))
    {
    this->width = buttonSpriteSheetTexture.getWidth();
    this->height = buttonSpriteSheetTexture.getHeight();
    for (int i = 0; i < OUTLINE_SPRITE_TOTAL - 1; ++i) {
        this->outline_sprite_clips.push_back(SDL_Rect{(i+1) * 32, 32, 32, 32});
    }
    this->outline_sprite_clips.push_back(SDL_Rect{ 32, 0, 32, 32});
}

void SdlButton::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

void SdlButton::setEquipped(bool equipped){
    is_equipped = equipped;
}

void SdlButton::handleEvent(SDL_Event &e, bool &is_event_handled) {
    //if mouse even happend
    if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP){
        int x,y;
        /*Devuelve la posicion del mouse*/
        SDL_GetMouseState(&x,&y);

        /*Boton no se clickeo*/
        this->left_click = 0;

        bool inside = (x > position.x && x < position.x + width && y > position.y && y < position.y + height);

        if (!inside){
            outline_sprite = OUTLINE_SPRITE_MOUSE_OUT;
        } else {
            switch (e.type){
                case SDL_MOUSEMOTION:
                    outline_sprite = OUTLINE_SPRITE_MOUSE_OVER_MOTION;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    is_event_handled = true;
                    if(e.button.button == SDL_BUTTON_LEFT && e.button.clicks == 1){
                        /*usa item*/
                        this->left_click += 1;
                    } else if(e.button.button == SDL_BUTTON_RIGHT && e.button.clicks == 1){
                        /*selecciona item*/
                        this->right_click +=1;
                        outline_sprite = OUTLINE_SPRITE_BUTTON_CLICKED;
                    }
                    break;
            }
        }
    }
    if(sprite_locked){
        outline_sprite = OUTLINE_SPRITE_BUTTON_CLICKED;
    }
}

void SdlButton::use(BlockingQueue<std::unique_ptr<Message>> &clientEvents, int i,
        SdlMouse &mouse, SdlInventory *inventory) {
    if (left_click > 0){
        std::cout << "DEBUG: left click" << std::endl;
        (cmd)(clientEvents, i);
        this->is_equipped = true;
        inventory->notify(i, 0);
        left_click--;
    } else if (right_click > 0){
        std::cout << "DEBUG: right click" << std::endl;
        inventory->unlockOutlineSprite();
        lockOutlineSprite(true);
        inventory->notify(i);
        right_click--;
    }
}

void SdlButton::lockOutlineSprite(const bool lock){
    this->sprite_locked = lock;
}

void SdlButton::updateText(const equipment_t &equipment){
    if (is_equipped){
        buttonText.update("E");
    } else {
        buttonText.update(" ");
        is_equipped = false;
    }
}

void SdlButton::render() {
    //Show current button sprite
    this->buttonSpriteSheetTexture.render(position.x,position.y);
    this->outlineTexture.render(position.x,position.y,&outline_sprite_clips[outline_sprite]);
    this->buttonText.render(position.x, position.y);
}
