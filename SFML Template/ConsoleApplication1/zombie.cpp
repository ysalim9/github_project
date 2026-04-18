#include "zombie.h"
#include "player.h"
#include <iostream>
using namespace std;
using namespace sf;
vector<Zombie> zombielist;
Texture zombiespreite;
void Zombie::Startzombie() {
        shape.setTexture(zombiespreite);
        shape.setTextureRect(IntRect(0, 2 * 32, 32, 32));
        attackbox.setSize(Vector2f(50, 50));
        attackbox.setOrigin(attackbox.getLocalBounds().width / 2, attackbox.getLocalBounds().height / 2);
        shape.setOrigin(32 / 2, 32 / 2);
        shape.setScale(scale, scale);
}
void Zombie::caluclatngmovementdirection(Vector2f playerPos) {
            velocity = copyplayer.getPosition() - shape.getPosition();
        velocity = normalizezombie(velocity) * speed;
}
void Zombie::ainmationhamdler() {
        animTimer += dt;
        if (animTimer >= animSwitch) {
            animTimer = 0;
            if (isdead) {
                animationrow = 3;
                if (animationcol < 12) animationcol++;
                else animationcol = 12;
            }
            else if (isattacking) {
                animationrow = 1;
                animationcol = (animationcol + 1) % 7;
            }
            else {
                animationrow = 2;
                animationcol = (animationcol + 1) % 8;
            }
            shape.setTextureRect(IntRect(animationcol * 32, animationrow * 32, 32, 32));

            if (shape.getPosition().x > spriteofplayer.getPosition().x) shape.setScale(-scale, scale);
            else shape.setScale(scale, scale);
        }
}
void Zombie::attack_player(FloatRect playerBounds) {
    //FloatRect playerbounds = copyplayer.getGlobalBounds();
            if (attackbox.getGlobalBounds().intersects(playerBounds)) {
            isattacking = true;
            attackcounter += dt;
            if (attackcounter >= attacktime) {
                attackcounter = 0;
                cout << "hit player!" << endl;
            }
            }
              else isattacking = false;
}
void Zombie::spawnzombie(int count) {
    for (int i = 0; i < count; i++) {
        Zombie newzombie;
        newzombie.Startzombie();
        float offsetx = (rand() % 1000) - 500;
        float offsety = (rand() % 1000) - 500;
        newzombie.shape.setPosition(spriteofplayer.getPosition().x + offsetx, spriteofplayer.getPosition().y + offsety);
        zombielist.push_back(newzombie);

    }
}
void Zombie::zombiehandling() {
    float personalSpace = 50.0f;
    float separationStrength = 40.0f;

    for (int i = 0; i < (int)zombielist.size(); i++) {
        if (zombielist[i].health <= 0 && !zombielist[i].isdead) {
            zombielist[i].isdead = true;
            zombielist[i].speed = 0;
        }

        if (zombielist[i].isdead) {
            zombielist[i].deathTimer += dt;
            zombielist[i].ainmationhamdler();
            if (zombielist[i].deathTimer >= zombielist[i].deathDuration) {
                spawnzombie(2);
                zombielist.erase(zombielist.begin() + i);
                i--;
            }
            continue;
        }

        zombielist[i].attack_player(copyplayer.getGlobalBounds());
        if (!zombielist[i].isattacking)
        {
            zombielist[i].caluclatngmovementdirection(copyplayer.getPosition());


            Vector2f separationforce(0.0f, 0.0f);
            for (int j = 0; j < zombielist.size(); j++) {
                if (i == j || zombielist[j].isdead) continue;
                float dist = Distance(zombielist[i].shape.getPosition(), zombielist[j].shape.getPosition());
                if (dist < personalSpace && dist > 0) {
                    separationforce += (zombielist[i].shape.getPosition() - zombielist[j].shape.getPosition()) / dist;
                }
            }
        zombielist[i].velocity = normalize(zombielist[i].velocity + separationforce * separationStrength) * zombielist[i].speed;
        }
        else
        {
            zombielist[i].isattacking = true; 
            zombielist[i].velocity = Vector2f(0.f, 0.f);
        }
        zombielist[i].attack_player(copyplayer.getGlobalBounds());
        zombielist[i].ainmationhamdler();
        zombielist[i].shape.move(zombielist[i].velocity * (dt * 20.f));
        zombielist[i].attackbox.setPosition(zombielist[i].shape.getPosition());

    }
}
void Zombie::addzombie() {
        if (Keyboard::isKeyPressed(Keyboard::Z)) {
             if (!isZPressed) { spawnzombie(5); isZPressed = true; }
        }
        else isZPressed = false;
}
void Zombie::zombieupdate() {
    zombiehandling();
    addzombie();
}
