#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;	
	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);

}

Animation::~Animation()
{
}

void Animation::update(int row, float deltaTime, bool faceleft , bool falling , bool dash , bool fire)
{
	currentImage.y = row;
	totalTime += deltaTime;	
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;
		if (row == 2)
		{
			imageCount.x = 11;
		}
		if (falling == true)
		{
			row = 2;
			currentImage.x = 7;
		}
		if (fire == true)
		{
			row = 4;
		}
		if (row == 3 && dash != false)
		{						
			if (currentImage.x >= 5)
			{
				currentImage.x = 2;
			}	
		}
		if (row == 4)
		{
			imageCount.x = 5;
		}
		if (currentImage.x >= imageCount.x)
		{					
			currentImage.x = 0;
		}
	}
	uvRect.top = currentImage.y * uvRect.height;
	if (faceleft)
	{
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (currentImage.x+1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}

void Animation::updateBu(int row, float deltaTime, bool faceleft)
{
	currentImage.y = row;
	totalTime += deltaTime;
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;	
		if (row == 0)
		{
			imageCount.x = 5;
		}
		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}
	uvRect.top = currentImage.y * uvRect.height;
	if (faceleft)
	{
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}


