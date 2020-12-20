#pragma once
#include "IncludeHelper.hpp"
#include <time.h>
#include <SFML/Graphics.hpp>

class LudoDice{
private:
    int num_count[4][6];
    int total_count[4];
    time_t nTime;
    sf::Sprite img, nextImg;
    sf::Texture t_img[7];
    sf::Vector2f imgPos[4];
    int outcome;
    LudoGame *m_game;

public:
    LudoDice(LudoGame*);
    ~LudoDice();
    void load();
    int roll();
    void draw();
    bool isDiceClicked();

    int active;
    int nextActive;

};

