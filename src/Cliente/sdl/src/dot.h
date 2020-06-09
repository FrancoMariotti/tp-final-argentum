//
// Created by agustin on 8/6/20.
//

#ifndef SDLTEST_DOT_H
#define SDLTEST_DOT_H


#include <SDL2/SDL_image.h>
#include <vector>
class SdlTexture;
class Dot{
private:
    /*Textura del Dot*/
    SdlTexture& m_texture;

    //The dimensions of the dot
    const int DOT_WIDTH = 20;
    const int DOT_HEIGHT = 20;

    //Maximum axis velocity of the dot
    const int DOT_VEL = 10;

    //The X and Y offsets of the dot
    int mPosX, mPosY;

    //The velocity of the dot
    int mVelX, mVelY;

    //Dot's collision box
    std::vector<SDL_Rect> mColliders;

    bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b);

    //Moves the collision boxes relative to the dot's offset
    void shiftColliders();

public:
    //Initializes the variables
    Dot(int x, int y, SdlTexture &texture);

    //Takes key presses and adjusts the dot's velocity
    void handleEvent( SDL_Event& e );

    //Moves the dot
    void move(std::vector<SDL_Rect> &otherColliders, int screen_width, int screen_height);

    //Shows the dot on the screen
    void render();

    //Gets the collision boxes
    std::vector <SDL_Rect>& getColliders();

};



#endif //SDLTEST_DOT_H
