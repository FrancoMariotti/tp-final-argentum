//
// Created by franco on 25/6/20.
//

#ifndef ARGENTUM_OBSERVER_H
#define ARGENTUM_OBSERVER_H

class Observer {
public:
    virtual void movementUpdate(int x, int y) = 0;
    virtual void statsUpdate(float health_percentage,float mana_percentage,float exp_percentage,int gold,int level) = 0;
};


#endif //ARGENTUM_OBSERVER_H
