#include "Bib.h"
#include "Structures.h"

#include "Variables.h"

#include "Render.h"


void drawPlayerCards(RenderWindow& window, Player& player){
    int cardWidth = 70;
    int padding = player.counter * 1.7;//отступ карт
    int startX = (window.getSize().x - (player.counter * (cardWidth - padding) + padding)) / 2;
    int y = window.getSize().y - 100;


    for (int i = 0; i < player.counter; i++)
    {
        Sprite sprite(player.cards[i][0].texture);
        sprite.setPosition(startX + i * (cardWidth - padding), y);
        sprite.rotate(6.0f);
        if (i == positionCardChouse && TURN == 1) {
            sprite.move(0, -40);
        }
        window.draw(sprite);
    }
}
void drawEnemyCards(RenderWindow& window, Player& player)
{
    int cardWidth = 70;
    int padding = player.counter * 1.7;//отступ карт
    int startX = (window.getSize().x - (player.counter * (cardWidth - padding) + padding)) / 2;
    int y = window.getSize().y - 600;

    if (enemyCardDraw == 1) {
        for (int i = 0; i < player.counter; i++)
        {

            Sprite sprite(player.cards[i][0].texture);
            sprite.setPosition(startX + i * (cardWidth - padding), y);
            sprite.rotate(6.0f);
            if (i == positionCardChouseEnemy && TURN == 0 && flagStart) {
                sprite.move(0, +40);
            }
            window.draw(sprite);
        }
    }


    else if (enemyCardDraw == 0) {
        for (int i = 0; i < player.counter; i++)
        {
            Sprite sprite(player.backTexture);
            sprite.setPosition(startX + i * (cardWidth - padding), y);
            sprite.rotate(6.0f);
            if (i == positionCardChouseEnemy && TURN == 0 && flagStart) {
                sprite.move(0, +40);
            }

            window.draw(sprite);
        }
    }

}
void drawDesk(RenderWindow& window, Desk& desk) {

    int cardWidth = 70;
    int padding = 40;//отступ карт

    int startX = (window.getSize().x) - 700;
    int y = window.getSize().y / 2 - 50;


    if (desk.counter > 1) {

        Sprite sprite(desk.backTexture);
        Sprite trump(desk.cards[0]->texture);
        trump.setPosition(startX + 50, y);
        trump.rotate(90.0f);
        sprite.setPosition(startX, y);
        sprite.rotate(90.0f);
        window.draw(trump);
        window.draw(sprite);

    }
    else if (desk.counter == 1) {
        Sprite trump(desk.cards[0]->texture);
        trump.setPosition(startX, y);
        trump.rotate(90.0f);
        window.draw(trump);
    }



}
void drawDiscarding(RenderWindow& window, Desk& discarding) {

    int startX = (window.getSize().x) - 40;
    int y = window.getSize().y / 2 - 50;

    if (discarding.counter != 0) {
        Sprite sprite(discarding.backTexture);
        sprite.setPosition(startX, y);
        window.draw(sprite);
    }

}
void drawField(RenderWindow& window, Desk& field) {

    int cardWidth = 40;
    int padding = field.counter * 1.1;//отступ карт


    int startX = (window.getSize().x - (field.counter * (cardWidth - padding))) / 2;
    int y = window.getSize().y - 350;


    for (int i = 0; i < field.counter; i++)
    {
        if (animCard > 3) {
            if (i - 1 == field.counter - 2) {
                break;
            }
        }
        Sprite sprite(field.cards[i]->texture);
        sprite.setPosition(startX + i * (cardWidth - padding), y);
        sprite.rotate(6.0f);

        window.draw(sprite);
    }


}
void drawAnimCard(Player& player, Player& enemy, Desk& desk, Desk& discarding, Desk& field, RenderWindow& window) { 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    /*0-нет анимации
1-получение карты из колоды игроком
2-получение карты из колоды противником
3-из пол€ к игроку
4-из пол€ к противнику
5-из пол€ в сброс
*/
    if (tranlocateCard <= 300 && animCard != 0) {
        Sprite sprite(desk.backTexture);

        //1-получение карты из колоды игроком
        if (animCard == 1) {
            int startX = (window.getSize().x) - 800 + tranlocateCard;
            int y = window.getSize().y / 2 - 50 + tranlocateCard;
            sprite.setPosition(startX + 50, y);
            sprite.rotate(0.5f + tranlocateCard / 2);


        }
        //2-получение карты из колоды противником
        else if (animCard == 2) {
            int startX = (window.getSize().x) - 800 + tranlocateCard;
            int y = window.getSize().y / 2 - 50 - tranlocateCard;
            sprite.setPosition(startX + 50, y);
            sprite.rotate(0.5f + tranlocateCard / 2);

        }
        //3 - из пол€ к игроку
        else if (animCard == 3) {
            int startX = (window.getSize().x / 2);
            int y = window.getSize().y / 2 - 50;
            sprite.setTexture(field.cards[field.counter - 1]->texture);


            sprite.setPosition(startX, y + tranlocateCard);
        }
        //4-из пол€ к противнику
        else if (animCard == 4) {


            int startX = (window.getSize().x / 2);
            int y = window.getSize().y / 2 - 50;
            sprite.setTexture(field.cards[field.counter - 1]->texture);
            sprite.setPosition(startX, y - tranlocateCard);
        }
        //5-из пол€ в сброс
        else if (animCard == 5) {
            int startX = (window.getSize().x / 2 - 30);
            int y = window.getSize().y / 2 - 50;
            sprite.setTexture(field.cards[field.counter - 1]->texture);
            sprite.setPosition(startX + tranlocateCard * 2, y);

        }
        tranlocateCard += 10;
        if (tranlocateCard >= 300) {
            tranlocateCard = 0;
            animCard = 0;
        }

        window.draw(sprite);
    }

}
void PrintAllCard(Player& player, Player& enemy, Desk& desk, Desk& discarding, Desk& field) {

    RenderWindow window(VideoMode(800, 600), "SFML window");
    window.setFramerateLimit(60 + speedGame);
    // —оздаем текстуру дл€ фона
    Texture backGroundTexture;
    if (!backGroundTexture.loadFromFile("backgrounds.png")) {


    }
    // —оздаем пр€моугольник с размерами окна и задаем ему текстуру
    RectangleShape background(Vector2f(window.getSize().x, window.getSize().y));
    background.setTexture(&backGroundTexture);

    //загружаем шрифт и текст
    Font font;
    Text text;
    font.loadFromFile("font.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);


    while (gameIsOpen) {
        window.setFramerateLimit(30 + speedGame);
        // ќбработка событий
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                gameIsOpen = false; // ¬ыходим из цикла, если окно закрываетс€
            }
            //используетс€ дл€ отладки ////////////////////////////////////////////////////////////////////////////////////////////////////
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {




                //while (desk.counter) {
                //    discarding.addCards(desk.removeCard());
                //}
                //for (int i = player.counter - 1; i>=0;i--) {
                //    discarding.addCards(player.removeCard(i));
                //}
                // this_thread::sleep_for( chrono::milliseconds(200));
            }
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::E) {
                pushE = 1;
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::R) {
                pushR = 1;
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::B) {
                botON = !botON;
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::U) {
                if (speedGame != 0)
                    speedGame -= 10;
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::I) {
                if (speedGame < 150)
                    speedGame += 10;
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::V) {
                enemyCardDraw = !enemyCardDraw;
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                gameIsOpen = 0;
            }


        }

        // ќчищаем экран и рисуем фон
        window.clear();
        window.draw(background);
        if (botON) {
            text.setPosition(10, window.getSize().y / 2 + 20);
            text.setCharacterSize(20);
            text.setString("bot ON B ");

        }
        else {
            text.setPosition(10, window.getSize().y / 2 + 20);
            text.setCharacterSize(20);
            text.setString("bot OFF B ");


        }
        window.draw(text);

        text.setPosition(10, window.getSize().y / 2 - 75);
        text.setCharacterSize(20);
        text.setString("Speed " + to_string(speedGame));
        window.draw(text);


        text.setPosition(10, 10);
        text.setCharacterSize(20);
        text.setString("Round " + to_string(roundS));
        window.draw(text);

        text.setPosition(window.getSize().x - 100, window.getSize().y - 30);
        text.setCharacterSize(20);
        text.setString("Player " + to_string(countWinPlayer));
        window.draw(text);

        text.setPosition(window.getSize().x - 100, 10);
        text.setCharacterSize(20);
        text.setString("Enemy " + to_string(countWinEnemy));
        window.draw(text);




        if (win == 0 && flagStartInit != 0) {
            // –исуем карты 
            drawPlayerCards(window, player);
            drawEnemyCards(window, enemy);
            drawDesk(window, desk);
            drawDiscarding(window, discarding);
            drawAnimCard(player, enemy, desk, discarding, field, window);
            drawField(window, field);
            chouser(window, player); //мен€ет глобальную переменную positionCardChouse
            //отрисовка анимаций перемещени€ карт

        }
        if (flagStart) {
            if (TURN && win == 0) {

                text.setPosition(window.getSize().x / 2 - 50, window.getSize().y / 2 + 100);
                text.setCharacterSize(24);
                text.setString("YOU turn");
            }
            else if (!TURN && win == 0) {
                text.setPosition(window.getSize().x / 2 - 100, window.getSize().y / 2 - 100);
                text.setCharacterSize(24);
                text.setString("Opponent turn");

            }
            else if (win == 1) {
                text.setPosition(window.getSize().x / 2 - 270, window.getSize().y / 2 - 100);
                text.setCharacterSize(60);
                text.setString("   !!!YOU WIN!!!\n press R to restart");

            }
            else if (win == 2) {
                text.setPosition(window.getSize().x / 2 - 270, window.getSize().y / 2 - 100);
                text.setCharacterSize(60);
                text.setString("   !!!YOU LOSE!!!\n press R to restart");

            }
            else {
                text.setPosition(window.getSize().x / 2 - 150, window.getSize().y / 2 - 100);
                text.setCharacterSize(30);
                text.setString("WAIT");

            }
            window.draw(text);



        }


        window.display();
    }
}
void sound() {
    SoundBuffer soundBuffer1;
    SoundBuffer soundBuffer2;
    SoundBuffer soundBuffer3;
    SoundBuffer soundBuffer4;
    soundBuffer1.loadFromFile("card.wav");
    soundBuffer2.loadFromFile("cardAdd.wav");
    soundBuffer3.loadFromFile("fail.wav");
    soundBuffer4.loadFromFile("win.wav");



    Sound sound1(soundBuffer1);
    Sound sound2(soundBuffer2);
    Sound sound3(soundBuffer3);
    Sound sound4(soundBuffer4);
    sound3.setVolume(30);
    sound4.setVolume(30);
    while (1) {
        this_thread::sleep_for(chrono::milliseconds(100));
        switch (flagSound) {
        case(1):
            sound1.play();
            break;
        case(2):
            sound2.play();
            break;
        case(3):
            sound3.play();
            break;
        case(4):
            sound4.play();
            break;
        }
        flagSound = 0;

    }
}
//переключатель позиции выбора
void chouser(RenderWindow& window, Player& player) {
    pushR = 0;
    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        pushE = 0;
        if (positionCardChouse < 0) positionCardChouse = player.counter - 1;
        else positionCardChouse--;
        this_thread::sleep_for(chrono::milliseconds(150));

    }
    if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        pushE = 0;
        if (positionCardChouse > player.counter - 1) positionCardChouse = 0;
        else positionCardChouse++;
        this_thread::sleep_for(chrono::milliseconds(150));

    }
}