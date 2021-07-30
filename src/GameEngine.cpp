#include "GameEngine.h"



float asteroid::get_Radius(){
    return Radius;
}

void asteroid::rotate(){
    if(rotation_dir) aster.rotate(10);
    else aster.rotate(-10);
}

sf::Vector2f asteroid::asteroid_get_pos(){
    return aster.getPosition();
}

sf::Vector2f asteroid::get_direction(){
    return direction;
}

void asteroid::draw(sf::RenderWindow & window){
    window.draw(aster);
}

void asteroid::move_asteroid(){
    sf::Vector2f dir;
    dir.x = speed * direction.x;
    dir.y = speed * direction.y;
    aster.move(dir);
}

void asteroid::asteroid_set_pos(sf::Vector2f vec){
    aster.setPosition(vec);
}
void asteroid::set_speed(float speed){
    asteroid::speed = speed;
}

float asteroid::get_speed(){
   return speed;
}



void bullet::move(){
    sf::Vector2f move_vec;
    move_vec.x = 15 * direction.x;
    move_vec.y = 15 * direction.y;
    rocket.move(direction);
}

Vector2f bullet::get_position(){
    return rocket.getPosition();
}
 void bullet::bullet_draw(sf::RenderWindow & window){
     window.draw(rocket);
 }

void spaceShip::draw_spaceShip(sf::RenderWindow & window){
    window.draw(ship);
}
void spaceShip::rotate_spaceShip(float angle){
    rotation += angle;
    ship.rotate(-angle);
    rotation = rotation % 360;
    direction.x = cos(rotation * pi/180);
    direction.y = -sin(rotation * pi/180);
}
void spaceShip::move_spaceShip(float time){
    sf::Vector2f temp;
    temp.x = move_direction.x * velocity * time;
    temp.y = move_direction.y * velocity * time;
    ship.move(temp);
}
void spaceShip::set_acceleration(float acceleration){
    spaceShip::acceleration = acceleration;
}
void spaceShip::set_velocity(float velocity){
    spaceShip::velocity = velocity;
}

float spaceShip::get_acceleration(){
    return acceleration;
}
float spaceShip::get_velocity(){
    return velocity;
}
void spaceShip::fire_bullet(){

}

sf::Vector2f spaceShip::get_direction(){
    return direction;
}

void spaceShip::set_direction(const sf::Vector2f dir){
    move_direction.x = dir.x;
    move_direction.y = dir.y;
}

sf::Vector2f spaceShip::get_Bullet_xy(){
    Vector2f origin = ship.getPosition();
    Vector2f diff = direction;
    diff.x = 15 * diff.x - 3;
    diff.y = 15 * diff.y - 6;
    origin = origin + diff;
    return origin;
}


 sf::Vector2f spaceShip::get_pos(){
     return ship.getPosition();
 }


  void spaceShip::set_pos(const sf::Vector2f vec){
      ship.setPosition(vec);
  }