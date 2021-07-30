#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#define pi 3.14159265

#include <SFML/Graphics.hpp>
#include <random>
#include <math.h>
#include <iostream>

using namespace std;

using namespace sf;

class asteroid{
private:
    sf::ConvexShape aster;
    sf::Vector2f direction;
    float Radius;
    bool rotation_dir;
    float speed;
public:
    asteroid(int Rad){
        speed = 3;
        rotation_dir = rand() % 1 + 0;
        Radius = Rad;
        srand(time(nullptr));
        float alpha = rand() % 360;
        direction.x = cos(alpha * pi/180);
        direction.y = sin(alpha * pi/180);
        aster.setPointCount(19);
        for(int i = 0;i < 19;i++){
            aster.setPoint(i,Vector2f(Rad * cos(20*i*pi/180.f),(Rad - (rand() % 15)) *sin(20 * i * pi/180)));
        }
        std::cout << aster.getOrigin().x << endl;
        std::cout << aster.getOrigin().y << endl;
        aster.setFillColor(Color::Black);
        aster.setOutlineThickness(1);
        aster.setOutlineColor(sf::Color::Yellow);
    }
    
    void draw(sf::RenderWindow & window);
    void move_asteroid();
    void asteroid_set_pos(sf::Vector2f vec);
    sf::Vector2f asteroid_get_pos();
    sf::Vector2f get_direction();
    float get_Radius();
    void rotate();
    void set_speed(float speed);
    float get_speed();
};


class bullet{
private:
    sf::CircleShape rocket;
    sf::Vector2f direction;
public:
    bullet(sf::Vector2f vec,float R,sf::Vector2f dir){
        rocket.setFillColor(sf::Color::Red);
        rocket.setRadius(R);
        rocket.setPosition(vec);
        direction.x = dir.x;
        direction.y = dir.y;
    }
    void move();
    void bullet_draw(sf::RenderWindow & window);
    Vector2f get_position();
};

class spaceShip{
private:
    sf::ConvexShape ship;
    sf::Vector2f direction;
    sf::Vector2f move_direction;
    int rotation;
    float acceleration;
    float velocity;
public:
    spaceShip(float ScreenWidth,float ScreenHeight){
        acceleration = 0;
        velocity = 0;
        direction.x = 0;
        direction.y = -1;
        move_direction.x = direction.x;
        move_direction.y = direction.y;
        rotation = 90;
        ship.setPointCount(4);
        ship.setPoint(0,sf::Vector2f(0,0));
        ship.setPoint(1,sf::Vector2f(15,-30));  
        ship.setPoint(2,sf::Vector2f(30,0));  
        ship.setPoint(3,sf::Vector2f(15,-5));     
        ship.setOutlineThickness(1);
        ship.setOutlineColor(sf::Color(148,255,185));
        ship.setFillColor(sf::Color::Black);
        ship.setPosition(sf::Vector2f(ScreenWidth/2.f,ScreenHeight/2.f));
        ship.setOrigin(15.f,-15.f);
    }
    void draw_spaceShip(sf::RenderWindow & window);
    void rotate_spaceShip(float angle);
    void move_spaceShip(float time);
    void set_acceleration(float acceleration);
    void set_velocity(const float velocity);
    float get_acceleration();
    float get_velocity();
    void fire_bullet();
    sf::Vector2f get_direction();
    void set_direction(sf::Vector2f dir);
    sf::Vector2f get_Bullet_xy();
    sf::Vector2f get_pos();
    void set_pos(const sf::Vector2f vec);
};

#endif