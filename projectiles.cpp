//
// Created by spect on 4/30/2020.
//

#include "projectiles.h"

//set laser shape
Projectiles::Projectiles() {
    laser.setFillColor(Color::White);
    laser.setSize(Vector2f(4, 12));
    laser.setPosition(1200, 1200);
}

//fetch laser shape for drawing
const RectangleShape& Projectiles::getLaser() {
    return laser;
}


void Projectiles::playerFire(const Input& input, Ship& ship) {
    //create laser at ship as long as one does not already exist
    if (input.space && lasers.empty()) {
        laser.setPosition(ship.getX() + ship.getTex().getSize().x / 2 - laser.getSize().x / 2, ship.getY() - laser.getSize().y + 10);
        lasers.push_back(laser);
    }
    //fire laser forward at attackers
    if (!lasers.empty()) {
        laser.move(0, -15);
        //remove laser from the screen when it goes out of bounds
        if (laser.getPosition().y < 0) {
            lasers.pop_back();
            laser.setPosition(1200, 1200);
        }
    }
}

//remove laser from the screen
void Projectiles::destroy() {
    lasers.pop_back();
    laser.setPosition(1200, 1200);
}

//return x position of laser
double Projectiles::getX() {
    return laser.getPosition().x;
}

//return y position of laser
double Projectiles::getY() {
    return laser.getPosition().y;
}
