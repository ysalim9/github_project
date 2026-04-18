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
Zombie Z; 
//---------------------------------------------------------background---------------------------------------------------------//
View view(sf::FloatRect(0, 0, 1000, 800));
sf::RenderWindow window(sf::VideoMode(1080, 1050), "Zombies Project - Clean Version");
Sprite background;
Texture texturebacground;
 float dt = 0.0f;
//----------------------------------functions-----------------------------//
void Start();void Draw();void Update(float dt);
///////////////////////////////////////////////////////////////////////////
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
    zombiespreite.loadFromFile("zombie.png");
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
    player.Updateplayer(window);//calling function of player
    Z.zombieupdate();
    //----------------------------bakgriund-------------------------------------------------//
    view.setCenter(spriteofplayer.getPosition());
    background.setPosition(spriteofplayer.getPosition());
    int mapx = static_cast<int>(spriteofplayer.getPosition().x);
    int mapy = static_cast<int>(spriteofplayer.getPosition().y);
    background.setTextureRect(IntRect(mapx, mapy, 1000, 800));
}
void Draw() {
    window.clear();
    window.draw(background);
    window.setView(view);
    player.Drawplayer(window);
    for (auto& z : zombielist)window.draw(z.shape);
    window.display();
}