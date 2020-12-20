#pragma once
#include <SFML/Graphics.hpp>
#include "IncludeHelper.hpp"
#include <string>

enum class gameState{WAITING_FOR_DICE_ROLL, WAITING_FOR_PAWN_SELECTION};

class LudoGame{
private:
    int game_report_line;
    sf::Texture piece_t;
    int m_turn;
    int m_dice_outcome;
    int m_turn_count;

public:
    sf::Vector2f screenSize;
    sf::Vector2f tileSize;
    sf::Color colors[4];
    std::string color_names[4];
    bool gameOver;
    LudoBoard *board;
    LudoDice *dice;
    Pieces *pieces;
    sf::RenderWindow win;
    sf::RenderWindow secondWin;
    sf::Text whoWon;
    sf::Font font;
    gameState currentState;

    LudoGame(int);
    ~LudoGame();
    void load();
    void draw();
    void putGameReport(std::string);

    void rollDice();

    void playTurn();

    void cheatDice(int steps);

    void giveTurn();
    void nextTurn();
    int getTurn();
    void setGameState(gameState);
    int getGameState();

    void finishGame(int index);
};

