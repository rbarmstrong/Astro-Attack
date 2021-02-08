#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#include <SFML/Graphics.hpp>

#include "ship.h"
#include "helpers.h"
#include "attackers.h"
#include "projectiles.h"
#include "collisions.h"

using namespace sf;

int main() {
    //initialize variables for the game clock
    Clock clock;
    const int FRAME_RATE = 60;
    const Time FRAME_TIME = seconds(1.0 / FRAME_RATE);

    //create window for game
    RenderWindow window( VideoMode(888, 1080), "Astro Attack" );

    //initialize objects
    Input input;
    Ship ship;
    Attackers attackers;
    Projectiles projectiles;

    //create red line near bottom of the screen to represent the "danger zone"
    RectangleShape dangerZone;
    dangerZone.setPosition(0, 855);
    dangerZone.setSize(Vector2f(888, 5));
    dangerZone.setFillColor(Color::Red);

    //load arcade font to be used for text
    Font arcadeFont;
    if(!arcadeFont.loadFromFile("bin/data/ARCADE_N.ttf")) {
        cerr << "Could not load font" << endl;
        return -1;
    }

    //set text for player score and hi score titles
    Text scoreTitles;
    scoreTitles.setFont(arcadeFont);
    scoreTitles.setString("SCORE<1>\tHI-SCORE");
    scoreTitles.setFillColor(Color::White);
    scoreTitles.setPosition(25,20);

    //initialize player score integer and string, set text for the string
    int playerScoreInt = 0;
    stringstream ss;
    ss << setw(4) << setfill('0') << playerScoreInt;
    string playerScoreStr = ss.str();
    ss.str(string());
    ss.clear();
    Text playerScoreValue;
    playerScoreValue.setFont(arcadeFont);
    playerScoreValue.setString(playerScoreStr);
    playerScoreValue.setFillColor(Color::White);
    playerScoreValue.setPosition(80, 80);

    //initialize hiscore, either from hiscore.txt file or as 0 if file doe not exist, set text for hiscore
    int hiScoreInt;
    ifstream hiScoreFile("bin/data/hiscore.txt");
    ofstream newHiScore;
    if (!hiScoreFile.is_open()) {
        hiScoreInt = 0;
        cerr << "hiscore.txt not found";
    }
    else {
        hiScoreFile >> hiScoreInt;
    }
    ss << setw(4) << setfill('0') << hiScoreInt;
    string hiScoreStr = ss.str();
    ss.str(string());
    ss.clear();
    Text hiScoreValue;
    hiScoreValue.setFont(arcadeFont);
    hiScoreValue.setString(hiScoreStr);
    hiScoreValue.setFillColor(Color::White);
    hiScoreValue.setPosition(430, 80);

    //set game over screen text
    Text gameOverScreen;
    gameOverScreen.setFont(arcadeFont);
    gameOverScreen.setString("GAME OVER");
    gameOverScreen.setFillColor(Color::White);
    gameOverScreen.setPosition(300, 300);

    Text victoryScreen;
    victoryScreen.setFont(arcadeFont);
    victoryScreen.setString("YOU WIN");
    victoryScreen.setFillColor(Color::White);
    victoryScreen.setPosition(300, 300);

    //initialize game over boolean for use when checking if the player has lost
    bool gameOver = false;

    bool victory = false;

    //main game loop, each loop is executed over the period of 1 frame
    while( window.isOpen() ) {
        //resets the clock and clears the screen for the incoming frame cycle
        clock.restart();
        window.clear( Color::Black );

        //draw stationary images
        window.draw(scoreTitles);
        window.draw(playerScoreValue);
        window.draw(hiScoreValue);
        window.draw(dangerZone);

        //move the ship based on input, draw ship at its current position
        ship.move(input);
        window.draw(ship.getSprite());

        //move attackers based on their current speed and direction, draw each attacker at its current position
        attackers.move();
        for (int i = 0; i < attackers.getSize(); i++) {
            window.draw(attackers.getSprite(i));
            //if enemies cross the danger zone, game over
            if (attackers.getY(i) + attackers.getTex().getSize().y > 850) {
                gameOver = true;
            }
        }
        for (int i = 0; i < attackers.getSize(); i++) {
            //check if player's laser has collided with any attackers
            if (Collisions::collisionDetect(projectiles.getX(), projectiles.getY(), attackers.getX(i) +
            attackers.getTex().getSize().x, attackers.getX(i), attackers.getY(i) + attackers.getTex().getSize().y,
            attackers.getY(i))) {
                //destroy laser and the attacker it hit, increase player's score by 10
                attackers.destroy(i);
                projectiles.destroy();
                playerScoreInt += 10;
                //check if the player has defeated all enemies
                if (attackers.getSize() == 0 && !gameOver) {
                    victory = true;
                }
                //update player score
                ss << setw(4) << setfill('0') << playerScoreInt;
                playerScoreValue.setString(ss.str());
                ss.str(string());
                ss.clear();
                //if player has achieved the new hiscore, update hiscore
                if (playerScoreInt > hiScoreInt) {
                    hiScoreInt = playerScoreInt;
                    newHiScore.open("bin/data/hiscore.txt");
                    newHiScore << hiScoreInt;
                    newHiScore.close();
                }
            }
        }



        //fire laser if space is pressed, draw laser at its current position
        projectiles.playerFire(input, ship);
        window.draw(projectiles.getLaser());

        //if player has lost, display game over screen
        if (gameOver) {
            window.draw(gameOverScreen);
        }

        //if player has won, display victory screen
        if (victory) {
            window.draw(victoryScreen);
        }

        //display everything drawn in the window
        window.display();

        //check events
        Event event;
        while( window.pollEvent(event) ) {
            //if player hits red x, close game
            if (event.type == Event::Closed ) {
                window.close();
            }
            //check all keys pressed by player
            else if (event.type == Event::KeyPressed && !(gameOver || victory)) {
                switch (event.key.code) {
                    //if player presses left, left key press is read
                    case Keyboard::Left:
                        input.left = true;
                        break;
                        //if player presses right, right key press is read
                    case Keyboard::Right:
                        input.right = true;
                        break;
                        //if player presses space, space key press is read
                    case Keyboard::Space:
                        input.space = true;
                        break;
                }
            }
            else if (event.type == Event::KeyReleased) {
                switch (event.key.code) {
                    //stop reading left key press
                    case Keyboard::Left:
                        input.left = false;
                        break;
                        //stop reading right key press
                    case Keyboard::Right:
                        input.right = false;
                        break;
                        //stop reading space key press
                    case Keyboard::Space:
                        input.space = false;
                        break;
                }
            }
        }
        //guarantees the game runs at a maximum of 30 fps, closes hiscore input file
        Time elapsed = clock.getElapsedTime();
        Time sleepTime = FRAME_TIME - elapsed;
        sleep(sleepTime);
        hiScoreFile.close();
    }

    return EXIT_SUCCESS;
}