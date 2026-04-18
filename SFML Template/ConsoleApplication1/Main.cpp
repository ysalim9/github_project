#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <ctime>
#include "zombie.h"
#include "player.h"
#include <fstream>
#include <SFML/Audio.hpp>
#include <iomanip>

using namespace std;
using namespace sf;
Character  player;
Bullet bullet; 
//----------------------------------shapes and variables-----------------------//
//int colum = 0;
View view(sf::FloatRect(0, 0, 1000, 800));
sf::RenderWindow window(sf::VideoMode(1080, 1050), "Zombies Project - Clean Version");

//RectangleShape copyplayer(Vector2f(124 / 4, 128 / 2));
//RectangleShape re1(Vector2f(100, 100)), re2(Vector2f(100, 100));
//RectangleShape gun(Vector2f(25, 10));
//CircleShape circle(10.f);
Sprite background;
Texture texturebacground;
float dt;
//Sprite player;
//Vector2f aimdirection;
//Texture mario;

//----------------------------------------------guns variables------------------------------------------------------//
//enum weopan { pistlo, rifle };
//weopan currentweopon = pistlo;
//#define pistlofirerate 1.0f
//#define pistlodamage 25
//#define riflofirerate 0.5f
//#define riflodamage 15 
//
//float shoottimer = 0;
//float currentfirerate = pistlofirerate;
//int currentdamage = pistlodamage;
//
//int pistolAmmoLoaded = 8;
//int rifleAmmoLoaded = 30;
//float playersdpeed = 300.f;
//int currentammo = 8;
//bool isZPressed = false;

//----------------------------------functions prototypes-----------------------------//
void Start();
void Draw();
void Update(float dt);
//----------------------------------bullet structure----------------------//



//---------------------------------zombie structure----------------------------------//
//Vector2f normalize(Vector2f vector) {
//    float mag = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
//    if (mag == 0) return Vector2f(0, 0);
//    return Vector2f(vector.x / mag, vector.y / mag);
//}
//
//float Distance(Vector2f v1, Vector2f v2) {
//    return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
//}
//
//Texture zombiespreite;
//Texture zombiespreite2;
//struct zombie {
//    Sprite shape;
//    RectangleShape attackbox;
//    Vector2f velocity;
//    int health = 100;
//    float deathTimer = 0.0f;
//    float deathDuration = 1.2f;
//    float animTimer = 0;
//    float animSwitch = 0.1f;
//    float speed = 5;
//    int animationrow = 2;
//    int animationcol = 0;
//    int scale = 2;
//    float attackcounter = 0;
//    float attacktime = 1;
//    bool isattacking = false;
//    bool isdead = false;
//
//    void Startzombie() {
//        shape.setTexture(zombiespreite);
//        shape.setTextureRect(IntRect(0, 2 * 32, 32, 32));
//        attackbox.setSize(Vector2f(50, 50));
//        attackbox.setOrigin(attackbox.getLocalBounds().width / 2, attackbox.getLocalBounds().height / 2);
//        shape.setOrigin(32 / 2, 32 / 2);
//        shape.setScale(scale, scale);
//    }
//
//    void caluclatngmovementdirection(Vector2f playerPos) {
//        velocity = playerPos - shape.getPosition();
//        velocity = normalize(velocity) * speed;
//    }
//
//    void ainmationhamdler() {
//        animTimer += deltaTime;
//        if (animTimer >= animSwitch) {
//            animTimer = 0;
//            if (isdead) {
//                animationrow = 3;
//                if (animationcol < 12) animationcol++;
//                else animationcol = 12;
//            }
//            else if (isattacking) {
//                animationrow = 1;
//                animationcol = (animationcol + 1) % 7;
//            }
//            else {
//                animationrow = 2;
//                animationcol = (animationcol + 1) % 8;
//            }
//            shape.setTextureRect(IntRect(animationcol * 32, animationrow * 32, 32, 32));
//
//            if (shape.getPosition().x > player.getPosition().x) shape.setScale(-scale, scale);
//            else shape.setScale(scale, scale);
//        }
//    }
//
//    void attackplayer(FloatRect playerBounds) {
//        if (attackbox.getGlobalBounds().intersects(playerBounds)) {
//            isattacking = true;
//            attackcounter += deltaTime;
//            if (attackcounter >= attacktime) {
//                attackcounter = 0;
//                cout << "hit player!" << endl;
//            }
//        }
//        else isattacking = false;
//    }
//};
//vector<zombie> zombielist;
//vector<zombie> zombielist2;

int main() {
    srand(static_cast<unsigned>(time(0)));
    Start();
    Clock clock;
    while (window.isOpen()) {
        dt = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        Update(dt); 
        Draw();
    }
    return 0;
}

void Start() {
    //zombiespreite.loadFromFile("zombie.png");
    ////zombiespreite2.loadFromFile("zombie2.png");
    //mario.loadFromFile("mario.png");
    //player.setTexture(mario);
    //player.setTextureRect(IntRect(44, 2 * 62, 44, 62));
    //player.setPosition(205, 205);
    //player.setScale(1, 1);
    //player.setOrigin(player.getLocalBounds().width / 2, player.getLocalBounds().height / 2);
    //gun.setOrigin((gun.getLocalBounds().width / 2) - 100, gun.getLocalBounds().height / 2);
    //circle.setOrigin(circle.getLocalBounds().width / 2, circle.getLocalBounds().height / 2);
    //re1.setPosition(1000, 250);
    //re2.setPosition(250, 250);

    window.setMouseCursorVisible(false);
    //copyplayer.setOrigin(copyplayer.getLocalBounds().width / 2, copyplayer.getLocalBounds().height / 2);
    player.Startplayer();
    if (texturebacground.loadFromFile("background2.png")) {
        texturebacground.setRepeated(true);
        background.setTexture(texturebacground);
        background.setTextureRect(IntRect(0, 0, 1000, 800));
        background.setOrigin(500, 400);
    }
}

void Update(float dt) {
    player.Updateplayer(dt, window);
    bullet.bullethandling(dt);
    view.setCenter(player.players.getPosition());
    background.setPosition(player.players.getPosition());
    int mapx = static_cast<int>(player.players.getPosition().x);
    int mapy = static_cast<int>(player.players.getPosition().y);
    background.setTextureRect(IntRect(mapx, mapy, 1000, 800));

    //playermovement();
    //calculuting();
    //shooting();
    //bullethandling();
    //zombiehandling();
    //playercollieer();
    //switchwepoans();
    //reload();
    //addzombie();
    //playeranimation();
}

//void playermovement() {
//    up = false; down = false; a = false; d = false;
//    if (Keyboard::isKeyPressed(Keyboard::W)) { player.move(0, -playersdpeed * deltaTime); up = true; }
//    if (Keyboard::isKeyPressed(Keyboard::S)) { player.move(0, playersdpeed * deltaTime); down = true; }
//    if (Keyboard::isKeyPressed(Keyboard::D)) { player.move(playersdpeed * deltaTime, 0); d = true; }
//    if (Keyboard::isKeyPressed(Keyboard::A)) { player.move(-playersdpeed * deltaTime, 0); a = true; }
//}

    //void playeranimation() {
    //    if (up) { colum = (colum + 1) % 12; player.setTextureRect(IntRect(colum * 44, 3 * 62, 44, 62)); }
    //    else if (down) { colum = (colum + 1) % 12; player.setTextureRect(IntRect(colum * 44, 0 * 62, 44, 62)); }
    //    else if (d) { colum = (colum + 1) % 12; player.setTextureRect(IntRect(colum * 44, 2 * 62, 44, 62)); }
    //    else if (a) { colum = (colum + 1) % 12; player.setTextureRect(IntRect((colum + 1) * 44, 1 * 62, -44, 62)); }
    //}

//void playercollieer() {
//
//    if (copyplayer.getGlobalBounds().intersects(re2.getGlobalBounds())) {
//        if (Keyboard::isKeyPressed(Keyboard::W)) player.move(0, playersdpeed * deltaTime);
//        if (Keyboard::isKeyPressed(Keyboard::S)) player.move(0, -playersdpeed * deltaTime);
//        if (Keyboard::isKeyPressed(Keyboard::D)) player.move(-playersdpeed * deltaTime, 0);
//        if (Keyboard::isKeyPressed(Keyboard::A)) player.move(playersdpeed * deltaTime, 0);
//    }
//
//
//    for (int i = 0; i < bullets.size(); i++) {
//        bool bulletRemoved = false;
//
//
//        if (bullets[i].shape.getGlobalBounds().intersects(re2.getGlobalBounds())) {
//            bullets.erase(bullets.begin() + i);
//            i--;
//            continue;
//        }
//
//        for (int j = 0; j < zombielist.size(); j++) {
//            if (!zombielist[j].isdead && bullets[i].shape.getGlobalBounds().intersects(zombielist[j].shape.getGlobalBounds())) {
//                zombielist[j].health -= bullets[i].damage;
//                bullets.erase(bullets.begin() + i);
//                i--;
//                bulletRemoved = true;
//                break;
//            }
//        }
//    }
//}

//void calculuting() {
//    Vector2i mouseposscreen = Mouse::getPosition(window);
//    Vector2f mouseworldposition = window.mapPixelToCoords(mouseposscreen);
//    circle.setPosition(mouseworldposition);
//    aimdirection = mouseworldposition - player.getPosition();
//    gun.setRotation(atan2(aimdirection.y, aimdirection.x) * 180 / 3.14159f);
//    aimdirection = normalize(aimdirection);
//    gun.setPosition(player.getPosition());
//    copyplayer.setPosition(player.getPosition());
//}

//void shooting() {
//    shoottimer += deltaTime;
//    if (Mouse::isButtonPressed(Mouse::Left) && shoottimer >= currentfirerate && currentammo > 0) {
//        shoottimer = 0;
//        currentammo--;
//        if (currentweopon == pistlo) pistolAmmoLoaded = currentammo;
//        else rifleAmmoLoaded = currentammo;
//
//        Bullet newbullet;
//        newbullet.shape.setSize(Vector2f(10, 5));
//        newbullet.shape.setFillColor(Color::Cyan);
//        newbullet.shape.setPosition(gun.getPosition());
//        newbullet.shape.setRotation(gun.getRotation());
//        newbullet.damage = currentdamage;
//        newbullet.velocity = aimdirection * 800.0f;
//        bullets.push_back(newbullet);
//    }
//}
//
//void bullethandling() {
//    for (int i = 0; i < bullets.size(); i++) bullets[i].Update(deltaTime);
//}

//void zombiehandling() {
//    float personalSpace = 50.0f;
//    float separationStrength = 40.0f;
//
//    for (int i = 0; i < (int)zombielist.size(); i++) {
//        if (zombielist[i].health <= 0 && !zombielist[i].isdead) {
//            zombielist[i].isdead = true;
//            zombielist[i].speed = 0;
//        }
//
//        if (zombielist[i].isdead) {
//            zombielist[i].deathTimer += deltaTime;
//            zombielist[i].ainmationhamdler();
//            if (zombielist[i].deathTimer >= zombielist[i].deathDuration) {
//                zombielist.erase(zombielist.begin() + i);
//                i--;
//            }
//            continue;
//        }
//
//        zombielist[i].caluclatngmovementdirection(player.getPosition());
//
//        Vector2f separationforce(0.0f, 0.0f);
//        for (int j = 0; j < zombielist.size(); j++) {
//            if (i == j || zombielist[j].isdead) continue;
//            float dist = Distance(zombielist[i].shape.getPosition(), zombielist[j].shape.getPosition());
//            if (dist < personalSpace && dist > 0) {
//                separationforce += (zombielist[i].shape.getPosition() - zombielist[j].shape.getPosition()) / dist;
//            }
//        }
//
//        zombielist[i].velocity = normalize(zombielist[i].velocity + separationforce * separationStrength) * zombielist[i].speed;
//        zombielist[i].attackplayer(copyplayer.getGlobalBounds());
//        zombielist[i].ainmationhamdler();
//        zombielist[i].shape.move(zombielist[i].velocity * (deltaTime * 20.f));
//        zombielist[i].attackbox.setPosition(zombielist[i].shape.getPosition());
//    }
//}

//void spawnzombie(int count) {
//    for (int i = 0; i < count; i++) {
//        zombie newzombie;
//        newzombie.Startzombie();
//        float offsetx = (rand() % 1000) - 500;
//        float offsety = (rand() % 1000) - 500;
//        newzombie.shape.setPosition(player.getPosition().x + offsetx, player.getPosition().y + offsety);
//        zombielist.push_back(newzombie);
//    }
//}

//void addzombie() {
//    if (Keyboard::isKeyPressed(Keyboard::Z)) {
//        if (!isZPressed) { spawnzombie(5); isZPressed = true; }
//    }
//    else isZPressed = false;
//}

//void switchwepoans() {
//    if (Keyboard::isKeyPressed(Keyboard::Num1)) {
//        currentweopon = pistlo; currentfirerate = pistlofirerate; currentdamage = pistlodamage; currentammo = pistolAmmoLoaded;
//    }
//    if (Keyboard::isKeyPressed(Keyboard::Num2)) {
//        currentweopon = rifle; currentfirerate = riflofirerate; currentdamage = riflodamage; currentammo = rifleAmmoLoaded;
//    }
//}
//
//void reload() {
//    if (Keyboard::isKeyPressed(Keyboard::R)) {
//        if (currentweopon == pistlo) { pistolAmmoLoaded = 8; currentammo = 8; }
//        else { rifleAmmoLoaded = 30; currentammo = 30; }
//        cout << "reloading..." << endl;
//    }
//}

void Draw() {
    window.clear();
    window.draw(background);
    window.setView(view);
    player.Drawplayer(window);
    //window.draw(re1);
    //window.draw(re2);
    //for (auto& b : bullets) window.draw(b.shape);
    //window.draw(player);
    //window.draw(circle);
    //window.draw(gun);
    //for (auto& z : zombielist) window.draw(z.shape);
    window.display();
}