#include "Configuration.h"

Configuration& Configuration::getInstance() {
   static Configuration instance;
   return instance;
}