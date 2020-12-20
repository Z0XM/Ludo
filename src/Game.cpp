#include "Game.hpp"
#include "LudoBoard.hpp"
#include "Dice.hpp"
#include "Pieces.hpp"
#include <iostream>

LudoGame::LudoGame(int tileWidth)
    :game_report_line(0), m_turn(0), m_turn_count(1), screenSize(15*tileWidth, 15*tileWidth), tileSize(tileWidth, tileWidth)
{
    colors[0] = sf::Color::Red;
    colors[1] = sf::Color::Blue;
    colors[2] = sf::Color::Yellow;
    colors[3] = sf::Color::Green;

    color_names[0] = "Red";
    color_names[1] = "Blue";
    color_names[2] = "Yellow";
    color_names[3] = "Green";

    putGameReport("Ludo Game Started");
}
LudoGame::~LudoGame()
{
    delete board;
    delete dice;
    delete pieces;

    putGameReport("Ludo Game Ended");
}
void LudoGame::load()
{
    board = new LudoBoard(this);
    board->load();

    dice = new LudoDice(this);
    dice->load();

    pieces = new Pieces(this);
    pieces->load();

    win.create(sf::VideoMode(screenSize.x, screenSize.y), "Ludo");
    win.setFramerateLimit(30);
    putGameReport("Ludo Game Loaded");
    currentState = gameState::WAITING_FOR_DICE_ROLL;
}
void LudoGame::draw()
{
    board->draw();
    dice->draw();
    pieces->draw();
}

void LudoGame::putGameReport(std::string report)
{
    std::cout << "\n " << game_report_line << " : " << report;
    game_report_line++;
}

void LudoGame::nextTurn()
{
    m_turn_count--;
    if(m_turn_count == 0){
        if(++m_turn == 4)m_turn = 0;
        m_turn_count = 1;
        dice->nextActive = m_turn;
        putGameReport("Turn Passed To " + color_names[m_turn]);
    }
}
void LudoGame::rollDice()
{
    if(dice->isDiceClicked()){
        dice->active = m_turn;
        m_dice_outcome  = dice->roll();

        sf::Vector2i playable = pieces->canPlay(m_dice_outcome);
        if(!playable.x){
            nextTurn();
            setGameState(gameState::WAITING_FOR_DICE_ROLL);
        }
        else if(playable.x == 1){
            pieces->move(playable.y, m_dice_outcome);
            nextTurn();
            setGameState(gameState::WAITING_FOR_DICE_ROLL);
        }
        else setGameState(gameState::WAITING_FOR_PAWN_SELECTION);
    }
}

void LudoGame::playTurn()
{
    Pawn* played = pieces->checkIfPlayed(m_dice_outcome);
    if(played != nullptr){
        pieces->move(played, m_dice_outcome);
        nextTurn();
        setGameState(gameState::WAITING_FOR_DICE_ROLL);
    }
}
void LudoGame::cheatDice(int steps)
{
    dice->active = m_turn;
    m_dice_outcome  = steps; // only this is cheated

    sf::Vector2i playable = pieces->canPlay(m_dice_outcome);
    if(!playable.x){
        nextTurn();
        setGameState(gameState::WAITING_FOR_DICE_ROLL);
    }
    else if(playable.x == 1){
        pieces->move(playable.y, m_dice_outcome);
        nextTurn();
        setGameState(gameState::WAITING_FOR_DICE_ROLL);
    }
    else setGameState(gameState::WAITING_FOR_PAWN_SELECTION);
}
void LudoGame::giveTurn()
{
    m_turn_count++;
}
int LudoGame::getTurn()
{
    return m_turn;
}
void LudoGame::setGameState(gameState state)
{
    currentState = state;
    if(state == gameState::WAITING_FOR_DICE_ROLL)putGameReport("Game State : WAITING_FOR_DICE_ROLL");
    else if(state == gameState::WAITING_FOR_PAWN_SELECTION)putGameReport("Game State : WAITING_FOR_PAWN_SELECTION");
}
void LudoGame::finishGame(int index)
{
    gameOver = true;
    secondWin.create(sf::VideoMode(500, 100), "Game has Ended");
    font.loadFromFile("data/fonts/consola.ttf");
    whoWon.setString(color_names[index] + " has Won!");
    whoWon.setCharacterSize(40);
    whoWon.setFont(font);
    whoWon.setPosition(25,25);
}
