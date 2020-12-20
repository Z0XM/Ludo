#include "Pieces.hpp"
#include "Game.hpp"
#include "LudoBoard.hpp"
#include "Pawn.hpp"

#include <vector>

Pieces::Pieces(LudoGame* game)
    :m_game(game)
{
    hasWon[0] = hasWon[1] = hasWon[2] = hasWon[3] = 0;

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            m_pawns[i][j] = new Pawn(m_game, 10*i + j);

    m_game->putGameReport("Pieces Created");
}
Pieces::~Pieces()
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            delete m_pawns[i][j];

    m_game->putGameReport("Pieces Destroyed");
}

void Pieces::load()
{
    t_img.loadFromFile("data/images/piece.png");

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            m_pawns[i][j]->load(t_img);
        }
    }

    m_game->putGameReport("Pieces Loaded");
}

void Pieces::draw()
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            m_pawns[i][j]->draw();
}
sf::Vector2i Pieces::canPlay(int steps)
{
    sf::Vector2i playable = {0, 0};
    for(int i = 0; i < 4; i++){
        if(m_pawns[m_game->getTurn()][i]->isPlayable(steps))playable = {++playable.x, i};
    }
    return playable;
}
Pawn* Pieces::checkIfPlayed(int steps)
{
    sf::Vector2f mousePos = m_game->win.mapPixelToCoords(sf::Mouse::getPosition(m_game->win));

    for(int i = 0; i < 4; i++){
        if(m_pawns[m_game->getTurn()][i]->hit(mousePos) && m_pawns[m_game->getTurn()][i]->isPlayable(steps)){
            return m_pawns[m_game->getTurn()][i];
        }
    }
    return nullptr;
}
void Pieces::move(int pawn, int steps)
{
    m_current = m_pawns[m_game->getTurn()][pawn];
    m_current->move(steps);
}
void Pieces::move(Pawn* played, int steps)
{
    m_current = played;
    m_current->move(steps);
}
