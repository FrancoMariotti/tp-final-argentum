//
// Created by franco on 19/6/20.
//

#ifndef ARGENTUM_LOG_H
#define ARGENTUM_LOG_H


#include <string>
#include <fstream>

class Log {
    std::string path;
    std::ofstream log_file;
    static Log* singleton;
    static bool hay_instancia;
    Log();
    public:
        //Devuelve una instancia de Log.
        static Log* instancia();
        //Destructor del Log.
        ~Log();
        //Cierra el Log.
        static void cerrar();
        void printPosicion(int x, int y);
        void write(std::string contenido);
};


#endif //ARGENTUM_LOG_H
