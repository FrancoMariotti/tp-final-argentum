//
// Created by franco on 19/6/20.
//

#include <algorithm>
#include <ctime>
#include "Log.h"
bool Log::hay_instancia = false;
Log* Log::singleton = NULL;

std::string obtener_nombre_log(){
    //std::string fin_arch = ".txt";

    std::time_t fecha = std::time(NULL);
    std::string fecha_str = std::ctime(&fecha);
    std::replace(fecha_str.begin(), fecha_str.end(), ' ', '-');
    fecha_str.append(".txt");

    return fecha_str;
}

Log* Log::instancia(){
    if (!hay_instancia){
        singleton = new Log();
        hay_instancia = true;
    }
    return singleton;
}

Log::Log():log_file(){
    path = obtener_nombre_log();
    log_file.open(path, std::ios_base::out | std::ios_base::app);
}

Log::~Log(){
    //exportar(str.str());
    singleton = NULL;
    hay_instancia = false;
}

void Log::cerrar(){
    if (hay_instancia){
        delete singleton;
    }
}

void Log::printPosicion(int x,int y) {
    log_file << "(" << x << "," << y <<")" <<std::endl;
}

void Log::write(std::string contenido) {
    log_file <<contenido <<std::endl;
}

