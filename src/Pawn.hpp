#pragma once

#include <SFML/Graphics.hpp>
#include "IncludeHelper.hpp"

class Pawn{
private:
    int m_index_code;
    int m_home_code;
    int m_arrival_code;
    bool is_at_home;
    LudoGame *m_game;
    sf::Sprite *img;
    bool isWinning;

public:
    bool hasWon;
    sf::Vector2f scaleFactor;

    Pawn(LudoGame*, int);
    ~Pawn();
    void load(sf::Texture&);
    void draw();
    void setIndexCode(int);
    int getIndexCode();
    void updateIndexCode(int);
    void setHomeCode(int);
    int getHomeCode();

    sf::Vector2f regulatePos(sf::Vector2f);
    void updatePos(sf::Vector2f scale_factor);
    bool isAtPos(sf::Vector2f);
    bool isAtIndex(int);
    bool isAtHome();
    void hasLeftHome();
    void hasArrivedHome();
    void sendHome();

    void move(int steps);
    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f);
    bool hit(sf::Vector2f&);

    bool isPlayable(int);
};
