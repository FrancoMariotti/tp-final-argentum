//
// Created by agustin on 13/6/20.
//

#ifndef ARGENTUM_OSEXCEPTION_H
#define ARGENTUM_OSEXCEPTION_H

#include <exception>
#include <cerrno>
#include <cstring>
#include <cstdarg>
#include <cstdio>

#define BUF_LEN 256

class OSError : public std::exception {
private:
    char msg_error[BUF_LEN]="";

public:
    explicit OSError(const char* fmt, ...) noexcept;

    const char* what() const noexcept override;

    ~OSError() noexcept override = default;
};


#endif //ARGENTUM_OSEXCEPTION_H
