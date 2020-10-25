#include "Player.h"
#include <iostream>
Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpheight) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpheight = jumpheight;
	row = 0;
	faceleft = false;
	falling = false;
	dash = false;
	canjump = true;
	fire = false;
	body.setSize(sf::Vector2f(131.25f, 150.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(535.0f, 360.0f);
	body.setTexture(texture);
}

Player::~Player()
{
}

void Player::update(float deltaTime, sf::Vector2f direction)
{
	//std::cout << direction.x <<" "<< direction.y << std::endl;
	velocity.x = 0.0f;
	fire = false;
	dash = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		velocity.x -= speed ;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		velocity.x += speed ;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && (canjump == true))
	{
		canjump = false;
		velocity.y = -sqrtf(2.0f * 1500.0f * jumpheight);		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{				
		dash = true;
		if (dash == true)
		{
		    row = 3;
		}
		if (faceleft == true)
		{
			velocity.x = -2 * speed ;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				velocity.x = 2 * speed ;
				faceleft = false;
			}
		}
		if (faceleft == false)
		{
			velocity.x = 2 * speed ;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			{
				velocity.x = -2 * speed ;
				faceleft = true;
			}
		}		
	}	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
	{
		fire = true;
	}
	//-----------------------------------
	if (direction.y >= 0.0f)
	{		
		velocity.y += 1500.0f * deltaTime;
	}
	//-----------------------------------
	if (velocity.x == 0 && velocity.y == 0 && fire == false)
	{
		dash = false;
		falling = false;
		canjump = true;
		row = 0;
	}
	if (velocity.x == 0 && velocity.y == 0 && fire == true)
	{
		dash = false;
		falling = false;
		canjump = true;
		row = 4;
	}
	else
	{
		if (velocity.y < 0 && direction.y <= 0)
		{
			row = 2;
			falling = false;
			if (velocity.x > 0.0f)
			{
				faceleft = false;
			}
			if(velocity.x < 0.0f)
			{
				faceleft = true;
			}		
		}	
		if (velocity.y > 0 && direction.y >= 0)
		{
			row = 2;
			falling = true;
			canjump = false;
			if (velocity.x > 0.0f)
			{
				faceleft = false;
			}
			if (velocity.x < 0.0f)
			{
				faceleft = true;
			}
		}		
		if (velocity.x > 0.0f && velocity.y == 0.0f && dash == false)
		{
			row = 1;
			falling = false;
			faceleft = false;
			dash = false;
			canjump = true;
		}
		if(velocity.x < 0 && velocity.y == 0.0f && dash == false)
		{
			row = 1;
			falling = false;
			faceleft = true;
			dash = false;
			canjump = true;
		}		
	}
	body.move(velocity * deltaTime);
	animation.update(row, deltaTime, faceleft , falling , dash , fire);
	body.setTextureRect(animation.uvRect);		
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		//left
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//right
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		//bottom
		velocity.y = 0.0f;
		canjump = true;
		falling = false;
	}
	else if (direction.y > 0.0f)
	{
		//top
		velocity.y = 0.0f;
	}
}
