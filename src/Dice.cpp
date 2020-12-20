#include "Dice.hpp"
#include "Game.hpp"
#include "LudoBoard.hpp"
#include <cstdlib>
#include <string>
#include <iostream>

LudoDice::LudoDice(LudoGame* game)
    :m_game(game)
{
    m_game->putGameReport("Ludo Dice constructed");
}

void LudoDice::load()
{
    for(int i = 0; i < 4; i ++){
        for(int j = 0; j < 6; j++){
            num_count[i][j] = 6;
        }
        total_count[i] = 36;
    }

    t_img[0].loadFromFile("data/images/dice/one.png");
    t_img[1].loadFromFile("data/images/dice/two.png");
    t_img[2].loadFromFile("data/images/dice/three.png");
    t_img[3].loadFromFile("data/images/dice/four.png");
    t_img[4].loadFromFile("data/images/dice/five.png");
    t_img[5].loadFromFile("data/images/dice/six.png");
    t_img[6].loadFromFile("data/images/dice/default.png");

    img.setTexture(t_img[6]);
    nextImg.setTexture(t_img[6]);
    nextImg.scale(m_game->board->scaleFactor);
    img.scale(m_game->board->scaleFactor);

    imgPos[0] = m_game->board->getCellPos(2, 2);
    imgPos[1] = m_game->board->getCellPos(11, 2);
    imgPos[2] = m_game->board->getCellPos(11, 11);
    imgPos[3] = m_game->board->getCellPos(2, 11);

    active = 0;
    outcome = 0;

    m_game->putGameReport("Ludo Dice Loaded");
}
LudoDice::~LudoDice()
{
    m_game->putGameReport("Ludo Dice Destroyed");
}
int LudoDice::roll()
{
    if(total_count[active] == 0){
        total_count[active] = 36;
        for(int i = 0; i < 6; i++)
            num_count[active][i] = 6;
    }
    srand((unsigned)time(&nTime));

    int n = rand() % total_count[active] + 1;

    int i = 0, sum = 0;
    while(num_count[active][i] < n - sum){
        i++;
        sum += num_count[active][i];
    }
    if(i == 6)i=5;
    num_count[active][i]--;
    total_count[active]--;

    outcome  = i+1;

    m_game->putGameReport(std::string("Dice rolled for " + m_game->color_names[active] + " = " + (char)(outcome + 48) ));

    return outcome;
}

void LudoDice::draw()
{
    nextImg.setPosition(imgPos[nextActive]);
    m_game->win.draw(nextImg);

    if(outcome != 0){
        img.setPosition(imgPos[active]);
        img.setTexture(t_img[outcome - 1]);
        m_game->win.draw(img);
    }
}

bool LudoDice::isDiceClicked()
{
    sf::Vector2f mousePos = m_game->win.mapPixelToCoords(sf::Mouse::getPosition(m_game->win));
    return nextImg.getGlobalBounds().contains(mousePos);
}



