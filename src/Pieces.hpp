#pragma once
#include "IncludeHelper.hpp"
#include <SFML/Graphics.hpp>

class Pieces{
private:
    Pawn *m_pawns[4][4], *m_current;
    sf::Texture t_img;
    LudoGame *m_game;

public:
    int hasWon[4];
    Pieces(LudoGame*);
    ~Pieces();

    void load();
    void draw();
    void isAnyPawnAtPos(sf::Vector2f pos);
    void isAnyPawnAtIndex(int index);

    void move(Pawn* played, int steps);
    void move(int pawn, int steps);

    std::vector<Pawn*> getPlayablePos(int, int);
    Pawn* checkIfPlayed(int);
    sf::Vector2i canPlay(int);
};

