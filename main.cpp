#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
//#include <mutex>//����� ������������� �������
#include <thread>//������
#include <chrono>//�����
#define enemyCardDraw 1//1- �������� 2- ��������
#define random(a,b) a+rand()%(b+1-a)
using namespace std;
using namespace sf;

bool TURN = 0;
bool ROUND_END = 0;
int positionCardChouse = 0;//������������ ����� ����� ������ �����
int positionCardChouseEnemy = 0;//������������ ����� ����� ������ ���������
bool pushE = 0;//��� ������������ ������� ������ � ������ ���������, ���� �� ���������������� ������
bool pushR = 0;
const string CARDSUIT[4]{"Spades","Hearts","Diamonds","Clubs" };
int tranlocateCard = 0;//����������� ����
bool gameIsOpen = 1;
int animCard = 0;//������ ��������
/*0-��� ��������
1-��������� ����� �� ������ �������
2-��������� ����� �� ������ �����������
3-�� ���� � ������
4-�� ���� � ����������
5-�� ���� � �����
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
    int suitInt; //����� ������
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
        // Calculate suit and value based on position in the image
        card[0].suit = i / 9;
        card[0].value = (i % 9) + 6;

        // Set the texture rectangle for the card
        sf::IntRect textureRect(70 * (i % 9), 98 * (i / 9), 70, 98);
        card[0].texture.setSmooth(true);
        card[0].texture.setRepeated(false);
        card[0].texture.loadFromFile("card3.png", textureRect);
        desk.addCards(card);
    }
    desk.mix();
    swap(desk.cards[0], desk.cards[35]);//������������� ������ ��� ��������� �����
    desk.suitInt = desk.cards[0]->suit;//��������� ����� ������
    


}
void addCard(Desk& desk,Player &player) {
    if (desk.counter > 0) {
        for (int i = player.counter; i < 6; i++) {
            if (player.player) {
                animCard = 1;
            }
            else animCard = 2;
            while (animCard) {
                //�������� ��������� ��������
            }
            player.addCards(desk.removeCard());
        }
    }
}
//��� ����� ������(�� ������� �����)
bool scanToStart(Desk& desk, Player& player, Player& enemy) {
    
    int playerSuit = 13;
    int enemySuit = 13;
    for (int i = 0; i < 6; i++) {
        if (player.cards[i][0].suit == desk.cards[0]->suit && player.cards[i][0].value <playerSuit) {
            playerSuit == player.cards[i][0].value;
        }
        if (enemy.cards[i][0].suit == desk.cards[0]->suit && enemy.cards[i][0].value < enemySuit) {
            enemySuit == enemy.cards[i][0].value;
        }
    }
    return ((playerSuit < enemySuit) ? 1 : 0);



}
//��������, ����� �� ����� ������ ��������� ����� �� ����
bool scanToFight(Desk& field,Card& card,Desk& desk) {
    if (field.counter == 0) return 1;
    //����  ����� �� ������ � ����� ��������� � �������� ������ ������
    else if (card.suit!=desk.suitInt  &&  field.cards[field.counter-1]->suit==card.suit&& field.cards[field.counter-1]->value< card.value) {
        return 1;
    }
    //���� ��� ����� ������, � ����� ������� ���� �� ������
    else if (desk.suitInt == card.suit && field.cards[field.counter-1]->suit != desk.suitInt) {
        return 1;
    }
    //���� ����� ������, � ������� ���� ���� � �������� ������ ������
    else if (desk.suitInt == card.suit && field.cards[field.counter-1]->suit == desk.suitInt && field.cards[field.counter-1]->value < card.value) {
        return 1;
    }
    return 0;

}
//��������, ����� �� ����� ����������� �� ����
bool scanDopCard(Desk& field, Card& card, Desk& desk) {

    for (int i = 0; i < field.counter; i++) {
        if (field.cards[i]->value == card.value) {
            return 1;
        }
    }
    return 0;
}
//��� ����������
bool enemyTurn(Desk& field, Player& enemy,bool turn,Desk& desk,Desk& discarding) {
    if (field.counter == 0) {
        //�������� ����� ��������� �� �������� �����
        int x = 14;
        int j = 0;
        for (int i = 0; i <enemy.counter; i++) {
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

    else if (field.counter % 2 == 0 ) {
        int x = 13;
        int j = 0;
        bool flag = 0;
        for (int i = 0; i < enemy.counter; i++) {
            positionCardChouseEnemy = i;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            //���� ����� �� ������ � � �������� ������ ��� x � �� ����� � ��������
            if (enemy.cards[i]->suit != desk.suitInt && enemy.cards[i]->value < x && scanDopCard(field, enemy.cards[i][0], desk)) {
                j=i;
                x= enemy.cards[i]->value;
                flag=1;

            }

            
        }
        if (flag) {
            field.addCards(enemy.removeCard(j));
            return 1;
        }
        else {
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //����� ������ � �����
            for (int i = 0;  field.counter >0;i++) {
                animCard = 5;
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                discarding.addCards(field.removeCard());
                cout << "CARD ADD DISKARDING" << endl;
                
            }
            cout << field.counter << endl;
            ROUND_END = 1;
            return 1;
        }
        
    }
    else {
        int x = 13;
        int j = 0;
        bool flag = 0;
        //�������� ����� ����������� ����� ����� ������ ����� �� ����
        for (int i = 0; i <enemy.counter; i++) {
            positionCardChouseEnemy = i;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            //���� ����� �� ������ � � �������� ������ ��� ���������� ����� � �� ����� �� ������
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
            x = 13;
            j = 0;
            for (int i = 0; i <enemy.counter; i++) {
                positionCardChouseEnemy = i;
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                //���� ����� ������ � � �������� ������ ��� ���������� �������� ����� � �� ����� �� ������
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
        }
        else {
            //����� � ���� ������������ � ����������
            for (int i = 0; i <= field.counter; i++) {
                animCard = 4;
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                enemy.addCards(field.removeCard());
                
            }
            enemy.addCards(field.removeCard());
            cout << "ENEMY TAKE ALL card" << endl;
            ROUND_END = 1;
            
            return 1;
        }
    }


}
//������������� ������� ������
void chouser(RenderWindow& window, Player& player) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (positionCardChouse == 0) positionCardChouse = player.counter - 1;
        else positionCardChouse--;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (positionCardChouse == player.counter-1) positionCardChouse = 0;
        else positionCardChouse++;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }
}
//��� ������
bool playerTurn(Player& player, Desk& field, Desk& desk, Desk& discarding) {
    //����� ������,
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    if (field.counter == 0) {
         //������� ��� ������
        while (1) {
            if (pushE) {
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                field.addCards(player.removeCard(positionCardChouse));
                pushE = 0;
                return 1;
            }
        }
    }
    //�� ���� ������ ����������� ����
    else if (field.counter % 2 == 0) {
        while (1) {

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
                //����� ������ � �����
                for (int i = 0; field.counter > 0; i++) {
                    animCard = 5;
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                    discarding.addCards(field.removeCard());
                    cout << "CARD ADD DISKARDING" << endl;

                }
                discarding.addCards(field.removeCard());
                cout << field.counter<<endl;
                ROUND_END = 1;
                pushR = 0;
                return 1;

            }
        }
    }
    else {
        while (1) {
            if (pushE) {
                //����� �� ��������� ����� ������
                if ((scanToFight(field, player.cards[positionCardChouse][0], desk))) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                    field.addCards(player.removeCard(positionCardChouse));
                    pushE = 0;
                    return 1;
                }

            }
            if (pushR) {
                //������ ����� ������ �����
                for (int i = 0; i <= field.counter; i++) {
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
    int padding = player.counter * 1.7;//������ ����
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
    int padding = player.counter * 1.7;//������ ����
    int startX = (window.getSize().x - (player.counter * (cardWidth - padding) + padding)) / 2;
    int y = window.getSize().y - 600;

#if (enemyCardDraw==1)
    for (int i = 0; i < player.counter; i++)
    {

        sf::Sprite sprite(player.cards[i][0].texture);
        sprite.setPosition(startX + i * (cardWidth - padding), y);
        sprite.rotate(6.0f);
        if (i == positionCardChouseEnemy && TURN == 0) {
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
        if (i == positionCardChouseEnemy && TURN == 0) {
            sprite.move(0, -40);
        }

        window.draw(sprite);
    }
#endif

}
void drawDesk(RenderWindow& window, Desk& desk) {
    
    int cardWidth = 70;
    int padding = 40;//������ ����

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
    //������ �������� ���� ��� �����������
    if (animCard < 3) {
        int cardWidth = 40;
        int padding = field.counter * 1.1;//������ ����


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
    //�������� ������ ����� � ���������� ��� � ����������, � ������,� �����
    IntRect backTexture(630, 0, 70, 98);
    enemy.backTexture.loadFromFile("card3.png", backTexture);
    desk.backTexture.loadFromFile("card3.png", backTexture);
    discarding.backTexture.loadFromFile("card3.png", backTexture);
    //������������� ���������


}
void drawAnimCard(Player& player, Player& enemy, Desk& desk, Desk& discarding, Desk& field, RenderWindow& window) {    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    /*0-��� ��������
1-��������� ����� �� ������ �������
2-��������� ����� �� ������ �����������
3-�� ���� � ������
4-�� ���� � ����������
5-�� ���� � �����
*/
    if (tranlocateCard <= 300 && animCard != 0) {
        sf::Sprite sprite(desk.backTexture);
        //����� ������������ case �� ��� ������ ���������������� ���������� 
        bool flag = 0;
        if (animCard == 1) {
            int startX = (window.getSize().x) - 700 + tranlocateCard;
            int y = window.getSize().y / 2 - 50 + tranlocateCard;
            sprite.setPosition(startX + 50, y);

        }
        else if (animCard == 2) {
            int startX = (window.getSize().x) - 700 + tranlocateCard;
            int y = window.getSize().y / 2 - 50 - tranlocateCard;
            sprite.setPosition(startX + 50, y);

        }
        else if (animCard == 3) {
            //��������� ������ ����
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
            int y = window.getSize().y / 2;
            sprite.setPosition(startX + tranlocateCard, y);
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

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    window.setFramerateLimit(60);
    // ������� �������� ��� ����
    sf::Texture backGroundTexture;
    if (!backGroundTexture.loadFromFile("backgrounds.png")) {
      
       
    }
    // ������� ������������� � ��������� ���� � ������ ��� ��������
    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setTexture(&backGroundTexture);
    while (gameIsOpen) {
        // ��������� �������
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameIsOpen = false; // ������� �� �����, ���� ���� �����������
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                std::cout << "Space key pressed" << std::endl;
                //player.addCards(desk.removeCard());
                //field.addCards((desk.removeCard()));
                cout << TURN << endl;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E) {
                pushE = 1;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                pushR = 1;
            }

        }
        
        // ������� ����� � ������ ���
        window.clear();
        window.draw(background);

        // ������ ����� 
        drawPlayerCards(window, player);
        drawEnemyCards(window, enemy);
        drawDesk(window, desk);
        drawDiscarding(window, discarding);
        drawField(window, field);
        chouser(window, player); //������ ���������� ���������� positionCardChouse
        //��������� �������� ����������� ����
        drawAnimCard(player, enemy, desk, discarding, field, window);
        window.display();
    }
}
void game(Player& player, Player& enemy, Desk& desk, Desk& discarding, Desk& field) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    //������� �� 6 ����
    player.player = 1;
    addCard(desk, player);
    addCard(desk, enemy);
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    //��� ����� ������
    TURN = scanToStart(desk, player, enemy);

        while (gameIsOpen) {
            cout << "ROUND_END: " << ROUND_END << " TURN: " << TURN << " chouseCard: " << positionCardChouse << " GameIsOpen " << gameIsOpen;
            cout << "HOD" << endl;
            //���� ����� �����
            if (TURN) {
                cout << "TURN PLAYER" << endl;
                playerTurn(player, field, desk, discarding);
                TURN = !TURN;
            }

            //��� �� ����� ���������
            else {
                cout << "TURN ENEMY" << endl;
                enemyTurn(field, enemy, 1, desk, discarding);
                TURN = !TURN;


            }

            if (ROUND_END == 1) {
                addCard(desk, player);
                addCard(desk, enemy);
                ROUND_END = 0;

            }
            

        }
    
}
int main()
{
    



    Desk desk;
    Player player;
    Player enemy;
    Desk discarding;
    //����� 
    Desk field;
    //���� ��� 
    
    // ������� ����� ��� ������������� ����
    std::thread initThread(startInit, std::ref(player), std::ref(enemy), std::ref(desk), std::ref(discarding), std::ref(field));
    initThread.join();


    // ������� ����� ��� ��������� � ������ ������ ���������� ����
    std::thread renderThread(PrintAllCard, std::ref(player), std::ref(enemy), std::ref(desk), std::ref(discarding), std::ref(field));

    std::thread gameThread(game, std::ref(player), std::ref(enemy), std::ref(desk), std::ref(discarding), std::ref(field));

    renderThread.join();
    gameThread.join();
    return 0;
}