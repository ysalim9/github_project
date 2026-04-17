
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<string>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
using namespace sf;
Texture cursorTex;
RenderWindow window;
View view;
Texture dfr, poy, backgroundTex, homeTex, menuu, uu, levels, bock, ops, names, musichand2, musichand,menu_ingame, resume, exit2, options_2, select_level, main_menu,vamp_s;
Sprite sprt, bo, menu, b1, levpox, bockp, option_list, names_pox, musichandpox, musichandpox2, menu_ingamepox, resume_p, exit2p, options_2p, select_levelp, main_menup, vamp_spox;
RectangleShape fort(Vector2f(600, 100));
Music backgroundMusic;
CircleShape circ(100);
CircleShape close_options(25.f);
RectangleShape play, l1, l2, l3, options, exite, credits, dark_window, back_credit, musicTrack, sound_c, rec1_m, rec2_m;
Sprite customCursor;
bool rd = 0;
bool p = 0;
bool a = 0;     // اتجاه حركة الطلقة (يمين، يسار، إلخ)     // عداد فريمات التحريك (Animation)
bool e = 1;
bool show_menu=0;
bool music_control = 0, sound_control = 0;// متغير حالة (يمكن استخدامه للقوائم لاحقاً)
float max = 220;
float newlen;
float newlen_sound;
void start() {

    // إنشاء النافذة
    window.create(VideoMode(1365, 768), "Goku and Seven Balls");
    window.setFramerateLimit(30);

    circ.setOrigin(circ.getLocalBounds().width / 2, circ.getLocalBounds().height / 2);


    // تحميل الصور من الملفات
    menuu.loadFromFile("Gemini_Generated_Image_q2z0xjq2z0xjq2z0.PNG");
    bock.loadFromFile("leeeeev.PNG");
    bockp.setTexture(bock);
    ops.loadFromFile("Gemini_Generated_Image_90f6yd90f6yd90f6.PNG");
    //=====================================================================================================
    resume.loadFromFile("Resume_.PNG");
    options_2.loadFromFile("Options_.PNG");
    exit2.loadFromFile("exit.PNG");
    select_level.loadFromFile("select_.PNG");
    main_menu.loadFromFile("main_m.PNG");
    vamp_s.loadFromFile("background_menu_settings.PNG");
    resume_p.setTexture(resume);                                                                         //////////////دي قايمه الحاجات اللي بتظهر جاخل اللعبه 
    vamp_spox.setTexture(vamp_s);                                                                         //////////////دي قايمه الحاجات اللي بتظهر جاخل اللعبه 
    options_2p.setTexture(options_2);
    exit2p.setTexture(exit2);
    main_menup.setTexture(main_menu);
    select_levelp.setTexture(select_level);
    resume_p.setColor(Color::White);
    options_2p.setColor(Color::White);
    exit2p.setColor(Color::White);
    main_menup.setColor(Color::White);
    select_levelp.setColor(Color::White);
    resume_p.setScale(.25, .25);
    options_2p.setScale(.25, .25);
    main_menup.setScale(.25, .25);
    select_levelp.setScale(.25, .25);
    exit2p.setScale(.25, .25);
   vamp_spox.setScale(.17, .21);


    //====================================================================================================
    option_list.setTexture(ops);
    option_list.setPosition(490, 115);                                                                           ////////////////دي اللي فيها اعدادات الصوت 
    option_list.setScale(2, 2);
    //====================================================================================================

    circ.setScale(2, .23);
    menu.setTexture(menuu);
    // إعداد الكاميرا (View)
    view.setSize(500, 200);

    // إعداد الموسيقى
    if (backgroundMusic.openFromFile("September_Balcony.MP3")) {
        backgroundMusic.setLoop(true);
        backgroundMusic.play();
    }

    play.setFillColor(Color::Transparent);
    play.setPosition(488, 466);
    play.setSize(Vector2f(400.f, 143.f));
    credits.setFillColor(Color::Transparent);
    credits.setPosition(180.5, 503);
    credits.setSize(Vector2f(114.f, 94.f));

    l1.setFillColor(Color::Transparent);
    l1.setPosition(560, 146);
    l1.setSize(Vector2f(270.f, 80.f));
    l2.setFillColor(Color::Transparent);
    l2.setPosition(560, 262);
    l2.setSize(Vector2f(270.f, 80.f));
    l3.setFillColor(Color::Transparent);
    l3.setPosition(32, 678);
    l3.setSize(Vector2f(253.f, 72.f));
    options.setFillColor(Color::Transparent);
    options.setPosition(59, 61);
    options.setSize(Vector2f(74.f, 66.5f));
    exite.setFillColor(Color::Transparent);
    exite.setPosition(1085, 500);
    exite.setSize(Vector2f(115.f, 97.5f));
    close_options.setFillColor(Color::Transparent);
    close_options.setPosition(830, 121);

    dark_window.setSize(Vector2f(1365.f, 770.f));
    dark_window.setFillColor(Color::Transparent);
    back_credit.setFillColor(Color::Transparent);
    back_credit.setPosition(122, 634);
    back_credit.setSize(Vector2f(236.f, 85.f));

    names.loadFromFile("Gemini_Generated_Image_48t0zk48t0zk48t0 - Copy.PNG");
    names_pox.setTexture(names);
    menu_ingamepox.setColor(Color::White);
    bool isDraggingMusic = false; // هل المستخدم بيسحب المقبض حالياً؟

    // داخل دالة start()
    musicTrack.setSize(Vector2f(240, 30)); // عرض الشريط
    musicTrack.setFillColor(Color(132, 134, 128));
    musicTrack.setPosition(565, 347);
    musicTrack.setOutlineColor(Color(80, 72, 73));
    musicTrack.setOutlineThickness(4);
    sound_c.setSize(Vector2f(240, 30)); // عرض الشريط
    sound_c.setFillColor(Color(132, 134, 128));
    sound_c.setPosition(565, 454);
    sound_c.setOutlineThickness(4.5);
    sound_c.setOutlineColor(Color(80, 72, 73));
    musichand.loadFromFile("gogoma.PNG");
    musichandpox.setTexture(musichand);
    musichandpox.setScale(.1, .08);
    musichandpox.setPosition(767, 340);
    musichand2.loadFromFile("gogoma.PNG");
    musichandpox2.setTexture(musichand);
    musichandpox2.setScale(.1, .08);
    musichandpox2.setPosition(767, 445);
    rec1_m.setSize(Vector2f(240, 30)); // عرض الشريط
    rec1_m.setFillColor(Color(184, 184, 184));
    rec1_m.setPosition(565, 347);
    rec1_m.setOutlineColor(Color(80, 72, 73));
    rec1_m.setOutlineThickness(4);
    rec2_m.setSize(Vector2f(240, 30)); // عرض الشريط
    rec2_m.setFillColor(Color(184, 184, 184));
    rec2_m.setPosition(565, 454);
    rec2_m.setOutlineThickness(4.5);
    rec2_m.setOutlineColor(Color(80, 72, 73));
    /////////////////////////////////////////////////////////========================================================

    resume_p.setPosition(567,250 );
    select_levelp.setPosition(567,300 );
    main_menup.setPosition(567, 350);
   exit2p.setPosition(567, 400);
    options_2p.setPosition(567, 450);
    vamp_spox.setPosition(485, 130);

    menu_ingame.loadFromFile("menu_in_game.PNG");
        menu_ingamepox.setTexture(menu_ingame);
    //menu_ingamepox.setColor(Color::Transparent);
    menu_ingamepox.setScale(.25, .25);



}

// دالة التحديث: لمعالجة المنطق والحركة والتصادم
void ubdate() {
    Event event;
    Vector2i mupo = Mouse::getPosition(window);
    Vector2f mousepos = window.mapPixelToCoords(mupo);
    Vector2i sound_mouse = Mouse::getPosition(window);
    Vector2f sound_pos = window.mapPixelToCoords(sound_mouse);

    // 2. معالجة الأحداث (Events) مثل إغلاق النافذة والضرب
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();

    }
    if (e)
    {
        if (p)
        {
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                if (musicTrack.getGlobalBounds().contains(mousepos))

                {
                    music_control = 1;
                }
                //musicTrack.setSize(Vector2f(mousepos.x-musicTrack.getPosition().x, musicTrack.getSize().y));

                if (music_control)
                {
                    newlen = mousepos.x - musicTrack.getPosition().x;
                    if (newlen > 240)
                        newlen = 240;
                    if (newlen < 0)
                        newlen = 0;


                    musicTrack.setSize(Vector2f(newlen, musicTrack.getSize().y));

                    musichandpox.setPosition(musicTrack.getPosition().x + newlen - 25, 340);


                }


            }
            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (sound_c.getGlobalBounds().contains(sound_pos))

                {

                    sound_control = 1;

                }
                if (sound_control)
                {
                    newlen_sound = sound_pos.x - sound_c.getPosition().x;
                    if (newlen_sound > 240)
                        newlen_sound = 240;
                    if (newlen_sound < 0)
                        newlen_sound = 0;


                    sound_c.setSize(Vector2f(newlen_sound, sound_c.getSize().y));

                    musichandpox2.setPosition(sound_c.getPosition().x + newlen_sound - 25, 445);
                    backgroundMusic.setVolume(sound_pos.x - sound_c.getPosition().x - 10.f);
                }



            }
            if (!Mouse::isButtonPressed(Mouse::Left))
            {
                sound_control = 0;
                music_control = 0;
            }

            Vector2i mor = Mouse::getPosition(window);
            Vector2f kok = window.mapPixelToCoords(mor);
            if (close_options.getGlobalBounds().contains(kok))
            {
                close_options.setFillColor(Color(0, 0, 0, 130));
                if (Mouse::isButtonPressed(Mouse::Left))
                    p = 0;

            }
            else
                close_options.setFillColor(Color::Transparent);
        }
        else if (a)

        {
            Vector2i mor = Mouse::getPosition(window);
            Vector2f kok = window.mapPixelToCoords(mor);
            if (back_credit.getGlobalBounds().contains(kok))
            {
                back_credit.setFillColor(Color(0, 0, 0, 130));
                if (Mouse::isButtonPressed(Mouse::Left))
                    a = 0;

            }
            else
                back_credit.setFillColor(Color::Transparent);
        }
        else
        {
            Vector2i mor = Mouse::getPosition(window);
            Vector2f kok = window.mapPixelToCoords(mor);
            if (play.getGlobalBounds().contains(kok))
            {
                play.setFillColor(Color(0, 0, 0, 130));


                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    rd = 1;
                    e = 0;
                }
            }

            else  if (credits.getGlobalBounds().contains(kok))
            {                                                     ////الصوره بتتغير لما احط  الماوس عليها 

                credits.setFillColor(Color(0, 0, 0, 130));

                if (Mouse::isButtonPressed(Mouse::Left))
                {

                    a = 1;
                }
            }


            else if (options.getGlobalBounds().contains(kok))
            {
                options.setFillColor(Color(0, 0, 0, 130));

                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    p = 1;
                }



            }

            else    if (exite.getGlobalBounds().contains(kok))
            {
                exite.setFillColor(Color(0, 0, 0, 130));
                if (Mouse::isButtonPressed(Mouse::Left))
                    window.close();

            }

            else
            {

                play.setFillColor(Color::Transparent);
                credits.setFillColor(Color::Transparent);
                options.setFillColor(Color::Transparent);
                exite.setFillColor(Color::Transparent);



            }

        }
    }

    else if (rd)
    {
        Vector2i mor = Mouse::getPosition(window);
        Vector2f kok = window.mapPixelToCoords(mor);
        if (l1.getGlobalBounds().contains(kok))
        {
            l1.setFillColor(Color(0, 0, 0, 150));
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                rd = 0;
            
            }
        }
        else  if (l2.getGlobalBounds().contains(kok))
        {
            l2.setFillColor(Color(0, 0, 0, 150));


        }

        else  if (l3.getGlobalBounds().contains(kok))
        {
            l3.setFillColor(Color(0, 0, 0, 150));

            if (Mouse::isButtonPressed(Mouse::Left))
            {
                rd = 0;
                e = 1;
            }


        }

        else
        {
            l1.setFillColor(Color::Transparent);

            l2.setFillColor(Color::Transparent);
            l3.setFillColor(Color::Transparent);
        }

    }
    if (!e && !rd)
    {
        if (menu_ingamepox.getGlobalBounds().contains(mousepos))
        {
            menu_ingamepox.setColor(Color(200, 200, 200));
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                show_menu = 1;

            }
        }
        else
            menu_ingamepox.setColor(Color::White);

    }
    if (Mouse::isButtonPressed(Mouse::Left))
    {
        Vector2i lop = Mouse::getPosition(window);
        cout << lop.x << " " << lop.y << endl;
    }
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
    }
    // تحديث مركز الكاميرا ليلحق باللاعب
    //view.setCenter(bo.getPosition().x + 100, bo.getPosition().y + 100);

}

// دالة الرسم: لعرض كل العناصر على الشاشة
            //window.setView(window.getDefaultView());
void draw() {
    window.clear();

    if (e)
    {
        window.draw(menu);


        window.draw(play);
        window.draw(credits);
        window.draw(options);
        window.draw(exite);


        if (p)
        {

            dark_window.setFillColor(Color(0, 0, 0, 130));

            window.draw(dark_window);
            window.draw(option_list);
            window.draw(close_options);
            window.draw(rec2_m);
            window.draw(rec1_m);
            window.draw(musicTrack);
            window.draw(sound_c);
            window.draw(musichandpox);
            window.draw(musichandpox2);






        }
        else
            dark_window.setFillColor(Color::Transparent);


        if (a)
        {
            //dark_window.setFillColor(Color(0, 0, 0, 150));
            window.draw(names_pox);
            window.draw(back_credit);


        }
    }

    else if (rd)
    {
        window.draw(bockp);
        window.draw(l1);
        window.draw(l2);
        window.draw(l3);


    }
    else
    {
        window.draw(menu_ingamepox);
        if (show_menu)
        {
            window.draw(vamp_spox);
            window.draw(resume_p);
            window.draw(select_levelp);
            window.draw(main_menup);
            window.draw(exit2p);
            window.draw(options_2p);
        }
    }

    window.display();
}

// =========================================================
// 4. الدالة الرئيسية (Main)                                                                                   
// =========================================================
int main() {
    start(); // التشغيل مرة واحدة عند البداية

    // دورة اللعبة المستمرة
    while (window.isOpen()) {
        ubdate(); // تحديث الحسابات والمنطق
        draw();   // عرض النتائج
    }

    return 0;
}