//
// Created by agustin on 8/6/20.
//

#include "dot.h"
#include "client_sdl_texture.h"

Dot::Dot(int x, int y, SdlTexture &texture) :
    m_texture(texture){
    //Initialize the offsets
    mPosX = x;
    mPosY = y;
    //Create the necessary SDL_Rects
    mColliders.resize( 11 );

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

    //Initialize the collision boxes' width and height
    mColliders[ 0 ].w = 6;
    mColliders[ 0 ].h = 1;

    mColliders[ 1 ].w = 10;
    mColliders[ 1 ].h = 1;

    mColliders[ 2 ].w = 14;
    mColliders[ 2 ].h = 1;

    mColliders[ 3 ].w = 16;
    mColliders[ 3 ].h = 2;

    mColliders[ 4 ].w = 18;
    mColliders[ 4 ].h = 2;

    mColliders[ 5 ].w = 20;
    mColliders[ 5 ].h = 6;

    mColliders[ 6 ].w = 18;
    mColliders[ 6 ].h = 2;

    mColliders[ 7 ].w = 16;
    mColliders[ 7 ].h = 2;

    mColliders[ 8 ].w = 14;
    mColliders[ 8 ].h = 1;

    mColliders[ 9 ].w = 10;
    mColliders[ 9 ].h = 1;

    mColliders[ 10 ].w = 6;
    mColliders[ 10 ].h = 1;

    //Initialize colliders relative to position
    shiftColliders();
}

void Dot::handleEvent(SDL_Event &e) {
    //if a key was pressed
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        //Adjust the velocity
        switch(e.key.keysym.sym){
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;

        }
    }

    //if key was released
    /*Cuando se suelta la tecla tenemos que deshacer los cambios*/
    if(e.type == SDL_KEYUP && e.key.repeat == 0){
        switch(e.key.keysym.sym){
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;

        }
    }
}

void Dot::move(std::vector<SDL_Rect> &otherColliders, int screen_width, int screen_height) {
    //Move the dot left or right
    mPosX += mVelX;
    shiftColliders();

    //if the dot collided or went too far to the left or right
    if((mPosX < 0) || (mPosX + DOT_WIDTH > screen_width) || checkCollision(mColliders, otherColliders)){
        //Move back
        mPosX -= mVelX;
        shiftColliders();
    }

    //Move the dot up or down
    mPosY += mVelY;
    shiftColliders();
    //if the dot went too far up or down
    if((mPosY < 0) || (mPosY + DOT_HEIGHT > screen_height) || checkCollision(mColliders, otherColliders)){
        //Move back
        mPosY -= mVelY;
        shiftColliders();
    }
}

void Dot::render() {
    //Show the dot
    m_texture.render(mPosX, mPosY);
}

void Dot::shiftColliders() {
    //The row offset
    int r = 0;

    for (unsigned long set = 0; set < mColliders.size() ; ++set) {
        //Center the collision box
        mColliders[set].x = mPosX + ((DOT_WIDTH - mColliders[set].w) / 2);

        //Set the collision box at its row offset;
        mColliders[set].y = mPosY + r;

        //Move the row offset down the height of the collision box
        r += mColliders[set].h;
    }
}

bool Dot::checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b){
//The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Go through the A boxes
    for( unsigned long Abox = 0; Abox < a.size(); Abox++ )
    {
        //Calculate the sides of rect A
        leftA = a[ Abox ].x;
        rightA = a[ Abox ].x + a[ Abox ].w;
        topA = a[ Abox ].y;
        bottomA = a[ Abox ].y + a[ Abox ].h;

        //Go through the B boxes
        for(unsigned long Bbox = 0; Bbox < b.size(); Bbox++ )
        {
            //Calculate the sides of rect B
            leftB = b[ Bbox ].x;
            rightB = b[ Bbox ].x + b[ Bbox ].w;
            topB = b[ Bbox ].y;
            bottomB = b[ Bbox ].y + b[ Bbox ].h;

            //If no sides from A are outside of B
            if(!((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)))
            {
                //A collision is detected
                return true;
            }
        }
    }

    //If neither set of collision boxes touched
    return false;
}

std::vector<SDL_Rect>& Dot::getColliders() {
    return mColliders;
}
