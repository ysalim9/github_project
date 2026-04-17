#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "player.h"
using namespace std;
using namespace sf;
void Start();
void Update();
void Draw();
void PlayerMovement();
void CalculateAimDirection();
void PlayerAnimation();
void Shooting();
void HandleBullets();
void collision();
// --- الإعدادات العامة ---
RenderWindow window(VideoMode(1440, 900), "Vampire Survivors ");
View view(Vector2f(0, 0), Vector2f(window.getSize().x, window.getSize().y));
float deltatime;
enum Direction { Right, Left, Up, Down };
Direction aimDir = Right;
struct bullet {
    RectangleShape shape;
    Vector2f velocity;
    int damage = 25;
    void update(float dt) {
        shape.move(velocity * dt);
    }
};

// --- استركت الشخصية ---
struct Character {
    Sprite sprite;
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

    // مصفوفات الصور داخل الاستركت
    Texture non_R[6], non_L[6];
    Texture move_R[8], move_L[8];
    Texture hit_R[7], hit_L[7];
    Texture hit_up[5], hit_down[5];
    Texture damage_L[3], damage_R[3];
    Texture down_L[3], down_R[3];
    //Texture recall_L[5], recall_R[5];
    void loadAllTextures() {
        for (int i = 0; i < 6; i++) {
            non_L[i].loadFromFile("player/non_L/non_L_frame" + to_string(i) + ".png");
            non_R[i].loadFromFile("player/non_R/non_R_frame" + to_string(i) + ".png");
        }
        for (int i = 0; i < 8; i++) {
            move_L[i].loadFromFile("player/move_L/move_L_frame" + to_string(i) + ".png");
            move_R[i].loadFromFile("player/move_R/move_R_frame" + to_string(i) + ".png");
        }
        for (int i = 0; i < 7; i++) {
            hit_L[i].loadFromFile("player/hit_L/hit_L_frame" + to_string(i) + ".png");
            hit_R[i].loadFromFile("player/hit_R/hit_R_frame" + to_string(i) + ".png");
        }
        for (int  i = 0; i < 5; i++)
        {
            hit_up[i].loadFromFile("player/hit_up/hit_up_frame" + to_string(i) + ".png");
            hit_down[i].loadFromFile("player/hit_down/hit_up_frame" + to_string(i) + ".png");
            //recall_R[i].loadFromFile("player/recall_R/recall_R_frame" + to_string(i) + ".png");
           // recall_L[i].loadFromFile("player/recall_L/recall_L_frame" + to_string(i) + ".png");
        }
        for (int i = 0; i < 3; i++) {
            damage_L[i].loadFromFile("player/damage_L/damage_L_frame" + to_string(i) + ".png");
            damage_R[i].loadFromFile("player/damage_R/damage_R_frame" + to_string(i) + ".png");
            down_L[i].loadFromFile("player/down_L/down_L_frame"+ to_string(i)+ ".png");
            down_R[i].loadFromFile("player/down_R/down_R_frame" + to_string(i) + ".png");

        }   
    }
};
// --- المتغيرات العالمية ---
Character playerObj;
RectangleShape playerCollider(Vector2f(128 / 4, 128 / 2));
RectangleShape circle(Vector2f(100.f,60.f));   // شكل تجريبي
Sprite background, effectGun;
vector<bullet> bullets;
Texture backgroundTex;//effect_L[2], effect_R[2];
//bool showEffect = false;
//float effectTimer = 0;
// --- تعريف الدوال ---
void Start() {
    playerObj.loadAllTextures();
    playerObj.sprite.setOrigin(512 / 2, 512 / 2);
    playerObj.sprite.setPosition(720, 450);
    playerCollider.setOrigin(playerCollider.getSize().x / 2, playerCollider.getSize().y / 2);
    playerCollider.setSize(Vector2f(45.f, 70.f));
    playerCollider.setOutlineColor(Color::Green);
        playerCollider.setOutlineThickness(2);
    playerCollider.setFillColor(Color::Transparent);
    /*for (int i = 0; i < 2; i++) {
        effect_R[i].loadFromFile("effect_gun_R/effect_R_frame" + to_string(i) + ".png");
        effect_L[i].loadFromFile("effect_gun_L/effect_L_frame" + to_string(i) + ".png");
    }*/

    if (backgroundTex.loadFromFile("background2.png")) {
        backgroundTex.setRepeated(true);
        background.setTexture(backgroundTex);
        background.setTextureRect(IntRect(0, 0, 20000, 20000));
        background.setPosition(-10000, -10000);
    }
    effectGun.setOrigin(512 / 2, 512 / 2);
}

void PlayerMovement() {
    if (playerObj.isdead) return;
    float speed = 400.0f;
    playerObj.isMoving = false;
    if (playerObj.isDoingAction||playerObj.isdamage) return;

    if (Keyboard::isKeyPressed(Keyboard::Up)) { playerObj.sprite.move(0, -speed * deltatime); playerObj.isMoving = true; }
    if (Keyboard::isKeyPressed(Keyboard::Down)) { playerObj.sprite.move(0, speed * deltatime);  playerObj.isMoving = true; }
    if (Keyboard::isKeyPressed(Keyboard::Right)) { playerObj.sprite.move(speed * deltatime, 0);  playerObj.isMoving = true; }
    if (Keyboard::isKeyPressed(Keyboard::Left)) { playerObj.sprite.move(-speed * deltatime, 0); playerObj.isMoving = true; }
}

void CalculateAimDirection() {
    if (playerObj.isdead) return;
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
    Vector2f playerPos = playerObj.sprite.getPosition();

    float dx = mousePos.x - playerPos.x;
    float dy = mousePos.y - playerPos.y;
    if (abs(dx) > abs(dy)) {
        aimDir = (dx > 0) ? Right : Left;
        playerObj.facingRight = (dx > 0);
    }
    else {
        aimDir = (dy > 0) ? Down : Up;
    }
}

void PlayerAnimation() {
    playerObj.animTimer += deltatime;
    if (playerObj.animTimer >= 0.1f) {
        playerObj.animTimer = 0;
        playerObj.frameCounter++;
    }

    if (playerObj.currant_halthe <= 0)
    {
        playerObj.isdead = true;
        int deathFrame = playerObj.frameCounter;
        if (deathFrame > 2) deathFrame = 2;
        playerObj.sprite.setColor(Color::White);
        if (playerObj.facingRight)
            playerObj.sprite.setTexture(playerObj.down_R[deathFrame]);
        else
            playerObj.sprite.setTexture(playerObj.down_L[deathFrame]);
        return;
    }
       else if (playerObj.isdamage)
    {
        playerObj.frameCounter %= 2;
        playerObj.sprite.setColor(Color(255, 100, 100));
        if (playerObj.facingRight)
            playerObj.sprite.setTexture(playerObj.damage_R[playerObj.frameCounter]); 
        else
         playerObj.sprite.setTexture(playerObj.damage_L[playerObj.frameCounter]);
        playerObj.damageTimer += deltatime;
        if (playerObj.damageTimer >= 0.4f) {
            playerObj.isdamage = false;
            playerObj.sprite.setColor(Color::White);
        }
    }
     else if (playerObj.isDoingAction) {
        if (aimDir == Up) {
            playerObj.frameCounter %= 5;
            playerObj.sprite.setTexture(playerObj.hit_up[playerObj.frameCounter], true);
            if (playerObj.frameCounter == 4) playerObj.isDoingAction = false;
        }
        else if (aimDir == Down) {
            playerObj.frameCounter %= 5;
            playerObj.sprite.setTexture(playerObj.hit_down[playerObj.frameCounter], true);
            if (playerObj.frameCounter == 4) playerObj.isDoingAction = false;
        }
        else { // يمين أو شمال
            playerObj.frameCounter %= 7;
            playerObj.sprite.setTexture(playerObj.facingRight ? playerObj.hit_R[playerObj.frameCounter] : playerObj.hit_L[playerObj.frameCounter], true);
            if (playerObj.frameCounter == 6) playerObj.isDoingAction = false;
        }
    }
    else if (playerObj.isMoving) {
        playerObj.frameCounter %= 8;
        playerObj.sprite.setTexture(playerObj.facingRight ? playerObj.move_R[playerObj.frameCounter] : playerObj.move_L[playerObj.frameCounter]);
    }
    else {
        playerObj.frameCounter %= 6;
        playerObj.sprite.setTexture(playerObj.facingRight ? playerObj.non_R[playerObj.frameCounter] : playerObj.non_L[playerObj.frameCounter]);
    }
}

void Shooting() {

    if (playerObj.isdead) return;
    if (Mouse::isButtonPressed(Mouse::Left) && !playerObj.isDoingAction) {
        playerObj.isDoingAction = true;
        playerObj.frameCounter = 0;
        playerObj.animTimer = 0;
       // effectTimer = 0;
    }

    static bool fired = false;
    if (playerObj.isDoingAction && playerObj.frameCounter == 3 && !fired) {
        float baseAngle = 0;
        if (aimDir == Right) baseAngle = 0.f;
        else if (aimDir == Left) baseAngle = 180.f;
        else if (aimDir == Up) baseAngle = 270.f;
        else if (aimDir == Down) baseAngle = 90.f;
        float spread[] = { 0.f, -5.f, 5.f, 7.f, -7.f };
        for (int i = 0; i < 5; i++) {
            bullet b;
            b.shape.setSize(Vector2f(10, 5));
            b.shape.setFillColor(Color::Yellow);
            b.shape.setOrigin(5, 2.5f);
            b.shape.setPosition(playerObj.sprite.getPosition().x, playerObj.sprite.getPosition().y - 40);

            float rad = (baseAngle + spread[i]) * 3.14159f / 180.f;
            b.velocity = Vector2f(cos(rad) * 800.f, sin(rad) * 800.f);
            b.shape.setRotation(baseAngle + spread[i]);
            bullets.push_back(b);
        }
        fired = true;
       // showEffect = true;
    }
    if (!playerObj.isDoingAction) fired = false;
}

void HandleBullets() {
    for (size_t i = 0; i < bullets.size(); i++) {
        bullets[i].update(deltatime);
        // مسح الرصاص البعيد
        if (abs(bullets[i].shape.getPosition().x) > 20000) { bullets.erase(bullets.begin() + i); i--; }
    }
    }

void Update() {
    Vector2f targetPos = playerObj.sprite.getPosition();
    view.setCenter(view.getCenter() + (targetPos - view.getCenter()) * 0.1f);
    window.setView(view);

    PlayerMovement();
    CalculateAimDirection();
    PlayerAnimation();
    Shooting();
    HandleBullets();
    // تحديث مكان الكوليدر ليكون في منتصف اللاعب بالضبط
    playerCollider.setPosition(playerObj.sprite.getPosition().x,
        playerObj.sprite.getPosition().y-35.f);
    collision();
    if (playerObj.isdead)
    {
        playerObj.sprite.move(playerObj.deathVelocity * deltatime);
        playerObj.deathVelocity.x *= 0.98f;
        playerObj.deathVelocity.y *= 0.98f;
        if (playerObj.deathVelocity.x<.1f)
         playerObj.deathVelocity.x = 0;
    }
  /*  if (showEffect) {
        float offset = playerObj.facingRight ? 40.0f : -40.0f;
        effectGun.setPosition(playerObj.sprite.getPosition().x - offset, playerObj.sprite.getPosition().y - 10);
        effectTimer += deltatime;
        int frame = (effectTimer < 0.05f) ? 0 : 1;
        effectGun.setTexture(playerObj.facingRight ? effect_R[frame] : effect_L[frame]);
        if (effectTimer >= 0.1f) showEffect = false;
    }*/
}

void Draw() {
    window.clear();
    window.draw(background);
    window.draw(circle);
    //window.draw(playerCollider);
    for (int i = 0;i<bullets.size();i++) window.draw(bullets[i].shape);
    window.draw(playerObj.sprite);
    //if (showEffect) window.draw(effectGun);
    window.display();
}

int main() {
    Start();
    Clock clock;
    while (window.isOpen()) {
        deltatime = clock.restart().asSeconds();
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
        }
        Update();
        Draw();
    }
    return 0;
}

void collision() {
    if (playerObj.isdead) return;
    // استخدمنا الكوليدر الصغير بدل الصورة الكبيرة
    FloatRect playerBounds = playerCollider.getGlobalBounds();
    FloatRect circleBounds = circle.getGlobalBounds();
    FloatRect overlap;

    if (playerBounds.intersects(circleBounds, overlap)) {
        if (!playerObj.isdamage) {

               playerObj.currant_halthe -= 10;
              playerObj.frameCounter = 0;
              playerObj.damageTimer = 0;
         cout << "Player Health: " << playerObj.currant_halthe << endl;
          if (playerObj.currant_halthe <= 0)
            {
                float direction = (playerObj.sprite.getPosition().x > circle.getPosition().x) ? 1.f : -1.f;
                playerObj.deathVelocity = Vector2f(direction * 500.f, 0);
                playerObj.isdead = true;
            }
          else {
              playerObj.sprite.setColor(Color(255, 100, 100));
                playerObj.isdamage = true;
                float Knockback = 20.f;
                if (playerObj.facingRight)
                    playerObj.sprite.move(-Knockback, 0);
                else
                    playerObj.sprite.move(Knockback, 0);
            }
        }
    /*    if (overlap.width < overlap.height) {
            if (playerBounds.left < circleBounds.left)
                playerObj.sprite.move(-overlap.width, 0);
            else
                playerObj.sprite.move(overlap.width, 0);
        }
        else {
            if (playerBounds.top < circleBounds.top)
                playerObj.sprite.move(0, -overlap.height);
            else
                playerObj.sprite.move(0, overlap.height);
        }*/
    }

    for (int i = 0; i < bullets.size(); i++) {
        if (circle.getGlobalBounds().intersects(bullets[i].shape.getGlobalBounds())) {
            bullets.erase(bullets.begin() + i);
            i--;
        }
    }
}