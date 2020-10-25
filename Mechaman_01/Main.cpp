#include <SFML/Graphics.hpp>
#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<vector>
#include "Player.h"
#include"Platform.h"
#include"Bullet.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1080, 720), "Mechaman_01", sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1080.0f, 720.0f));
    sf::RectangleShape background(sf::Vector2f(7000.0f, 720.0f));
    background.setPosition(0.0f, 0.0f);
    sf::Texture bg;
    bg.loadFromFile("BG/stage1.png");
    background.setTexture(&bg);
    //--------test----------
    sf::RectangleShape test(sf::Vector2f(284.0f, 177.0f));
    test.setPosition(540.0f, 720.0f);
    sf::Texture t;
    t.loadFromFile("char/test.jfif");
    test.setTexture(&t);
    //--------test----------
    sf::Texture x;
    x.loadFromFile("char/sprite.png");
    Player player(&x, sf::Vector2u(15, 5), 0.1f, 300.0f, 220.0f);

    sf::Texture BULLET;
    BULLET.loadFromFile("char/bullet.png");
    Bullet bullet1(&BULLET, sf::Vector2u(5, 1), 0.1f, 750.0f, player.GetPosition());
    Bullet bullet2(&BULLET, sf::Vector2u(5, 1), 0.1f, 750.0f, player.GetPosition());
    Bullet bullet3(&BULLET, sf::Vector2u(5, 1), 0.1f, 750.0f, player.GetPosition());
    Bullet bullet4(&BULLET, sf::Vector2u(5, 1), 0.1f, 750.0f, player.GetPosition());

    std::vector<Platform> platforms;

    platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(100.0f, 720.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 535.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(1050.0f, 200.0f), sf::Vector2f(1200.0f, 500.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(1825.0f, 700.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 720.0f), sf::Vector2f(-50.0f, 360.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(260.0f, 200.0f), sf::Vector2f(2000.0f, 535.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(260.0f, 200.0f), sf::Vector2f(2130.0f, 700.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(1300.0f, 200.0f), sf::Vector2f(2940.0f, 535.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(120.0f, 200.0f), sf::Vector2f(3640.0f, 500.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(600.0f, 200.0f), sf::Vector2f(3800.0f, 700.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(120.0f, 200.0f), sf::Vector2f(4140.0f, 500.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(800.0f, 200.0f), sf::Vector2f(4600.0f, 650.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(120.0f, 200.0f), sf::Vector2f(4560.0f, 500.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(600.0f, 200.0f), sf::Vector2f(5200.0f, 700.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(85.0f, 200.0f), sf::Vector2f(5185.0f, 650.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(120.0f, 200.0f), sf::Vector2f(5430.0f, 650.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(100.0f, 200.0f), sf::Vector2f(5540.0f, 450.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(120.0f, 200.0f), sf::Vector2f(3510.0f, 450.0f)));
    //--------top side---------
    platforms.push_back(Platform(nullptr, sf::Vector2f(1950.0f, 100.0f), sf::Vector2f(4575.0f, 30.0f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(120.0f, 200.0f), sf::Vector2f(4140.0f, 70.0f)));
    bool faceleft , falling , dash;
    
    float deltaTime = 0.0f;
    sf::Clock clock;
    int Bul[4];
    for (int i = 0; i < 4; i++)
    {
        Bul[i] = 0;
    }
    faceleft = false;
    falling = false;
    dash = false;

    while (window.isOpen())
    {       
        deltaTime = clock.restart().asSeconds();
        if (deltaTime > 1.0f / 20.0f)
            deltaTime = 1.0f / 20.0f;

        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                std::cout << "Width: " << evnt.size.width << "Height: " << evnt.size.height << std::endl;
                break;
            }
        }

        //player.update(deltaTime);
        //-----test-----
        test.move(0.0f, -100.0f * deltaTime);
        if (test.getPosition().y < -200.0f)
        {
            test.setPosition(540.0f, 720.0f);
        }
        //----------test--------------

        sf::Vector2f direction;

        for (Platform& platform : platforms)
            if (platform.GetCollider().collision(player.GetCollider(), direction, 1.0f))
                player.OnCollision(direction);

        player.update(deltaTime, direction);

        view.setCenter(sf::Vector2f(player.GetPosition()));
        if (view.getCenter().x - 540.0f <= 0.0f)
        {           
            if (view.getCenter().y - 360.0f <= 0.0f)
            {
                view.setCenter(sf::Vector2f(540.0f, 360.0f));
            }
            if (view.getCenter().y + 360.0f >= 720.0f)
            {
                view.setCenter(sf::Vector2f(540.0f, 360.0f));
            }
        }
        if (view.getCenter().x + 540.0f >= 7000.0f)
        {
            if (view.getCenter().y - 360.0f <= 0.0f)
            {
                view.setCenter(sf::Vector2f(6460.0f, 360.0f));
            }
            if (view.getCenter().y + 360.0f >= 720.0f)
            {
                view.setCenter(sf::Vector2f(6460.0f, 360.0f));
            }
        }
        if (view.getCenter().x - 540.0f > 0.0f && view.getCenter().x + 540.0f < 7000.0f)
        {
            if (view.getCenter().y - 360.0f <= 0.0f)
            {
                view.setCenter(sf::Vector2f(player.GetPosition().x, 360.0f));
            }
            if (view.getCenter().y + 360.0f >= 720.0f)
            {
                view.setCenter(sf::Vector2f(player.GetPosition().x, 360.0f));
            }
        }

        std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;
        std::cout << Bul[0]<< " " << Bul[1] << " " << Bul[2] << " " << Bul[3] << " " << faceleft  << std::endl;
        window.clear();
        window.setView(view);
        window.draw(background);
        window.draw(test); //-----test--------
        for (Platform& platform : platforms)
        {
            platform.Draw(window);
        }
        //window.draw(background);       
        player.draw(window);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            faceleft = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            faceleft = false;
        }
        for (int i = 0;i < 4;i++) 
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
            {
                if (faceleft == false && Bul[i] == 0)
                {
                    if(i == 0)
                    {
                        bullet1.attackR(player.GetPosition());
                    }  
                    if (i == 1)
                    {
                        bullet2.attackR(player.GetPosition());
                    }
                    if (i == 2)
                    {
                        bullet3.attackR(player.GetPosition());
                    }
                    if (i == 3)
                    {
                        bullet4.attackR(player.GetPosition());
                    }
                    Bul[i] = 1;
                }
                if (faceleft == true && Bul[i] == 0)
                {
                    if (i == 0)
                    {
                        bullet1.attackL(player.GetPosition());
                    }
                    if (i == 1)
                    {
                        bullet2.attackL(player.GetPosition());
                    }
                    if (i == 2)
                    {
                        bullet3.attackL(player.GetPosition());
                    }
                    if (i == 3)
                    {
                        bullet4.attackL(player.GetPosition());
                    }
                    Bul[i] = -1;
                }
                break;
            }
        }
        if (Bul[0] == 1)
        {
            bullet1.updateR(deltaTime);
            bullet1.draw(window);
        }
        if (Bul[0] == -1)
        {
            bullet1.updateL(deltaTime);
            bullet1.draw(window);
        }
        if (Bul[1] == 1)
        {
            bullet1.updateR(deltaTime);
            bullet1.draw(window);
        }
        if (Bul[1] == -1)
        {
            bullet1.updateL(deltaTime);
            bullet1.draw(window);
        }if (Bul[2] == 1)
        {
            bullet1.updateR(deltaTime);
            bullet1.draw(window);
        }
        if (Bul[2] == -1)
        {
            bullet1.updateL(deltaTime);
            bullet1.draw(window);
        }if (Bul[3] == 1)
        {
            bullet1.updateR(deltaTime);
            bullet1.draw(window);
        }
        if (Bul[3] == -1)
        {
            bullet1.updateL(deltaTime);
            bullet1.draw(window);
        }
        if (abs(bullet1.GetPosition().x - view.getCenter().x) >= 600.0f)
        {
            Bul[0] = 0;
            bullet1.isAvaliable();
        }
        if (abs(bullet2.GetPosition().x - view.getCenter().x) >= 600.0f)
        {
            Bul[1] = 0;
            bullet2.isAvaliable();
        }
        if (abs(bullet3.GetPosition().x - view.getCenter().x) >= 600.0f)
        {
            Bul[2] = 0;
            bullet3.isAvaliable();
        }
        if (abs(bullet4.GetPosition().x - view.getCenter().x) >= 600.0f)
        {
            Bul[3] = 0;
            bullet4.isAvaliable();
        }
        window.display();     
    }
    return 0;
}