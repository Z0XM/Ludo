#include "Pawn.hpp"
#include "Pieces.hpp"
#include "Game.hpp"
#include "LudoBoard.hpp"

Pawn::Pawn(LudoGame* game, int code)
    :m_index_code(-1), m_home_code(code), is_at_home(true), m_game(game), isWinning(false), hasWon(false), scaleFactor(0.5f, 0.5f)
{
    img = new sf::Sprite;
}
Pawn::~Pawn(){
    delete img;
}

int regulateIndex(int index){
    if(index > 51) index -= 52;
    else if (index < 0)index += 52;
    return index;
}

void Pawn::setIndexCode(int code){
    m_index_code = regulateIndex(code);
}
void Pawn::updateIndexCode(int dcode){
    m_index_code = regulateIndex(m_index_code + dcode);
}
int Pawn::getIndexCode(){
    return m_index_code;
}
void Pawn::setHomeCode(int code){
    m_home_code = code;
}
int Pawn::getHomeCode(){
    return m_home_code;
}

void Pawn::load(sf::Texture& t_img)
{
    img->setTexture(t_img);
    img->setColor(m_game->colors[m_home_code/10]);
    img->setOrigin(img->getLocalBounds().width * 0.5f, img->getLocalBounds().height * 0.5f);

    sendHome();

    img->setScale(m_game->board->scaleFactor);
}

void Pawn::draw()
{
    m_game->win.draw(*img);
}

bool Pawn::isAtPos(sf::Vector2f pos){
    if(img->getPosition() == pos)return true;
    return false;
}
bool Pawn::isAtIndex(int index){
    if(m_index_code == index)return true;
    return false;
}
bool Pawn::isAtHome(){
    return is_at_home;
}
void Pawn::hasLeftHome(){
    is_at_home = false;
}
void Pawn::hasArrivedHome(){
    is_at_home = true;
}

void Pawn::sendHome()
{
    m_index_code = -1;
    sf::Vector2f startPos[] = {{1.f, 1.f}, {10.f, 1.f}, {10.f, 10.f}, {1.f, 10.f} };
    sf::Vector2f endPos[] = {{0.f, 0.f}, {3.f, 0.f}, {3.f, 3.f}, {0.f, 3.f} };
    img->setPosition(regulatePos(m_game->board->getCellPos(startPos[m_home_code/10] + endPos[m_home_code%10])));
    is_at_home = true;
}
bool Pawn::isPlayable(int steps)
{
    if(hasWon)return false;
    if(isWinning && getIndexCode() + steps > 5)return false;
    if(isAtHome() && (steps == 6 || steps == 1))return true;

    if(!isAtHome()){
        int newIndex = regulateIndex(getIndexCode() + steps);
        if(m_game->board->isStop(newIndex))return true;
        if(m_game->board->getIPC(newIndex) == 0)return true;
        else if(m_game->board->getPawnPointedByPath(newIndex)->getHomeCode()/10 != getHomeCode()/10)
            return true;
    }

    return false;
}
sf::Vector2f Pawn::regulatePos(sf::Vector2f pos)
{
    return {pos.x + m_game->tileSize.x * scaleFactor.x, pos.y + m_game->tileSize.y * scaleFactor.y};
}
void Pawn::updatePos(sf::Vector2f scale_factor)
{
    scaleFactor = scale_factor;
    img->setPosition(regulatePos(m_game->board->getCellPosByIndex(getIndexCode())));
}

void Pawn::move(int steps)
{
    sf::Vector2f scaleByHome[4] = { {0.25f, 0.25f}, {0.75f, 0.25f}, {0.75f, 0.75f}, {0.25f, 0.75f} };

    if(isAtHome() && (steps == 6 || steps == 1)){
        setIndexCode(13 * (m_home_code/10));
        hasLeftHome();
        if(m_game->board->getIPC(getIndexCode()) == 1){
            m_game->board->getPawnPointedByPath(getIndexCode())->updatePos(scaleByHome[m_game->board->getPawnPointedByPath(getIndexCode())->getHomeCode() / 10]);
        }
        if(m_game->board->getIPC(getIndexCode()) >= 1){
            scaleFactor = scaleByHome[getHomeCode() / 10];
        }
        img->setPosition(regulatePos(m_game->board->getCellPosByIndex(13 * (m_home_code/10))));

        m_game->board->increaseIPC(getIndexCode());
        m_game->board->setPawnPointedByPath(this, getIndexCode());
    }

    else if(!isAtHome() && !isWinning){
        int oldIndex = getIndexCode();
        int newIndex = regulateIndex(oldIndex + steps);

        m_game->board->removePawnPointedByPath(getHomeCode(), oldIndex);
        m_game->board->decreaseIPC(oldIndex);

        if(m_game->board->getIPC(oldIndex) == 1){
            m_game->board->getPawnPointedByPath(oldIndex)->updatePos(sf::Vector2f(0.5f, 0.5f));
        }

        if(m_game->board->getIPC(newIndex) == 0)
            scaleFactor = sf::Vector2f(0.5f, 0.5f);

        if((oldIndex < 13 * (getHomeCode() / 10) || (oldIndex < 51 && getHomeCode() / 10 == 0))
            && oldIndex + steps > regulateIndex(13 * (getHomeCode() / 10) - 1)){
            isWinning = true;
            int index = steps + oldIndex - regulateIndex(13 * (getHomeCode() / 10) - 1);
            m_game->board->setToWin(this, index);
            setIndexCode(index);
        }
        else{
            if(m_game->board->isStop(newIndex)){
                if(m_game->board->getIPC(newIndex) == 1){
                    m_game->board->getPawnPointedByPath(newIndex)->updatePos(scaleByHome[m_game->board->getPawnPointedByPath(newIndex)->getHomeCode() / 10]);
                }
                if(m_game->board->getIPC(newIndex) >= 1){
                    scaleFactor = scaleByHome[getHomeCode() / 10];
                }
            }
            else if(m_game->board->getIPC(newIndex) == 1){
                m_game->board->getPawnPointedByPath(newIndex)->updatePos(sf::Vector2f(0.5f, 0.5f));
                scaleFactor = sf::Vector2f(0.5f, 0.5f);
                m_game->board->getPawnPointedByPath(newIndex)->sendHome();
                m_game->board->decreaseIPC(newIndex);
                m_game->giveTurn();
            }
            img->setPosition(regulatePos(m_game->board->getCellPosByIndex(newIndex)));
            updateIndexCode(steps);

            m_game->board->setPawnPointedByPath(this, getIndexCode());
            m_game->board->increaseIPC(getIndexCode());
        }
    }
    else if(isWinning){
        int index = getIndexCode() + steps;
        if(index == 5){
            hasWon = true;
            m_game->pieces->hasWon[getHomeCode() / 10]++;
            if(m_game->pieces->hasWon[getHomeCode() / 10] == 4)m_game->finishGame(getHomeCode() / 10);
            img->setColor(sf::Color(0,0,0,50));
            m_game->board->getToWinBase(this);
        } else {
            m_game->board->setToWin(this, index);
            setIndexCode(index);
        }
    }
    if(steps == 6)m_game->giveTurn();
}

sf::Vector2f Pawn::getPosition()
{
    return img->getPosition();
}
void Pawn::setPosition(sf::Vector2f pos)
{
    img->setPosition(pos);
}
bool Pawn::hit(sf::Vector2f& mousePos)
{
    return img->getGlobalBounds().contains(mousePos);
}
