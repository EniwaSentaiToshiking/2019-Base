#include "DirectionDetecter.h"


DirectionDetecter::DirectionDetecter(int threshold, TurningDirection turningDirection)
{
    local = new Localization();
    this->threshold = threshold;
    this->turningDirection = turningDirection;
}

DirectionDetecter::~DirectionDetecter()
{
    delete local;
}

void DirectionDetecter::init(){
    local->update();
    prev_direction = local->getCurrentDirection();
}

bool DirectionDetecter::detect()
{
    local->update();
    if(this->threshold >= 0 && this->turningDirection == DIRECTION_LEFT){
        if(local->getCurrentDirection() - prev_direction >= threshold) return true;
    } else if(this->threshold >= 0 && this->turningDirection == DIRECTION_RIGHT) {
        if(prev_direction - local->getCurrentDirection() >= threshold) return true;
    } else {
        if(local->getCurrentDirection() - prev_direction <= threshold) return true;
    }
    return false;
}