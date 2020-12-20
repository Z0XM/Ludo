#include "LudoBoard.hpp"
#include "Game.hpp"
#include "Pawn.hpp"
#include <iostream>

LudoBoard::LudoBoard(LudoGame *game)
    :m_game(game), scaleFactor(0.25 * game->screenSize.x / 750, 0.25 * game->screenSize.y / 750)
{
    for(int i = 0; i < 52; i++){
        m_index_piece_count[i] = 0;
    }

    m_game->putGameReport("Ludo Board Constructed");
}
LudoBoard::~LudoBoard()
{
    m_game->putGameReport("Ludo Board Destroyed");
}
void LudoBoard::load()
{
    t_home.loadFromFile("data/images/grey home.png");

    for(int i = 0; i < 4; i++){
        home[i].setTexture(t_home);
        home[i].setColor(m_game->colors[i]);
        home[i].scale(scaleFactor);
    }

    home[0].setPosition(getCellPos(0, 0));
    home[1].setPosition(getCellPos(9, 0));
    home[2].setPosition(getCellPos(9, 9));
    home[3].setPosition(getCellPos(0, 9));

    t_path.loadFromFile("data/images/grey path.png");

    t_base.loadFromFile("data/images/base.png");

    t_win_base.loadFromFile("data/images/win base.png");

    for(int i = 0; i < 52; i++){
        if(i % 13 == 0 || (i-8) % 13 == 0)path[i].img.setTexture(t_base);
        else path[i].img.setTexture(t_path);
        if(i % 13 == 0)path[i].img.setColor(m_game->colors[i / 13]);
        path[i].img.scale(scaleFactor);
    }

    std::map<int, sf::Vector2i> path_index;
    path_index[0] = {1, 6}; path_index[1] = {2, 6}; path_index[2] = {3, 6}; path_index[3] = {4, 6}; path_index[4] = {5, 6};
    path_index[5] = {6, 5}; path_index[6] = {6, 4}; path_index[7] = {6, 3}; path_index[8] = {6, 2}; path_index[9] = {6, 1};
    path_index[10] = {6, 0}; path_index[11] = {7, 0}; path_index[12] = {8, 0};
    path_index[13] = {8, 1}; path_index[14] = {8, 2}; path_index[15] = {8, 3}; path_index[16] = {8, 4}; path_index[17] = {8, 5};
    path_index[18] = {9, 6}; path_index[19] = {10, 6}; path_index[20] = {11, 6}; path_index[21] = {12, 6}; path_index[22] = {13, 6};
    path_index[23] = {14, 6}; path_index[24] = {14, 7}; path_index[25] = {14, 8};
    path_index[26] = {13, 8}; path_index[27] = {12, 8}; path_index[28] = {11, 8}; path_index[29] = {10, 8}; path_index[30] = {9, 8};
    path_index[31] = {8, 9}; path_index[32] = {8, 10}; path_index[33] = {8, 11}; path_index[34] = {8, 12}; path_index[35] = {8, 13};
    path_index[36] = {8, 14}; path_index[37] = {7, 14}; path_index[38] = {6, 14};
    path_index[39] = {6, 13}; path_index[40] = {6, 12}; path_index[41] = {6, 11}; path_index[42] = {6, 10}; path_index[43] = {6, 9};
    path_index[44] = {5, 8}; path_index[45] = {4, 8}; path_index[46] = {3, 8}; path_index[47] = {2, 8}; path_index[48] = {1, 8};
    path_index[49] = {0, 8}; path_index[50] = {0, 7}; path_index[51] = {0, 6};

    for(int i = 0; i < 52; i++){
        if(i % 13 == 0 || (i-8) % 13 == 0)path[i].isStop = true;
        path[i].img.setPosition(getCellPos(path_index[i].x, path_index[i].y));
    }

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 5; j++){
            path_win[i][j].setTexture(t_path);
            path_win[i][j].setColor(m_game->colors[i]);
            path_win[i][j].scale(scaleFactor);
        }
    }

    for(int j = 0; j < 5; j++)
        path_win[0][j].setPosition(getCellPos(j+1, 7));

    for(int j = 0; j < 5; j++)
        path_win[1][j].setPosition(getCellPos(7, j+1));

    for(int j = 0; j < 5; j++)
        path_win[2][j].setPosition(getCellPos(13-j, 7));

    for(int j = 0; j < 5; j++)
        path_win[3][j].setPosition(getCellPos(7, 13-j));

    win_base.setTexture(t_win_base);
    win_base.setPosition(getCellPos(6, 6));
    win_base.scale(scaleFactor);

    m_game->putGameReport("Ludo Board Loaded");
}
void LudoBoard::draw()
{
    for(int i = 0; i < 4; i++){
        m_game->win.draw(home[i]);
    }
    for(int i = 0; i < 52; i++){
        m_game->win.draw(path[i].img);
    }
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 5; j++){
            m_game->win.draw(path_win[i][j]);
        }
    }
    m_game->win.draw(win_base);
}

sf::Vector2f LudoBoard::getCellPos(float x, float y){
    return {m_game->tileSize.x * x, m_game->tileSize.y * y};
}
sf::Vector2f LudoBoard::getCellPos(sf::Vector2f p){
    return {m_game->tileSize.x * p.x, m_game->tileSize.y * p.y};
}
sf::Vector2f LudoBoard::getCellCoord(sf::Vector2f pos)
{
    return {(pos.x) / m_game->tileSize.x, (pos.y) / m_game->tileSize.y};
}
sf::Vector2f LudoBoard::getCellPosByIndex(int index){
    if(index > 51)index = index - 52;
    return path[index].img.getPosition();
}
int LudoBoard::getIndexByCellPos(sf::Vector2f p){
    for(int i = 0; i < 52; i++){
        if(path[i].img.getPosition() == p)return i;
    }
    return -1;
}

void LudoBoard::increaseIPC(int index)
{
    m_index_piece_count[index] += 1;
}
void LudoBoard::decreaseIPC(int index)
{
    m_index_piece_count[index] -= 1;
}
int LudoBoard::getIPC(int index)
{
    return m_index_piece_count[index];
}

void LudoBoard::setPawnPointedByPath(Pawn *ptr, int index)
{
    path[index].pawn.push_back(ptr);
}
Pawn* LudoBoard::getPawnPointedByPath(int index)
{
    return path[index].pawn[0];
}
void LudoBoard::removePawnPointedByPath(int index)
{
    path[index].pawn.pop_back();
}
void LudoBoard::removePawnPointedByPath(int home_code, int index)
{
    for(int i = 0; i < path[index].pawn.size(); i++){
        if(path[index].pawn[i]->getHomeCode() == home_code){
            path[index].pawn.erase(path[index].pawn.begin() + i);
            break;
        }
    }
}

bool LudoBoard::isStop(int index)
{
    return path[index].isStop;
}

void LudoBoard::setToWin(Pawn* pawn, int index)
{
    pawn->setPosition(pawn->regulatePos(path_win[pawn->getHomeCode() / 10][index].getPosition()));
}
void LudoBoard::getToWinBase(Pawn* pawn)
{
    sf::Vector2f winPos[][4] = { { {6.5,7}, {6.5,7.5}, {6.5,8}, {7,7.5} },
                                 { {7,6.5}, {7.5,6.5}, {8,6.5}, {7.5,7} },
                                 { {8.5,8}, {8.5,7.5}, {8.5,7}, {8,7.5} },
                                 { {8,8.5}, {7.5,8.5}, {7,8.5}, {7.5,8} } };
    pawn->setPosition(getCellPos(winPos[pawn->getHomeCode() / 10][pawn->getHomeCode() % 10]));
}
