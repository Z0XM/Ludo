#include <SFML/Graphics.hpp>
#include <iostream>

#include "src/Game.hpp"
#include "src/LudoBoard.hpp"
#include "src/Dice.hpp"
#include "src/Pieces.hpp"

int main()
{
    LudoGame* game = new LudoGame(50);

    game->load();

    sf::ContextSettings contextSettings;
    contextSettings.antialiasingLevel = 8;

    while (!game->gameOver && game->win.isOpen())
    {
        sf::Event event;
        while (game->win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                game->win.close();

            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (game->currentState == gameState::WAITING_FOR_DICE_ROLL)
                        game->rollDice();

                    else if (game->currentState == gameState::WAITING_FOR_PAWN_SELECTION)
                        game->playTurn();
                }
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (game->currentState == gameState::WAITING_FOR_DICE_ROLL && event.key.code > 25 && event.key.code < 36) {
                    game->cheatDice(event.key.code - 26);
                }
            }

        }
        game->win.clear(sf::Color(103, 103, 103));
        game->draw();
        game->win.display();
    }
    while (game->secondWin.isOpen() && game->win.isOpen()) {
        sf::Event event;
        while (game->win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                game->secondWin.close();
                game->win.close();
            }
        }
        while (game->secondWin.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                game->secondWin.close();
                game->win.close();
            }
        }
        game->secondWin.clear();
        game->secondWin.draw(game->whoWon);
        game->secondWin.display();
    }

    delete game;
    return 0;
}
