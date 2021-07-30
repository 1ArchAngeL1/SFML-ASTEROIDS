
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameEngine.h"
#include "GameFunctionals.h"

#include "input.h"
#include <iostream>
#include <math.h>

#define pi 3.14159265
#define ScreenWidth 1080
#define ScreenHeight 720

const float ammo_R = 3;
int score = 0;
int lives = 3;



int main(){
    vector<sf::CircleShape> stars;
    for(int i = 0;i < 100;i++){
        sf::CircleShape star(1);
        star.setFillColor(sf::Color::White);
        float x = rand() % ScreenWidth;
        float y = rand() % ScreenHeight;
        star.setPosition(Vector2f(x,y));
        stars.push_back(star);
    }
    sf::SoundBuffer thrustBuffer;
    thrustBuffer.loadFromFile("thrust.wav");
    sf::Sound thrust_sound;
    thrust_sound.setBuffer(thrustBuffer);
    srand(time(nullptr));
    sf::SoundBuffer explosionBuffer;
    explosionBuffer.loadFromFile("bangMedium.wav");
    sf::Sound exp_sound;
    exp_sound.setBuffer(explosionBuffer);
    sf::SoundBuffer shootBuffer;
    shootBuffer.loadFromFile("fire.wav");
    sf::Sound shootSound;
    shootSound.setBuffer(shootBuffer);
    sf::RenderWindow window(sf::VideoMode(ScreenWidth,ScreenHeight), "SFML-ASTEROIDS!");
    spaceShip ship(ScreenWidth,ScreenHeight);
    sf::Text scoreBoard;
    sf::Font myFont;
    sf::Text livesBoard;
    livesBoard.setFont(myFont);
    livesBoard.setFillColor(Color::White);
    livesBoard.setString("Lives: " + to_string(lives));
    livesBoard.setPosition(120,10);
    livesBoard.scale(sf::Vector2f(0.5f,0.5f));
    myFont.loadFromFile("fonti.ttf");
    scoreBoard.setFont(myFont);
    scoreBoard.setFillColor(sf::Color::White);
    scoreBoard.setString("Score: " + to_string(score));
    scoreBoard.setPosition(10,10);
    scoreBoard.scale(sf::Vector2f(0.5f,0.5f));
    float delay = 0.035f;
    sf::Clock clock;
    float chrono = 0;
    ship.set_acceleration(-7);
    bool move = false;
    std::vector<bullet> bullets;
    std::vector<asteroid> asteroids;
    Clock clock2;
    float chrono2 = 0;
    float delay2 = 0.001f;
    Clock clock3;
    float chrono3 = 0;
    float delay3 = 3.5;
    sf::Text menu_Start;
    menu_Start.setFont(myFont);
    menu_Start.setString("START GAME");
    menu_Start.setFillColor(Color::Magenta);
    menu_Start.setScale(sf::Vector2f(1.5,1.5));
    menu_Start.setPosition(sf::Vector2f(ScreenWidth/2-170,ScreenHeight/2-100));
    sf::Text menu_exit;
    menu_exit.setFont(myFont);
    menu_exit.setString("QUIT GAME");
    menu_exit.setScale(sf::Vector2f(1.5f,1.5f));
    menu_exit.setFillColor(sf::Color::White);
    menu_exit.setPosition(sf::Vector2f(ScreenWidth/2 - 150,ScreenHeight/2));
    sf::Text menu_logo;
    menu_logo.setFont(myFont);
    menu_logo.setString("ASTEROIDS");
    menu_logo.setScale(sf::Vector2f(2.f,2.f));
    menu_logo.setFillColor(sf::Color::Yellow);
    menu_logo.setPosition(sf::Vector2f(ScreenWidth/2 - 200,ScreenHeight/10));
    sf::Music mus;
    mus.openFromFile("menuMus.wav");
    mus.setLoop(true);
    mus.play();
    int index = 0;
    A:
    while(window.isOpen()){
        Input::Listen();
        sf::Event event;
        while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed)
            window.close();
            break;
        }
        if(Input::Pressed(sf::Keyboard::Down)){
            if(index != 1){
                index++;
                menu_exit.setFillColor(Color::Magenta);
                menu_Start.setFillColor(Color::White);
            }
        }
        if(Input::Pressed(sf::Keyboard::Up)){
            if(index != 0){
                index--;
                menu_exit.setFillColor(Color::White);
                menu_Start.setFillColor(Color::Magenta);
            }
        }
        if(Input::Pressed(sf::Keyboard::Enter)){
            if(index == 0){
                mus.stop();
                break;
            }else{
                return 0;
            }
        }
        window.clear();
        for(int i = 0;i < stars.size();++i)window.draw(stars[i]);
        window.draw(menu_Start);
        window.draw(menu_exit);
        window.draw(menu_logo);
        window.display();
    }
    while (window.isOpen()){
        for(int i = 0;i < bullets.size();i++){
            Vector2f cords = bullets[i].get_position();
            if(cords.x < 0 || cords.x > ScreenWidth || cords.y < 0 || cords.y > ScreenHeight)bullets.erase(bullets.begin() + i);
        }
        chrono2 += clock2.getElapsedTime().asSeconds();
        clock2.restart();
        chrono += clock.getElapsedTime().asSeconds();
        clock.restart();
        chrono3 += clock3.getElapsedTime().asSeconds();
        clock3.restart();
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(chrono >= delay){
             Input::Listen();
            chrono = 0;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                ship.rotate_spaceShip(-7);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                ship.rotate_spaceShip(7);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                 thrust_sound.play();
                ship.set_velocity(130);
                sf::Vector2f dir = ship.get_direction();
                ship.set_direction(dir);
                move = true;
            }
            if(Input::Pressed(sf::Keyboard::Space)){
                bullet new_bullet(ship.get_Bullet_xy(),ammo_R,ship.get_direction());
                bullets.push_back(new_bullet);
                shootSound.play();
            }
            if(ship.get_velocity() > 70)
            ship.set_velocity((float)ship.get_velocity() + ship.get_acceleration());
            if(move)ship.move_spaceShip(delay);
            spaceShip_edgeColl(ship,ScreenWidth,ScreenHeight);
            for(int i = 0;i < asteroids.size();++i)asteroids[i].move_asteroid();
            for(int i = 0;i < asteroids.size();++i)asteroids[i].rotate(),asteroid_edge_coll(asteroids[i],ScreenWidth,ScreenHeight);
            if(spaceShip_coll(ship,asteroids)){
                exp_sound.play();
                lives--;
                if(lives < 0){
                   break;
                }
                livesBoard.setString("Lives: " + to_string(lives));
            }
        }
        if(chrono2 >= delay2){
            chrono2 = 0;
            for(int i = 0;i < bullets.size();++i)bullets[i].move();
        }
        if(chrono3 >= delay3){
            chrono3 = 0;
            asteroid astr(rand() % 40 + 20);
            sf::Vector2f dir = astr.get_direction();
            if(dir.x < 0)astr.asteroid_set_pos(Vector2f(ScreenWidth + astr.get_Radius(),rand() % 600 + 200));
            if(dir.x > 0)astr.asteroid_set_pos(Vector2f(-astr.get_Radius(),rand() % 600 + 200));
            asteroids.push_back(astr);
        }
        for(int i = 0;i < asteroids.size();i++){
                for(int j = 0;j < bullets.size();j++){
                    if(bullet_coll(bullets[j],asteroids[i])){
                        score++;
                        exp_sound.play();
                        bullets.erase(bullets.begin() + j);
                        float Rad = asteroids[i].get_Radius();
                        sf::Vector2f pos = asteroids[i].asteroid_get_pos();
                        float old_speed = asteroids[i].get_speed();
                        asteroids.erase(asteroids.begin() + i);
                        if(Rad/2.f > 10){
                            asteroid ast_1(Rad/2);
                            asteroid ast_2(Rad/2);
                            ast_1.set_speed(2 * old_speed);
                            ast_1.asteroid_set_pos(sf::Vector2f(pos.x,pos.y + Rad/2));
                            ast_2.set_speed(2 * old_speed);
                            ast_2.asteroid_set_pos(sf::Vector2f(pos.x,pos.y - Rad/2));
                            asteroids.push_back(ast_1);
                            asteroids.push_back(ast_2);
                        }
                    }
                }
            }
        scoreBoard.setString("Score: " + to_string(score));
        window.clear();
        for(int i = 0;i < stars.size();++i)window.draw(stars[i]);
        for(int i = 0;i < bullets.size();++i)bullets[i].bullet_draw(window);
        for(int i = 0;i < asteroids.size();++i)asteroids[i].draw(window);
        ship.draw_spaceShip(window);
        window.draw(scoreBoard);
        window.draw(livesBoard);
        window.display();
    }
    return 0;
}