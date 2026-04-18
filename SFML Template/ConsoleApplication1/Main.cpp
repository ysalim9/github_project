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
//---------------------------------------------------------background---------------------------------------------------------//
View view(sf::FloatRect(0, 0, 1000, 800));
sf::RenderWindow window(sf::VideoMode(1080, 1050), "Zombies Project - Clean Version");
Sprite background;
Texture texturebacground;
float dt;


//----------------------------------functions-----------------------------//
void Start();
void Draw();
void Update(float dt);




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
    window.setMouseCursorVisible(false);
    player.Startplayer();

    if (texturebacground.loadFromFile("background2.png")) {
        texturebacground.setRepeated(true);
        background.setTexture(texturebacground);
        background.setTextureRect(IntRect(0, 0, 1000, 800));
        background.setOrigin(500, 400);
    }
}

void Update(float dt) {
    //-------------------------calling function of player------------------------------------//
    player.Updateplayer(dt, window);
    bullet.bullethandling(dt);
    //----------------------------bakgriund-------------------------------------------------//
    view.setCenter(player.players.getPosition());
    background.setPosition(player.players.getPosition());
    int mapx = static_cast<int>(player.players.getPosition().x);
    int mapy = static_cast<int>(player.players.getPosition().y);
    background.setTextureRect(IntRect(mapx, mapy, 1000, 800));
}


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


void Draw() {
    window.clear();
    window.draw(background);
    window.setView(view);
    player.Drawplayer(window);
    //window.draw(re1);
    //window.draw(re2);
    //for (auto& z : zombielist) window.draw(z.shape);
    window.display();
}