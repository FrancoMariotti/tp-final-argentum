//
// Created by agustin on 19/7/20.
//

#ifndef ARGENTUM_CLIENT_UPDATE_FACTORY_H
#define ARGENTUM_CLIENT_UPDATE_FACTORY_H


#include "client_update.h"
#include "Common/Messages/Message.h"
class GUI;
class Message;
class UpdateFactory {
private:
    std::map<int, Update*> updates;
public:
    explicit UpdateFactory();
    UpdateFactory(const UpdateFactory& other) = delete;
    UpdateFactory(UpdateFactory&& other) = delete;

    const Update* getUpdate(const int msg_id) const;

    ~UpdateFactory();



};


#endif //ARGENTUM_CLIENT_UPDATE_FACTORY_H
