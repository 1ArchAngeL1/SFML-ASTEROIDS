
#include "GameFunctionals.h"


void asteroid_edge_coll(asteroid & astr,int screenWidth,int screenHeight){
    sf::Vector2f pos = astr.asteroid_get_pos();
    float Radius = astr.get_Radius();
    if(pos.x >= screenWidth + Radius)astr.asteroid_set_pos(Vector2f(-Radius,pos.y));
    if(pos.x <= -Radius)astr.asteroid_set_pos(Vector2f(screenWidth + Radius,pos.y));
    if(pos.y <= -Radius)astr.asteroid_set_pos(Vector2f(pos.x,screenHeight + Radius));
    if(pos.y >= screenHeight + Radius)astr.asteroid_set_pos(Vector2f(pos.x,-Radius));
}


void spaceShip_edgeColl(spaceShip & ship,int screenWidth,int screenHeight){
    sf::Vector2f pos = ship.get_pos();
    if(pos.x >= screenWidth + 15)ship.set_pos(Vector2f(-15,pos.y));
    if(pos.x <= -15)ship.set_pos(Vector2f(screenWidth + 15,pos.y));
    if(pos.y <= -15)ship.set_pos(Vector2f(pos.x,screenHeight + 15));
    if(pos.y >= screenHeight + 15)ship.set_pos(Vector2f(pos.x,-15));
}

bool bullet_coll(bullet & bull,asteroid & aster){
        float Radius = aster.get_Radius();
        sf::Vector2f ast_pos = aster.asteroid_get_pos();
        sf::Vector2f bull_pos = bull.get_position();
        float diff = sqrt(pow(ast_pos.x - bull_pos.x,2) + pow(ast_pos.y - bull_pos.y,2));
        if(diff <= Radius)return true;
        return false;
}

bool spaceShip_coll(spaceShip ship,vector<asteroid> & asteroids){
    for(int i = 0;i < asteroids.size();i++){
        sf::Vector2f pos = asteroids[i].asteroid_get_pos();
        float Radius = asteroids[i].get_Radius();
        sf::Vector2f ship_pos = ship.get_pos();
        if(sqrt(pow(pos.x - ship_pos.x,2) + pow(pos.y - ship_pos.y,2)) < Radius + 10){
            asteroids.erase(asteroids.begin() + i);
             return true;
        }  
    }
    return false;
}










