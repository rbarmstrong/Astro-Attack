//
// Created by spect on 4/30/2020.
//

#include "collisions.h"

//check if given projectile coordinates are within the rectangular hitbox zone, return true if so
bool Collisions::collisionDetect(double projectileX, double projectileY, double xUpper, double xLower, double yUpper, double yLower) {
    return projectileX < xUpper && projectileX > xLower && projectileY < yUpper && projectileY > yLower;
}
