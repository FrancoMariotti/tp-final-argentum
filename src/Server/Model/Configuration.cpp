//
// Created by franco on 15/7/20.
//

#include "Configuration.h"

Configuration& Configuration::getInstance() {
   /*if (!instance) return new Configuration;
    return instance;*/
   static Configuration instance;
   return instance;
}
/*
Configuration::~Configuration() {
    if (instance) delete instance;
}
*/