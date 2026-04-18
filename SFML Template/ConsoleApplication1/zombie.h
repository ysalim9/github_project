#pragma once 
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;
//Vector2f normalize(Vector2f vector) {
//    float mag = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
//    if (mag == 0) return Vector2f(0, 0);
//    return Vector2f(vector.x / mag, vector.y / mag);
//}

float Distance(Vector2f v1, Vector2f v2) {
    return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}
Texture zombiespreite;
struct zombie {
    Sprite shape;
    RectangleShape attackbox;
    Vector2f velocity;
    int health = 100;
    float deathTimer = 0.0f;
    float deathDuration = 1.2f;
    float animTimer = 0;
    float animSwitch = 0.1f;
    float speed = 5;
    int animationrow = 2;
    int animationcol = 0;
    int scale = 2;
    float attackcounter = 0;
    float attacktime = 1;
    bool isattacking = false;
    bool isdead = false;

    void Startzombie();
    void ainmationhamdler();
    void attackplayer(FloatRect playerBounds);
    void zombiehandling();
    void addzombie();
  
       
    
};
vector<zombie> zombielist;
