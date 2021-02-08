//
// Created by spect on 4/29/2020.
//

#ifndef SFML_TEMPLATE_SHIP_H
#define SFML_TEMPLATE_SHIP_H

#include <SFML/Graphics.hpp>
#include "helpers.h"

using namespace sf;
using namespace std;

class Ship {

public:
    Ship();
    const Sprite& getSprite();
    void move(const Input& input);
    double getX();
    double getY();
    const Texture& getTex();

private:
    Texture tex;
    Sprite sprite;
    double xPos;
    double yPos;
    double speed;
};


#endif //SFML_TEMPLATE_SHIP_H
