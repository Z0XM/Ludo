#pragma once
#include "IncludeHelper.hpp"
#include <SFML/Graphics.hpp>

struct PawnSpritePointer{
    std::vector<Pawn*> pawn;
    sf::Sprite img;
    bool isStop;
};

class LudoBoard{
private:
    sf::Texture t_home, t_win_base, t_path, t_base;
    sf::Sprite home[4], win_base, path_win[4][5];
    PawnSpritePointer path[52];
    int m_index_piece_count[52];
    LudoGame *m_game;

public:
    LudoBoard(LudoGame*);
    ~LudoBoard();
    void load();
    void draw();
    sf::Vector2f getCellPos(float x, float y);
    sf::Vector2f getCellPos(sf::Vector2f p);
    sf::Vector2f getCellCoord(sf::Vector2f pos);
    sf::Vector2f getCellPosByIndex(int index);
    int getIndexByCellPos(sf::Vector2f p);

    void increaseIPC(int index);
    void decreaseIPC(int index);
    int getIPC(int index);

    bool isStop(int index);

    void setPawnPointedByPath(Pawn* ptr, int index);
    void removePawnPointedByPath(int index);
    void removePawnPointedByPath(int home_code, int index);
    Pawn* getPawnPointedByPath(int index);

    void setToWin(Pawn*, int);
    void getToWinBase(Pawn*);

    sf::Vector2f scaleFactor;
};

