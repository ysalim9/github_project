#pragma once 
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;
inline Vector2f normalizezombie(Vector2f vector) {
    float mag = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
    if (mag == 0) return Vector2f(0, 0);
    return Vector2f(vector.x / mag, vector.y / mag);
}

inline float Distance(Vector2f v1, Vector2f v2) {
    return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}
extern Texture zombiespreite;
struct Zombie {
    Sprite shape;
    RectangleShape attackbox;
    Vector2f velocity;
    float attackRange = 40.0f;
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
    void zombieupdate();
    void caluclatngmovementdirection(Vector2f playerPos);
    void ainmationhamdler( );
    void attack_player( FloatRect playerBounds);
    void spawnzombie(int count);
    void zombiehandling();
    void addzombie();
  
       
    
};
extern vector<Zombie> zombielist;
