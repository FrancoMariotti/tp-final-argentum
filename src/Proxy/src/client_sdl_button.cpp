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
        left_click(0),
        right_click(0),
        position{0,0},
        outline_sprite(OUTLINE_SPRITE_MOUSE_OUT),
        outline_sprite_clips{{0,0,0,0},
                             {0,0,0,0}},
        buttonSpriteSheetTexture(buttonTexture),
        outlineTexture(outlineTexture) {
    this->width = buttonTexture.getWidth();
    this->height = buttonTexture.getHeight();
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
        this->left_click = 0;

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
            outline_sprite = OUTLINE_SPRITE_MOUSE_OUT;
        }
        //Mouse is inside button
        else {
            //Set mouseover sprite
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
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    break;
            }
        }
    }

}

void SdlButton::use(BlockingQueue<std::unique_ptr<Message>> &clientEvents, int i, SdlMouse &mouse) {
    if(left_click > 0){
        std::cout << "double" << std::endl;
        (cmd)(clientEvents, i);
        left_click--;
    } else if (right_click > 0){
        std::cout << "single" << std::endl;
        mouse.setLastClickedItemIndex(i);
        right_click--;
    }
}

void SdlButton::render() {
    //Show current button sprite
    this->buttonSpriteSheetTexture.render(position.x,position.y);
    this->outlineTexture.render(position.x,position.y,&outline_sprite_clips[outline_sprite]);
}

