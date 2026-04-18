#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

#define pistlofirerate 1.0f
#define pistlodamage 25
#define riflofirerate 0.5f
#define riflodamage 15
inline Vector2f normalize(Vector2f vector) {
    float mag = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
    if (mag == 0) return Vector2f(0, 0);
    return Vector2f(vector.x / mag, vector.y / mag);
}

enum weopan { pistlo, rifle };

struct Bullet {
    RectangleShape shape;
    int damage;
    Vector2f velocity;

    void updatebullet(float deltaTime) {
        shape.move(velocity * deltaTime);
    }
    void bullethandling(float dt);
};

struct Character {
    Sprite players;
    float animTimer = 0;
    bool isdamage = false;
    bool isdead = false;
    float damageTimer = 0;
    int frameCounter = 0;
    int currant_halthe = 100;
    Vector2f deathVelocity;
    bool isMoving = false;
    bool isDoingAction = false;
    bool facingRight = true;

    void Startplayer();
    void Drawplayer(RenderWindow& window);
    void Updateplayer(float dt, RenderWindow& window);
    void playermovement(float dt);
    void playeranimation();
    void playercollieer(float dt);
    void calculuting(RenderWindow& window);
};

extern vector<Bullet> bullets;
extern RectangleShape copyplayer;
extern RectangleShape re1, re2, gun;
extern CircleShape circle;
extern Texture mario;

extern bool up, down, a, d;
extern int colum;
extern Vector2f aimdirection;
extern float playersdpeed;
extern weopan currentweopon;
extern float shoottimer;
extern float currentfirerate;
extern int currentdamage;
extern int pistolAmmoLoaded;
extern int rifleAmmoLoaded;
extern int currentammo;
extern bool isZPressed;

