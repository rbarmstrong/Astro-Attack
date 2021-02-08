//
// Created by spect on 4/29/2020.
//

#ifndef SFML_TEMPLATE_ATTACKERS_H
#define SFML_TEMPLATE_ATTACKERS_H


#include <SFML/Graphics.hpp>
#include "helpers.h"

using namespace sf;
using namespace std;

class Attackers {

public:
    Attackers();
    const Sprite& getSprite(int index);
    void move();
    void destroy(int index);
    double getX(int index);
    double getY(int index);
    const Texture& getTex();
    double getSize();

private:
    Texture tex;
    Sprite sprite;
    double xPos;
    double yPos;
    vector<Sprite> sprites;
    vector<double> xPoss;
    vector<double> yPoss;

    double speed;
    int direction;
};


#endif //SFML_TEMPLATE_ATTACKERS_H
