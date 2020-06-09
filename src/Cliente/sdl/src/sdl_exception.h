//
// Created by agustin on 6/6/20.
//

#ifndef LAZYFOO_SDL_EXCEPTION_H
#define LAZYFOO_SDL_EXCEPTION_H

#include <exception>
#include <string>

class SdlException: public std::exception {
private:
    std::string description;
public:
    SdlException(const char* description, const char* sdlError);

    const char* what() const noexcept override;
};



#endif //LAZYFOO_SDL_EXCEPTION_H
