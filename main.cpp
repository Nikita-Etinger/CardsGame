#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
//#include <mutex>//метод синхронизации потоков
#include <thread>//потоки
#include <chrono>//время
#include <SFML/Audio.hpp>
#define enemyCardDraw 2//1- показать 2- спрятать
#define botON 0;//0-бот отключен 1-включен
#define random(a,b) a+rand()%(b+1-a)
using namespace std;
using namespace sf;

bool flagStart = 0;
bool TURN = 0;
bool ROUND_END = 0;
int positionCardChouse = 0;//отслеживание какую карты выбрал игрок
int positionCardChouseEnemy = 0;//отслеживание какую карты выбрал противник
bool pushE = 0;//для отслеживания нажатия игрока в потоке отрисовки, дабы не синхронизировать потоки
bool pushR = 0;
const string CARDSUIT[4]{"Spades","Hearts","Diamonds","Clubs" };
int tranlocateCard = 0;//перемещение карт
bool gameIsOpen = 1;
int flagSound = 0;
int win = 0;
int animCard = 0;//запуск анимаций
/*0-нет анимации
1-получение карты из колоды игроком
2-получение карты из колоды противником
3-из поля к игроку
4-из поля к противнику
5-из поля в сброс
*/





struct Card
{
    sf::Texture texture;
    int suit; // 0 - Spades, 1 - Hearts, 2 - Diamonds, 3 - Clubs
    int value; // 6 - Ace
    void show() {
        cout << "suit: " << CARDSUIT[suit] << " Value: " << value << endl;
    }
    
};
struct Desk
{
    Texture backTexture;
    int suitInt; //масть козыря
    Card** cards = nullptr;
    int counter = 0;

    void mix() {
        srand(time(NULL));
        for (int j = 0; j < 36; j++) {
            int x = random(j, 35);
            if (x != j) {
                swap(cards[j], cards[x]);
            }
        }
    }

    Card* removeCard() {
        if (counter == 0) {
            return nullptr;
        }
        int index = counter - 1;
        Card* removedCard = cards[index];
        cards[index] = nullptr; 
        counter--;
        if (counter == 0) {
            delete[] cards;
            cards = nullptr;
        }
        else {
            Card** newCards = new Card * [counter];
            for (int j = 0; j < counter; j++) {
                if (j < index) {
                    newCards[j] = cards[j];
                }
                else {
                    newCards[j] = cards[j + 1];
                }
            }
            delete[] cards;
            cards = newCards;
        }
        return removedCard;
    }

    void addCards(Card* card) {
        if (card == nullptr) {
            return;
        }
        Card** newCards = new Card * [counter + 1];
        for (int i = 0; i < counter; i++) {
            newCards[i] = cards[i];
        }
        newCards[counter] = card;
        counter++;
        if (cards != nullptr) {
            delete[] cards;
        }
        cards = newCards;
    }
};
struct Player {
    Card** cards = new Card*[0];
    int counter = 0;
    Texture backTexture;
    bool player = 0;
  
    Card* removeCard(int index) {
        if (index < 0 || index >= counter) {
            return nullptr;
        }
        cout << "DELL";
        cards[index]->show();
        Card* removedCard = cards[index];
        cards[index] = nullptr; // set to nullptr to avoid double deletion
        counter--;
        if (counter == 0) {
            delete[] cards;
            cards = nullptr;
        }
        else {
            Card** newCards = new Card * [counter];
            for (int j = 0; j < counter; j++) {
                if (j < index) {
                    newCards[j] = cards[j];
                }
                else {
                    newCards[j] = cards[j + 1];
                }
            }
            delete[] cards;
            cards = newCards;
        }
        return removedCard;
    }
    

    void addCards(Card* card) {
        if (card == nullptr) {
            return;
        }
        cout << "ADD";
        card->show();
        Card** newCards = new Card * [counter + 1];
        for (int i = 0; i < counter; i++) {
            newCards[i] = cards[i];
        }
        newCards[counter] = card;
        counter++;
        if (cards != nullptr) {
            delete[] cards;
        }
        cards = newCards;
    }



    

};
void loadCards(Desk& desk)
{
    for (int i = 0; i < 36; i++)
    {
        Card* card=new Card[1];

        card[0].suit = i / 9;
        card[0].value = (i % 9) + 6;
        //создаёт прямоугольник по требуемым координатам
        sf::IntRect textureRect(70 * (i % 9), 98 * (i / 9), 70, 98);
        //добавляет размытие
        card[0].texture.setSmooth(true);
        card[0].texture.setRepeated(false);
        //вырезает из основного изображения карты по прямоугольнику
        card[0].texture.loadFromFile("card3.png", textureRect);
        desk.addCards(card);
    }
    desk.mix();
    swap(desk.cards[0], desk.cards[35]);//устанавливает козырь как последнюю карту
    desk.suitInt = desk.cards[0]->suit;//фиксируем масть козыря
    


}
void addCard(Desk& desk,Player &player) {
    
    if (desk.counter > 0) {

        for (int i = player.counter; i < 6; i++) {
            flagSound = 2;
            if (player.player) {
                animCard = 1;
            }
            else animCard = 2;
            while (animCard) {
                
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                //ожидание окончания анимации
            }
            player.addCards(desk.removeCard());
        }
    }
}
//кто ходит первым(по младшей масти)
bool scanToStart(Desk& desk, Player& player, Player& enemy) {
    
    int playerValue = 15;
    int enemyValue = 15;
    for (int i = 0; i < 6; i++) {
        //если карта козырь и она меньше предыдущей карты 
        //cout << "player card suit" << player.cards[i][0].suit << "Player card value"<< player.cards[i][0].value << endl;
        //cout << "desk card suit" << desk.suitInt << "old value"<< playerValue << endl;
        cout << player.cards[i][0].suit << "==" << desk.suitInt << "&&" << player.cards[i][0].value << "<" << playerValue << endl;
        if (player.cards[i][0].suit == desk.suitInt && player.cards[i][0].value <playerValue) {
            playerValue = player.cards[i][0].value;
        }
        if (enemy.cards[i][0].suit == desk.suitInt && enemy.cards[i][0].value < enemyValue) {
            enemyValue = enemy.cards[i][0].value;
        }
    }
    cout << "EnemyValue: " << enemyValue << "PlayerValue: " << playerValue << endl;
    return ((playerValue < enemyValue) ? 1 : 0);



}
//проверка, может ли карта побить последнюю карту на поле
bool scanToFight(Desk& field,Card& card,Desk& desk) {
    if (field.counter == 0) return 1;
    //если  карта не козырь и масти совпадают и значение бъющей больше
    else if (card.suit!=desk.suitInt  &&  field.cards[field.counter-1]->suit==card.suit&& field.cards[field.counter-1]->value< card.value) {
        return 1;
    }
    //если эта карта козырь, а карта которую бьют не козырь
    else if (desk.suitInt == card.suit && field.cards[field.counter-1]->suit != desk.suitInt) {
        return 1;
    }
    //если карта козырь, и которую бъют тоже и значение бъющей больше
    else if (desk.suitInt == card.suit && field.cards[field.counter-1]->suit == desk.suitInt && field.cards[field.counter-1]->value < card.value) {
        return 1;
    }
    return 0;

}
//проверка, может ли карта подкинуться на поле
bool scanDopCard(Desk& field, Card& card, Desk& desk) {

    for (int i = 0; i < field.counter; i++) {
        if (field.cards[i]->value == card.value) {
            return 1;
        }
    }
    return 0;
}
//ход противника
bool enemyTurn(Desk& field, Player& enemy,bool turn,Desk& desk,Desk& discarding) {

        if (field.counter == 0) {
            //выбирает самую маленькую не козырную карту
            int x = 15;
            int j = 0;
            for (int i = 0; i < enemy.counter; i++) {
                positionCardChouseEnemy = i;
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                if (enemy.cards[i]->suit != desk.suitInt && enemy.cards[i]->value < x) {

                    j = i;
                    x = enemy.cards[i]->value;
                }
            }
            field.addCards(enemy.removeCard(j));
            return 1;


        }

        else if (field.counter % 2 == 0) {
            int x = 15;
            int j = 0;
            bool flag = 0;
            for (int i = 0; i < enemy.counter; i++) {
                positionCardChouseEnemy = i;
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                //если карта не козырь и её значение меньше чем x и он может её докинуть
                if (enemy.cards[i]->suit != desk.suitInt && enemy.cards[i]->value < x && scanDopCard(field, enemy.cards[i][0], desk)) {
                    j = i;
                    x = enemy.cards[i]->value;
                    flag = 1;

                }


            }
            if (flag) {
                field.addCards(enemy.removeCard(j));
                return 1;
            }
            else {
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //карты уходят в сброс
                for (int i = 0; field.counter > 0; i++) {

                    discarding.addCards(field.removeCard());
                    while (animCard) {

                        std::this_thread::sleep_for(std::chrono::milliseconds(200));
                        //ожидание окончания анимации
                    }


                }
                animCard = 5;
                cout << "CARD ADD DISKARDING" << endl;
                cout << field.counter << endl;
                ROUND_END = 1;
                return 1;
            }

        }

        else {
            int x = 15;
            int j = 0;
            bool flag = 0;
            //проверка какая минимальная карта может побить карту на поле
            for (int i = 0; i < enemy.counter; i++) {
                positionCardChouseEnemy = i;
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                //если карта не козырь и её значение меньше чем предыдущая карта и он может ей побить
                if (enemy.cards[i]->suit != desk.suitInt && enemy.cards[i]->value < x && scanToFight(field, enemy.cards[i][0], desk)) {
                    j = i;
                    x = enemy.cards[i]->value;
                    flag = 1;
                }


            }
            if (flag) {
                field.addCards(enemy.removeCard(j));
                return 1;
            }
            else if (!flag) {
                x = 15;
                j = 0;
                for (int i = 0; i < enemy.counter; i++) {
                    positionCardChouseEnemy = i;
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                    //если карта козырь и её значение меньше чем предыдущая козырная карта и он может ей побить
                    if (enemy.cards[i]->suit == desk.suitInt && enemy.cards[i]->value < x && scanToFight(field, enemy.cards[i][0], desk)) {
                        j = i;
                        x = enemy.cards[i]->value;
                        flag = 1;
                    }
                }
                if (flag) {
                    field.addCards(enemy.removeCard(j));
                    return 1;
                }
                else {
                    //карты с поля перемещаются к противнику
                    animCard = 4;
                    for (int i = 0; field.counter-1 >= 0; i++) {
                        enemy.addCards(field.removeCard());

                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    cout << "ENEMY TAKE ALL card" << endl;
                    ROUND_END = 1;
                    return 1;
                }
            }

        }


}
//переключатель позиции выбора
void chouser(RenderWindow& window, Player& player) {
    pushR = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        pushE = 0;
        if (positionCardChouse < 0) positionCardChouse = player.counter - 1;
        else positionCardChouse--;
        cout << positionCardChouse << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        pushE = 0;
        if (positionCardChouse > player.counter-1) positionCardChouse = 0;
        else positionCardChouse++;
        cout << positionCardChouse << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));

    }
}
//ход игрока
bool playerTurn(Player& player, Desk& field, Desk& desk, Desk& discarding) {
    //после пустое,
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    if (field.counter == 0) {
         //ожидает ход игрока
        while (player.counter != 0) {
            if (pushE) {
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                field.addCards(player.removeCard(positionCardChouse));
                pushE = 0;
                return 1;
            }
        }
    }
    //на поле четное колличество карт
    else if (field.counter % 2 == 0) {
        while (player.counter != 0) {

            if (pushE) {
                if (scanDopCard(field, player.cards[positionCardChouse][0], desk)) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                    field.addCards(player.removeCard(positionCardChouse));
                    pushE = 0;
                    return 1;
                }

            }
            if (pushR) {
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //карты уходят в сброс
                cout << "CARD ADD DISKARDING" << endl;
                for (int i = 0; field.counter > 0; i++) {
                    

                    discarding.addCards(field.removeCard());
                    while (animCard) {

                        std::this_thread::sleep_for(std::chrono::milliseconds(200));
                        //ожидание окончания анимации
                    }
                    

                }
                animCard = 5;
                discarding.addCards(field.removeCard());
                cout << field.counter<<endl;
                ROUND_END = 1;
                pushR = 0;
                return 1;

            }
        }
    }
    else {
        while (player.counter != 0) {
            if (pushE) {
                //может ли выбранная карта побить
                if ((scanToFight(field, player.cards[positionCardChouse][0], desk))) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                    field.addCards(player.removeCard(positionCardChouse));
                    pushE = 0;
                    return 1;
                }

            }
            if (pushR) {
                //игроку нечем побить карту
                for (int i = 0; field.counter-1 >= 0; i++) {
                    animCard = 3;
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                    player.addCards(field.removeCard());
                }
                player.addCards(field.removeCard());
                cout << "PLAYER TAKE ALL CARD" << endl;
                ROUND_END = 1;

                pushR = 0;
                return 1;
            }
        }
    }

    

}
void drawPlayerCards(sf::RenderWindow& window, Player& player)
{
    int cardWidth = 70;
    int padding = player.counter * 1.7;//отступ карт
    int startX = (window.getSize().x - (player.counter * (cardWidth - padding) + padding)) / 2;
    int y = window.getSize().y - 100;


    for (int i = 0; i < player.counter; i++)
    {
        sf::Sprite sprite(player.cards[i][0].texture);
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

#if (enemyCardDraw==1)
    for (int i = 0; i < player.counter; i++)
    {

        sf::Sprite sprite(player.cards[i][0].texture);
        sprite.setPosition(startX + i * (cardWidth - padding), y);
        sprite.rotate(6.0f);
        if (i == positionCardChouseEnemy && TURN == 0 && flagStart) {
            sprite.move(0, +40);
        }
        window.draw(sprite);
    }


#elif (enemyCardDraw==2)
    for (int i = 0; i < player.counter; i++)
    {
        sf::Sprite sprite(player.backTexture);
        sprite.setPosition(startX + i * (cardWidth - padding), y);
        sprite.rotate(6.0f);
        if (i == positionCardChouseEnemy && TURN == 0&& flagStart) {
            sprite.move(0, +40);
        }

        window.draw(sprite);
    }
#endif

}
void drawDesk(RenderWindow& window, Desk& desk) {
    
    int cardWidth = 70;
    int padding = 40;//отступ карт

    int startX = (window.getSize().x) - 700;
    int y = window.getSize().y / 2 - 50;

    
    if (desk.counter > 1) {

        sf::Sprite sprite(desk.backTexture);
        Sprite trump(desk.cards[0]->texture);
        trump.setPosition(startX + 50, y);
        trump.rotate(90.0f);
        sprite.setPosition(startX, y);
        sprite.rotate(90.0f);
        window.draw(trump);
        window.draw(sprite);

    }
    else if (desk.counter == 1) {
        cout << "One card left" << endl;
        Sprite trump(desk.cards[0]->texture);
        trump.setPosition(startX, y);
        trump.rotate(90.0f);
        window.draw(trump);
    }



}
void drawDiscarding(RenderWindow& window, Desk& discarding) {

    int startX = (window.getSize().x) - 100;
    int y = window.getSize().y / 2 - 50;

    if (discarding.counter != 0) {
        sf::Sprite sprite(discarding.backTexture);
        sprite.setPosition(startX, y);
        window.draw(sprite);
    }

}
void drawField(RenderWindow& window, Desk& field) {
    //запуск анимации если нет перемещения
    if (animCard < 3) {
        int cardWidth = 40;
        int padding = field.counter * 1.1;//отступ карт


        int startX = (window.getSize().x - (field.counter * (cardWidth - padding))) / 2;
        int y = window.getSize().y - 350;

        //cout << field.counter << endl;
        for (int i = 0; i < field.counter; i++)
        {
            sf::Sprite sprite(field.cards[i]->texture);
            sprite.setPosition(startX + i * (cardWidth - padding), y);
            sprite.rotate(6.0f);

            window.draw(sprite);
        }
    }

}
void startInit(Player& player, Player& enemy, Desk& desk, Desk& discarding, Desk& field) {
    loadCards(desk);
    //вырезает оборот карты и отправляет его к противнику, в колоду,в сброс
    IntRect backTexture(630, 0, 70, 98);
    enemy.backTexture.loadFromFile("card3.png", backTexture);
    desk.backTexture.loadFromFile("card3.png", backTexture);
    discarding.backTexture.loadFromFile("card3.png", backTexture);
    //инициализация завершена


}
void drawAnimCard(Player& player, Player& enemy, Desk& desk, Desk& discarding, Desk& field, RenderWindow& window) {    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    /*0-нет анимации
1-получение карты из колоды игроком
2-получение карты из колоды противником
3-из поля к игроку
4-из поля к противнику
5-из поля в сброс
*/
    if (tranlocateCard <= 300 && animCard != 0) {
        sf::Sprite sprite(desk.backTexture);
        //хотел использовать case но там нельзя инициализировать переменные 
        bool flag = 0;
        if (animCard == 1) {
            int startX = (window.getSize().x) - 800 + tranlocateCard;
            int y = window.getSize().y / 2 - 50 + tranlocateCard;
            sprite.setPosition(startX + 50, y);

        }
        else if (animCard == 2) {
            int startX = (window.getSize().x) - 800 + tranlocateCard;
            int y = window.getSize().y / 2 - 50 - tranlocateCard;
            sprite.setPosition(startX + 50, y);

        }
        else if (animCard == 3) {
            //отрисовка вместо поля
            int startX = (window.getSize().x / 2);
            int y = window.getSize().y / 2;
            sprite.setPosition(startX, y + tranlocateCard);
        }
        else if (animCard == 4) {
            int startX = (window.getSize().x / 2);
            int y = window.getSize().y / 2;
            sprite.setPosition(startX, y - tranlocateCard);
        }
        else if (animCard == 5) {
            int startX = (window.getSize().x / 2);
            int y = window.getSize().y / 2-50;
            sprite.setPosition(startX + tranlocateCard, y);
        }
        tranlocateCard += 10;
        if (tranlocateCard >= 300) {
            tranlocateCard = 0;
            animCard = 0;
        }
        sprite.rotate(0.5f + tranlocateCard/2);
        window.draw(sprite);
    }

}
void PrintAllCard(Player& player, Player& enemy, Desk& desk, Desk& discarding, Desk& field) {

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    window.setFramerateLimit(60);
    // Создаем текстуру для фона
    sf::Texture backGroundTexture;
    if (!backGroundTexture.loadFromFile("backgrounds.png")) {
      
       
    }
    // Создаем прямоугольник с размерами окна и задаем ему текстуру
    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setTexture(&backGroundTexture);

    //загружаем шрифт и текст
    Font font;
    sf::Text text;
    font.loadFromFile("font.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);


    while (gameIsOpen) {
        // Обработка событий
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameIsOpen = false; // Выходим из цикла, если окно закрывается
            }
            //используется для отладки ////////////////////////////////////////////////////////////////////////////////////////////////////
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {

                std::cout << "Space key pressed" << std::endl;
                
                
                while (desk.counter) {
                    discarding.addCards(desk.removeCard());
                }
                for (int i = player.counter - 1; i>=0;i--) {
                    discarding.addCards(player.removeCard(i));
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                cout << TURN << endl;
            }
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E) {
                pushE = 1;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                pushR = 1;
            }

        }
        
        // Очищаем экран и рисуем фон
        window.clear();
        window.draw(background);

        if (win == 0) {
            // Рисуем карты 
            drawPlayerCards(window, player);
            drawEnemyCards(window, enemy);
            drawDesk(window, desk);
            drawDiscarding(window, discarding);
            drawField(window, field);
            chouser(window, player); //меняет глобальную переменную positionCardChouse
            //отрисовка анимаций перемещения карт
            drawAnimCard(player, enemy, desk, discarding, field, window);
        }
        if (flagStart) {
            if (TURN&&win==0) {

                text.setPosition(window.getSize().x / 2 - 50, window.getSize().y / 2 + 100);
                text.setString("YOU turn");
            }
            else {
                text.setPosition(window.getSize().x / 2 - 100, window.getSize().y / 2 - 100);
                text.setString("Opponent turn");

            }
            if (win == 1) {
                text.setPosition(window.getSize().x / 2 - 250, window.getSize().y / 2-50);
                text.setCharacterSize(60);
                text.setString("!!!YOU WIN!!!");
                
            }
            else if (win == 2) {
                text.setPosition(window.getSize().x / 2 - 250, window.getSize().y / 2-50);
                text.setCharacterSize(60);
                text.setString("!!!YOU LOSE!!!");

            }
        
        }

        window.draw(text);
        window.display();
    }
}
void sound() {
    sf::SoundBuffer soundBuffer1;
    sf::SoundBuffer soundBuffer2;
    sf::SoundBuffer soundBuffer3;
    sf::SoundBuffer soundBuffer4;
    soundBuffer1.loadFromFile("card.wav");
    soundBuffer2.loadFromFile("cardAdd.wav");
    soundBuffer3.loadFromFile("fail.wav");
    soundBuffer4.loadFromFile("win.wav");



    sf::Sound sound1(soundBuffer1);
    sf::Sound sound2(soundBuffer2);
    sf::Sound sound3(soundBuffer3);
    sf::Sound sound4(soundBuffer4);
    while(1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        switch (flagSound) {
        case(1):
            sound1.play();
            cout<<"SOUND"<<endl;
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
void game(Player& player, Player& enemy, Desk& desk, Desk& discarding, Desk& field) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    //раздаем по 6 карт
    player.player = 1;
    addCard(desk, player);
    addCard(desk, enemy);
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    //кто ходит первым
    TURN = scanToStart(desk, player, enemy);
    flagStart = 1;

        while (gameIsOpen) {
            //cout << "ROUND_END: " << ROUND_END << " TURN: " << TURN << " chouseCard: " << positionCardChouse << " GameIsOpen " << gameIsOpen;
            cout << "HOD" << endl;
            //если ходит игрок
            if (TURN) {
                cout << "TURN PLAYER" << endl;
#ifdef botON==0
                playerTurn(player, field, desk, discarding);// КОД ИГРОКА
#elif botON==1
                enemyTurn(field, player, 1, desk, discarding);// КОД БОТА
#endif         
            }

            //или же ходит противник
            else {
                cout << "TURN ENEMY" << endl;
                enemyTurn(field, enemy, 1, desk, discarding);// КОД БОТА
                
            }

            if (ROUND_END == 1) {
                addCard(desk, player);
                addCard(desk, enemy);
                ROUND_END = 0;
                
            }
            else {
                flagSound = 1;
            }
            
            
            if (desk.counter == 0) {
                if (player.counter == 0) {
                    win = 1;
                    flagSound = 4;
                    break;
                }
                else if (enemy.counter == 0) {
                    win = 2;
                    flagSound = 3;
                    break;
                }
            }

            TURN = !TURN;
        }
    
}
int main()
{
    



    Desk desk;
    Player player;
    Player enemy;
    Desk discarding;
    //сброс 
    Desk field;
    //поле боя 
    
    // Создаем поток для инициализации игры
    std::thread initThread(startInit, std::ref(player), std::ref(enemy), std::ref(desk), std::ref(discarding), std::ref(field));
    initThread.join();


    // Создаем поток для отрисовки и создание окна 
    thread renderThread(PrintAllCard, std::ref(player), std::ref(enemy), std::ref(desk), std::ref(discarding), std::ref(field));
    //поток для звука
    thread renderSound(sound);
    //поток логики
    thread gameThread(game, std::ref(player), std::ref(enemy), std::ref(desk), std::ref(discarding), std::ref(field));

    renderSound.join();
    renderThread.join();
    gameThread.join();
    return 0;
}