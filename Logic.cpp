#include "Bib.h"
#include "Structures.h"


#include "Variables.h"


#include "Render.h"
#include "Logic.h"

void loadCards(Desk& desk)
{
    for (int i = 0; i < 36; i++)
    {
        Card* card = new Card[1];

        card[0].suit = i / 9;
        card[0].value = (i % 9) + 6;
        //������ ������������� �� ��������� �����������
        IntRect textureRect(70 * (i % 9), 98 * (i / 9), 70, 98);
        //��������� ��������
        card[0].texture.setSmooth(true);
        card[0].texture.setRepeated(false);
        //�������� �� ��������� ����������� ����� �� ��������������
        card[0].texture.loadFromFile("card3.png", textureRect);
        desk.addCards(card);
    }
    desk.mix();
    swap(desk.cards[0], desk.cards[35]);//������������� ������ ��� ��������� �����
    desk.suitInt = desk.cards[0]->suit;//��������� ����� ������



}
void addCard(Desk& desk, Player& player) {

    if (desk.counter > 0) {

        for (int i = player.counter; i < 6; i++) {
            flagSound = 2;
            if (player.player) {
                animCard = 1;
            }
            else animCard = 2;
            while (animCard) {

                this_thread::sleep_for(chrono::milliseconds(200));
                //�������� ��������� ��������
            }
            player.addCards(desk.removeCard());
        }
    }
}
//��� ����� ������(�� ������� �����)
bool scanToStart(Desk& desk, Player& player, Player& enemy) {

    int playerValue = 15;
    int enemyValue = 15;
    for (int i = 0; i < 6; i++) {
        //���� ����� ������ � ��� ������ ���������� ����� 

        if (player.cards[i][0].suit == desk.suitInt && player.cards[i][0].value < playerValue) {
            playerValue = player.cards[i][0].value;
        }
        if (enemy.cards[i][0].suit == desk.suitInt && enemy.cards[i][0].value < enemyValue) {
            enemyValue = enemy.cards[i][0].value;
        }
    }

    return ((playerValue < enemyValue) ? 1 : 0);



}
//��������, ����� �� ����� ������ ��������� ����� �� ����
bool scanToFight(Desk& field, Card& card, Desk& desk) {
    if (field.counter == 0) return 1;
    //����  ����� �� ������ � ����� ��������� � �������� ������ ������
    else if (card.suit != desk.suitInt && field.cards[field.counter - 1]->suit == card.suit && field.cards[field.counter - 1]->value < card.value) {
        return 1;
    }
    //���� ��� ����� ������, � ����� ������� ���� �� ������
    else if (desk.suitInt == card.suit && field.cards[field.counter - 1]->suit != desk.suitInt) {
        return 1;
    }
    //���� ����� ������, � ������� ���� ���� � �������� ������ ������
    else if (desk.suitInt == card.suit && field.cards[field.counter - 1]->suit == desk.suitInt && field.cards[field.counter - 1]->value < card.value) {
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
bool enemyTurn(Desk& field, Player& enemy, Desk& desk, Desk& discarding) {

    if (field.counter == 0) {
        //�������� ����� ��������� �� �������� �����
        int x = 15;
        int j = 0;
        for (int i = 0; i < enemy.counter; i++) {
            if (enemy.player) positionCardChouse = i;
            else positionCardChouseEnemy = i;
            this_thread::sleep_for(chrono::milliseconds(200 - speedGame));
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
            if (enemy.player) positionCardChouse = i;
            else positionCardChouseEnemy = i;
            this_thread::sleep_for(chrono::milliseconds(200 - speedGame));
            //���� ����� �� ������ � � �������� ������ ��� x � �� ����� � ��������
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
            //����� ������ � �����
            for (int i = 0; field.counter > 0; i++) {
                animCard = 5;

                while (animCard) {

                    this_thread::sleep_for(chrono::milliseconds(200 - speedGame));
                    //�������� ��������� ��������
                }
                discarding.addCards(field.removeCard());

            }


            ROUND_END = 1;
            return 1;
        }

    }

    else {
        int x = 15;
        int j = 0;
        bool flag = 0;
        //�������� ����� ����������� ����� ����� ������ ����� �� ����
        for (int i = 0; i < enemy.counter; i++) {
            if (enemy.player) positionCardChouse = i;
            else positionCardChouseEnemy = i;
            this_thread::sleep_for(chrono::milliseconds(200 - speedGame));
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
            x = 15;
            j = 0;
            for (int i = 0; i < enemy.counter; i++) {
                if (enemy.player) positionCardChouse = i;
                else positionCardChouseEnemy = i;
                this_thread::sleep_for(chrono::milliseconds(200 - speedGame));
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
            else {
                //����� � ���� ������������ � ����������

                for (int i = 0; field.counter - 1 >= 0; i++) {
                    if (enemy.player) {
                        animCard = 3;
                    }
                    else  animCard = 4;

                    while (animCard) {

                        this_thread::sleep_for(chrono::milliseconds(200 - speedGame));
                        //�������� ��������� ��������
                    }
                    enemy.addCards(field.removeCard());
                }

                ROUND_END = 1;
                return 1;
            }
        }

    }


}

//��� ������
bool playerTurn(Player& player, Desk& field, Desk& desk, Desk& discarding) {
    //����� ������,
    this_thread::sleep_for(chrono::milliseconds(1000));
    if (field.counter == 0) {
        //������� ��� ������
        while (player.counter != 0) {
            if (pushE) {
                this_thread::sleep_for(chrono::milliseconds(200));
                field.addCards(player.removeCard(positionCardChouse));
                pushE = 0;
                return 1;
            }
        }
    }
    //�� ���� ������ ����������� ����
    else if (field.counter % 2 == 0) {
        while (player.counter != 0) {
            if (pushE) {
                if (scanDopCard(field, player.cards[positionCardChouse][0], desk)) {
                    this_thread::sleep_for(chrono::milliseconds(200));
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
                    while (animCard) {
                        this_thread::sleep_for(chrono::milliseconds(200));
                        //�������� ��������� ��������
                    }
                    discarding.addCards(field.removeCard());
                }

                ROUND_END = 1;
                pushR = 0;
                return 1;

            }
        }
    }
    else {
        while (player.counter != 0) {
            if (pushE) {
                //����� �� ��������� ����� ������
                if ((scanToFight(field, player.cards[positionCardChouse][0], desk))) {
                    this_thread::sleep_for(chrono::milliseconds(200));
                    field.addCards(player.removeCard(positionCardChouse));
                    pushE = 0;
                    return 1;
                }

            }
            if (pushR) {
                //������ ����� ������ �����
                for (int i = 0; field.counter - 1 >= 0; i++) {
                    animCard = 3;
                    while (animCard) {
                        this_thread::sleep_for(chrono::milliseconds(200));
                        //�������� ��������� ��������
                    }
                    player.addCards(field.removeCard());
                }

                ROUND_END = 1;

                pushR = 0;
                return 1;
            }
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
    flagStartInit = 1;


}
void game(Player& player, Player& enemy, Desk& desk, Desk& discarding, Desk& field) {
    this_thread::sleep_for(chrono::milliseconds(2000));
    //������� �� 6 ����
    player.player = 1;
    addCard(desk, player);
    addCard(desk, enemy);
    this_thread::sleep_for(chrono::milliseconds(300));
    //��� ����� ������
    TURN = scanToStart(desk, player, enemy);
    flagStart = 1;

    while (gameIsOpen) {

        //���� ����� �����
        if (TURN) {

            if (!botON) {
                playerTurn(player, field, desk, discarding);// ��� ������
            }
            else

                enemyTurn(field, player, desk, discarding);// ��� ����        
        }

        //��� �� ����� ���������
        else {

            enemyTurn(field, enemy, desk, discarding);// ��� ����

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
                countWinPlayer++;
                flagStartInit = 0;
                break;
                //���������� ����
            }
            else if (enemy.counter == 0) {
                win = 2;
                flagSound = 3;
                countWinEnemy++;
                flagStartInit = 0;
                break;
                //���������� ����
            }
        }

        TURN = !TURN;
    }

}
void RestartGame(Player& player, Player& enemy, Desk& desk, Desk& discarding, Desk& field) {
    roundS++;
    while (gameIsOpen) {
        //������� ����
        for (int i = player.counter - 1; i >= 0; i--) {
            delete[] player.removeCard(i);

        }
        for (int i = enemy.counter - 1; i >= 0; i--) {
            delete[] enemy.removeCard(i);

        }
        for (int i = desk.counter - 1; i >= 0; i--) {
            delete[] desk.removeCard();

        }
        for (int i = field.counter - 1; i >= 0; i--) {
            delete[] field.removeCard();

        }
        for (int i = discarding.counter - 1; i >= 0; i--) {
            delete[] discarding.removeCard();

        }



        // ������������� ����
        startInit(player, enemy, desk, discarding, field);
        while (flagStartInit == 0) {
            this_thread::sleep_for(chrono::milliseconds(300));
            //�������� ��������� �������������
        }
        //����� ������
        thread gameThread(game, ref(player), ref(enemy), ref(desk), ref(discarding), ref(field));

        gameThread.join();
        while (pushR == 0) {
            this_thread::sleep_for(chrono::milliseconds(300));
            //������� ������� ������ ����������� � ���� �����������

        }
        win = 0;
        pushR = 0;
        flagStartInit = 0;
        flagStart = 0;
    }
}