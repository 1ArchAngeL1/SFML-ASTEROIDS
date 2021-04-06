#ifndef GAMEFUNCTIONALS_H
#define GAMEFUNCTIONALS_H

#include "GameEngine.h"


void asteroid_edge_coll(asteroid & astr,int screenWidth,int screenHeight);

void spaceShip_edgeColl(spaceShip & ship,int screenWidth,int screenHeight);

bool bullet_coll(bullet& bull,asteroid& aster);

bool spaceShip_coll(spaceShip ship,vector<asteroid> & asteroids);






















#endif