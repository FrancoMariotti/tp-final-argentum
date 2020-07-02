//
// Created by agustin on 12/6/20.
//

#include "client_sdl_button.h"
#include "common_proxy_socket.h"
#include "common_message.h"

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 200

/**TODO: Hacer un overload para el caso de que no
 * tengan spritesheet y sean imagenes estaticas
 * agregar una segunda textura para los clips, e.g recuadro verde al
 * pasar el mouse por encima*/

SdlButton::SdlButton(SdlTexture& buttonTexture, SdlTexture& outlineTexture) :
        double_click(0),
        single_click(0),
        position{0,0},
        current_sprite(BUTTON_SPRITE_MOUSE_OUT),
        outline_sprite(OUTLINE_SPRITE_MOUSE_OUT),
        buttonSpriteSheetTexture(buttonTexture),
        outlineTexture(outlineTexture) {
    this->width = buttonTexture.getWidth();
    this->height = buttonTexture.getHeight();

    for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) {
        this->button_sprite_clips[i] = {0, i * BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT};
    }
    for (int i = 0; i < OUTLINE_SPRITE_TOTAL; ++i) {
        this->outline_sprite_clips[i] = {(i+1) * 32, 32, 32, 32};
    }
}

void SdlButton::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

void SdlButton::handleEvent(SDL_Event &e, bool &is_event_handled) {
    //if mouse even happend
    if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP){
        int x,y;
        /*Devuelve la posicion del mouse*/
        SDL_GetMouseState(&x,&y);

        /*Boton no se clickeo*/
        this->double_click = 0;

        //Check if mouse is in button
        bool inside = true;
        //Mouse is left of the button
        if(x < position.x){
            inside = false;
        } else if (x > position.x + width ){
            inside = false;
        } else if (y < position.y){
            inside = false;
        } else if (y > position.y + height){
            inside = false;
        }
        if (!inside){
            current_sprite = BUTTON_SPRITE_MOUSE_OUT;
            outline_sprite = OUTLINE_SPRITE_MOUSE_OUT;
        }
        //Mouse is inside button
        else {
            //Set mouseover sprite
            switch (e.type){
                case SDL_MOUSEMOTION:
                    current_sprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    outline_sprite = OUTLINE_SPRITE_MOUSE_OVER_MOTION;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    current_sprite = BUTTON_SPRITE_MOUSE_DOWN;
                    is_event_handled = true;
                    if(e.button.button == SDL_BUTTON_LEFT && e.button.clicks >= 2){
                        /*usa item*/
                        this->double_click += 1;
                    } else if(e.button.button == SDL_BUTTON_RIGHT && e.button.clicks == 1){
                        /*selecciona item*/
                        this->single_click +=1;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    current_sprite = BUTTON_SPRITE_MOUSE_UP;
                    break;
            }
        }
    }

}

void SdlButton::use(BlockingQueue<std::unique_ptr<Message>> &clientEvents, int i, SdlMouse &mouse) {
    if(double_click > 0){
        std::cout << "double" << std::endl;
        (cmd)(clientEvents, i);
        double_click--;
    } else if (single_click > 0){
        std::cout << "single" << std::endl;
        mouse.setLastClickedItemIndex(i);
        single_click--;
    }
}

void SdlButton::render() {
    //Show current button sprite
    this->buttonSpriteSheetTexture.render(position.x,position.y);
    this->outlineTexture.render(position.x,position.y,&outline_sprite_clips[outline_sprite]);
}

SdlButton::~SdlButton() {
}
