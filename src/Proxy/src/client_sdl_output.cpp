//
// Created by agustin on 26/6/20.
//

#include "client_sdl_output.h"

SdlOutput::SdlOutput(const int x, const int y, const SdlWindow &window, TTF_Font *font, const std::string label) :
    text_color{0x33, 0x33, 0x33, 0xFF},
    font(font),
    LABEL(label),
    output(LABEL + "0"),
    outputTexture(output, font, text_color, window),
    X(x),
    Y(y)
    {}

/*Sobreescribe atributo output con @param new_output*/
void SdlOutput::update(const std::string& new_output){
    this->output = LABEL + new_output;
    outputTexture.loadFromRenderedText(output,text_color,font);

}

void SdlOutput::render(){
    outputTexture.render(X,Y);
}