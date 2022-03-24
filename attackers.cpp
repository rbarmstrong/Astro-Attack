//
// Created by spect on 4/29/2020.
//

#include "attackers.h"
#include <iostream>


using namespace std;

Attackers::Attackers() {
    //load texture for attackers
    if (!tex.loadFromFile("data/InvaderA_00@2x.png")) {
        cerr << "Could not load texture" << endl;
        exit(-1);
    }
    //add attacker sprites to attackers vector, setting their textures and positions
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 11; j++) {
            sprites.push_back(sprite);
            sprites.at(sprites.size() - 1).setTexture(tex);
            xPoss.push_back(xPos);
            xPoss.at(xPoss.size() - 1) = 80 + (tex.getSize().x + 20) * j;
            yPoss.push_back(yPos);
            yPoss.at(yPoss.size() - 1) = 250 + (tex.getSize().y + 40) * i;
        }
    }
    //set speed and direction of movement
    speed = 0.5;
    direction = 1;
}

//return the sprite of the selected attacker
const Sprite& Attackers::getSprite(int index) {
    return sprites.at(index);
}

//move attackers across and down the screen
void Attackers::move() {
    //move attackers horizontally and update their position
    for (int i = 0; i < sprites.size(); i++) {
        xPoss.at(i) += speed * direction;
        sprites.at(i).setPosition(xPoss.at(i), yPoss.at(i));
    }
    for (int i = 0; i < sprites.size(); i++) {
        //when block of attackers reaches end of screen, change direction, increase speed, and shift down vertically
        if (xPoss.at(i) + tex.getSize().x > 888 || xPoss.at(i) < 0) {
            speed += 0.2;
            direction *= -1;
            for (int j = 0; j < sprites.size(); j++) {
                yPoss.at(j) += 10;
            }
            break;
        }
    }
}

//delete specified attacker
void Attackers::destroy(int index) {
    sprites.erase(sprites.begin() + index);
    xPoss.erase(xPoss.begin() + index);
    yPoss.erase(yPoss.begin() + index);
}

//return x position of specified attacker
double Attackers::getX(int index) {
    return xPoss.at(index);
}

//return y position of specified attacker
double Attackers::getY(int index) {
    return yPoss.at(index);
}

//return texture of specified attacker
const Texture& Attackers::getTex() {
    return tex;
}

//return number of total attackers on the screen
double Attackers::getSize() {
    return sprites.size();
}
