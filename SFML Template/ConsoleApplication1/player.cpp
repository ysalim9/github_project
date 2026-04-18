#include "player.h"
#include <iostream>

vector<Bullet> bullets;
RectangleShape copyplayer;
RectangleShape re1, re2, gun;
CircleShape circle;
Sprite spriteofplayer; 
Texture mario;
//----------------------------------varabiles---------------------------------//
bool up = false, down = false, a = false, d = false;
int colum = 0;
Vector2f aimdirection;
float playersdpeed = 100.f;
weopan currentweopon = pistlo;
float shoottimer = 0;
float currentfirerate = pistlofirerate;
int currentdamage = pistlodamage;
int pistolAmmoLoaded = 8;
int rifleAmmoLoaded = 30;
int currentammo = 8;
bool isZPressed = false;
void Character:: Startplayer() {
    circle.setRadius(10.f); 
    circle.setFillColor(Color::Red); 
    circle.setOrigin(10.f, 10.f);
    if (!mario.loadFromFile("player character/mario.png")) {
        std::cout << "Error loading mario.png" << std::endl;
    }
    spriteofplayer.setTexture(mario);
    spriteofplayer.setTextureRect(IntRect(44, 2 * 62, 44, 62));
    spriteofplayer.setPosition(205, 205);
    spriteofplayer.setScale(1, 1);
    spriteofplayer.setOrigin(spriteofplayer.getLocalBounds().width / 2, spriteofplayer.getLocalBounds().height / 2);
    gun.setOrigin((gun.getLocalBounds().width / 2) - 100, gun.getLocalBounds().height / 2);
    circle.setOrigin(circle.getLocalBounds().width / 2, circle.getLocalBounds().height / 2);
    re1.setPosition(1000, 250);
    re2.setPosition(250, 250);
    copyplayer.setOrigin(copyplayer.getLocalBounds().width / 2, copyplayer.getLocalBounds().height / 2);

}

void Character::playermovement() {
    up = false, down = false, a = false, d = false;
    if (Keyboard::isKeyPressed(Keyboard::W)) { spriteofplayer.move(0, -playersdpeed * dt); up = true; }
    if (Keyboard::isKeyPressed(Keyboard::S)) { spriteofplayer.move(0, playersdpeed * dt); down = true; }
    if (Keyboard::isKeyPressed(Keyboard::D)) { spriteofplayer.move(playersdpeed * dt, 0); d = true; }
    if (Keyboard::isKeyPressed(Keyboard::A)) { spriteofplayer.move(-playersdpeed * dt, 0); a = true; }
}


void Character:: playeranimation() {
    if (up) { colum = (colum + 1) % 12;spriteofplayer.setTextureRect(IntRect(colum * 44, 3 * 62, 44, 62)); }
    else if (down) { colum = (colum + 1) % 12; spriteofplayer.setTextureRect(IntRect(colum * 44, 0 * 62, 44, 62)); }
    else if (d) { colum = (colum + 1) % 12; spriteofplayer.setTextureRect(IntRect(colum * 44, 2 * 62, 44, 62)); }
    else if (a) { colum = (colum + 1) % 12; spriteofplayer.setTextureRect(IntRect((colum + 1) * 44, 1 * 62, -44, 62)); }
}
  
void Character::playercollieer( ) {

    if (copyplayer.getGlobalBounds().intersects(re2.getGlobalBounds())) {
        if (Keyboard::isKeyPressed(Keyboard::W)) spriteofplayer.move(0, playersdpeed * dt);
        if (Keyboard::isKeyPressed(Keyboard::S)) spriteofplayer.move(0, -playersdpeed * dt);
        if (Keyboard::isKeyPressed(Keyboard::D)) spriteofplayer.move(-playersdpeed * dt, 0);
        if (Keyboard::isKeyPressed(Keyboard::A)) spriteofplayer.move(playersdpeed * dt, 0);
    }


    for (int i = 0; i < bullets.size(); i++) {
        bool bulletRemoved = false;


        if (bullets[i].shape.getGlobalBounds().intersects(re2.getGlobalBounds())) {
            bullets.erase(bullets.begin() + i);
            i--;
            continue;
        }
        for (int j = 0; j < zombielist.size(); j++) {
            if (!zombielist[j].isdead && bullets[i].shape.getGlobalBounds().intersects(zombielist[j].attackbox.getGlobalBounds())) {
                zombielist[j].health -= bullets[i].damage;
                bullets.erase(bullets.begin() + i);
                i--;
                bulletRemoved = true;
                break;
            }
        }
    }
    
}
void Character:: calculuting(RenderWindow& window) {
    Vector2i mouseposscreen = Mouse::getPosition(window);
    Vector2f mouseworldposition = window.mapPixelToCoords(mouseposscreen);
    circle.setPosition(mouseworldposition);
    aimdirection = normalize(mouseworldposition - spriteofplayer.getPosition());
    gun.setRotation(atan2(aimdirection.y, aimdirection.x) * 180 / 3.14159f);
    gun.setPosition(spriteofplayer.getPosition());
    copyplayer.setPosition(spriteofplayer.getPosition());
}
void Character:: shooting() {
    shoottimer += dt;
    if (Mouse::isButtonPressed(Mouse::Left) && shoottimer >= currentfirerate && currentammo > 0) {
        shoottimer = 0;
        currentammo--;
        if (currentweopon == pistlo) pistolAmmoLoaded = currentammo;
        else rifleAmmoLoaded = currentammo;

        Bullet newbullet;
        newbullet.shape.setSize(Vector2f(10, 5));
        newbullet.shape.setFillColor(Color::Cyan);
        newbullet.shape.setPosition(gun.getPosition());
        newbullet.shape.setRotation(gun.getRotation());
        newbullet.damage = currentdamage;
        newbullet.velocity = aimdirection * 800.0f;
        bullets.push_back(newbullet);
    }
}
void Bullet::bullethandling() {
    for (int i = 0; i < bullets.size(); i++)
        bullets[i].updatebullet(dt);
}
void Character:: switchwepoans() {
    if (Keyboard::isKeyPressed(Keyboard::Num1)) {
        currentweopon = pistlo; currentfirerate = pistlofirerate; currentdamage = pistlodamage; currentammo = pistolAmmoLoaded;
    }
    if (Keyboard::isKeyPressed(Keyboard::Num2)) {
        currentweopon = rifle; currentfirerate = riflofirerate; currentdamage = riflodamage; currentammo = rifleAmmoLoaded;
    }
}
void Character:: reload() {
    if (Keyboard::isKeyPressed(Keyboard::R)) {
        if (currentweopon == pistlo) { pistolAmmoLoaded = 8; currentammo = 8; }
        else { rifleAmmoLoaded = 30; currentammo = 30; }
        
    }
}
void Character::Drawplayer(RenderWindow& window) {
    window.draw(re1);
    window.draw(re2);
    for (auto& b : bullets) window.draw(b.shape);
    window.draw(spriteofplayer);
    window.draw(circle);
    window.draw(gun);


};
void Character::Updateplayer(  RenderWindow& window) {
    playermovement();
    calculuting(window);
    shooting();
    bullet.bullethandling();
    playercollieer();
    switchwepoans();
    reload();
    playeranimation();
}