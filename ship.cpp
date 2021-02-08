//
// Created by spect on 4/29/2020.
//

#include "ship.h"
#include <iostream>

using namespace std;

Ship::Ship() {
    //load ship texture
    if (!tex.loadFromFile("bin/data/Ship@2x.png")) {
        cerr << "Could not load texture" << endl;
        exit(-1);
    }
    //initialize ship position, set visuals and speed
    xPos = 80;
    yPos = 900;
    sprite.setTexture(tex);
    sprite.setColor(Color::Green);
    speed = 6;
}

//return ship sprite for drawing
const Sprite& Ship::getSprite() {
    return sprite;
}

//move ship based on keyboard input
void Ship::move(const Input& input) {
    //move ship left
    if (input.left && xPos > 0) {
        xPos -= speed;
    }
    //move ship right
    if (input.right && xPos < 888 - tex.getSize().x) {
        xPos += speed;
    }
    //update ship position after move
    sprite.setPosition(xPos, yPos);
}

//return x position of ship
double Ship::getX() {
    return xPos;
}

//return y position of ship
double Ship::getY() {
    return yPos;
}

//return texture used for ship
const Texture& Ship::getTex() {
    return tex;
}
