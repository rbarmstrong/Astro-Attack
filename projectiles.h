//
// Created by spect on 4/30/2020.
//

#ifndef SFML_TEMPLATE_PROJECTILES_H
#define SFML_TEMPLATE_PROJECTILES_H

#include <SFML/Graphics.hpp>
#include "helpers.h"
#include "ship.h"

using namespace sf;
using namespace std;

class Projectiles {
public:
    Projectiles();
    const RectangleShape& getLaser();
    void playerFire(const Input& input, Ship& ship);
    void destroy();
    double getX();
    double getY();

private:
    RectangleShape laser;
    vector<RectangleShape> lasers;
};


#endif //SFML_TEMPLATE_PROJECTILES_H
