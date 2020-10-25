#include "Bullet.h"
#include "Player.h"

Bullet::Bullet(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f pos) :
    animation(texture, imageCount, switchTime)
{
    this->speed = speed;
    row = 0;
    body.setSize(sf::Vector2f(50.0f, 50.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(pos);
    body.setTexture(texture);
    bool faceleft = false;
}
Bullet::~Bullet()
{
}

void Bullet::updateR(float deltaTime)
{
    velocity.y = 0;
    velocity.x = speed;  

    body.move(velocity * deltaTime);
    animation.updateBu(row, deltaTime, false);
    body.setTextureRect(animation.uvRect);
}

void Bullet::updateL(float deltaTime)
{
    velocity.y = 0;
    velocity.x = speed;

    body.move(-(velocity * deltaTime));
    animation.updateBu(row, deltaTime , true);
    body.setTextureRect(animation.uvRect);
}

void Bullet::attackR(sf::Vector2f pos) 
{
    if (isAva == true)
    {
        body.setPosition(pos.x + 50.0f, pos.y);
        isAva = false;
    }
}

void Bullet::attackL(sf::Vector2f pos)
{
    if (isAva == true)
    {
        body.setPosition(pos.x - 50.0f, pos.y);
        isAva = false;
    }
}

bool Bullet::isAvaliable()
{
    isAva = true;
    return isAva;
}

void Bullet::draw(sf::RenderWindow& window)
{
    window.draw(body);
}
