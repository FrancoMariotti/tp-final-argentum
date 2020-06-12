//
// Created by agustin on 6/6/20.
//

#include "client_sdl_exception.h"

SdlException::SdlException(const char* description, const char* sdlError) :
    std::exception(),
    description(description) {
        this->description.append("\n SDL_ERROR:").append(sdlError);
}

const char* SdlException::what() const noexcept{
    return this->description.c_str();
}

