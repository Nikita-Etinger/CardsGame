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
        //создаёт прямоугольник по требуемым координатам
        IntRect textureRect(70 * (i % 9), 98 * (i / 9), 70, 98);
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

        if (player.cards[i][0].suit == desk.suitInt && player.cards[i][0].value < playerValue) {
            playerValue = player.cards[i][0].value;
        }
        if (enemy.cards[i][0].suit == desk.suitInt && enemy.cards[i][0].value < enemyValue) {
            enemyValue = enemy.cards[i][0].value;
        }
    }

    return ((playerValue < enemyValue) ? 1 : 0);



}
//проверка, может ли карта побить последнюю карту на поле
bool scanToFight(Desk& field, Card& card, Desk& desk) {
    if (field.counter == 0) return 1;
    //если  карта не козырь и масти совпадают и значение бъющей больше
    else if (card.suit != desk.suitInt && field.cards[field.counter - 1]->suit == card.suit && field.cards[field.counter - 1]->value < card.value) {
        return 1;
    }
    //если эта карта козырь, а карта которую бьют не козырь
    else if (desk.suitInt == card.suit && field.cards[field.counter - 1]->suit != desk.suitInt) {
        return 1;
    }
    //если карта козырь, и которую бъют тоже и значение бъющей больше
    else if (desk.suitInt == card.suit && field.cards[field.counter - 1]->suit == desk.suitInt && field.cards[field.counter - 1]->value < card.value) {
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
bool enemyTurn(Desk& field, Player& enemy, Desk& desk, Desk& discarding) {

    if (field.counter == 0) {
        //выбирает самую маленькую не козырную карту
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
                animCard = 5;

                while (animCard) {

                    this_thread::sleep_for(chrono::milliseconds(200 - speedGame));
                    //ожидание окончания анимации
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
        //проверка какая минимальная карта может побить карту на поле
        for (int i = 0; i < enemy.counter; i++) {
            if (enemy.player) positionCardChouse = i;
            else positionCardChouseEnemy = i;
            this_thread::sleep_for(chrono::milliseconds(200 - speedGame));
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
                if (enemy.player) positionCardChouse = i;
                else positionCardChouseEnemy = i;
                this_thread::sleep_for(chrono::milliseconds(200 - speedGame));
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

                for (int i = 0; field.counter - 1 >= 0; i++) {
                    if (enemy.player) {
                        animCard = 3;
                    }
                    else  animCard = 4;

                    while (animCard) {

                        this_thread::sleep_for(chrono::milliseconds(200 - speedGame));
                        //ожидание окончания анимации
                    }
                    enemy.addCards(field.removeCard());
                }

                ROUND_END = 1;
                return 1;
            }
        }

    }


}

//ход игрока
bool playerTurn(Player& player, Desk& field, Desk& desk, Desk& discarding) {
    //после пустое,
    this_thread::sleep_for(chrono::milliseconds(1000));
    if (field.counter == 0) {
        //ожидает ход игрока
        while (player.counter != 0) {
            if (pushE) {
                this_thread::sleep_for(chrono::milliseconds(200));
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
                    this_thread::sleep_for(chrono::milliseconds(200));
                    field.addCards(player.removeCard(positionCardChouse));
                    pushE = 0;
                    return 1;
                }
            }
            if (pushR) {
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //карты уходят в сброс

                for (int i = 0; field.counter > 0; i++) {

                    animCard = 5;
                    while (animCard) {
                        this_thread::sleep_for(chrono::milliseconds(200));
                        //ожидание окончания анимации
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
                //может ли выбранная карта побить
                if ((scanToFight(field, player.cards[positionCardChouse][0], desk))) {
                    this_thread::sleep_for(chrono::milliseconds(200));
                    field.addCards(player.removeCard(positionCardChouse));
                    pushE = 0;
                    return 1;
                }

            }
            if (pushR) {
                //игроку нечем побить карту
                for (int i = 0; field.counter - 1 >= 0; i++) {
                    animCard = 3;
                    while (animCard) {
                        this_thread::sleep_for(chrono::milliseconds(200));
                        //ожидание окончания анимации
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
    //вырезает оборот карты и отправляет его к противнику, в колоду,в сброс
    IntRect backTexture(630, 0, 70, 98);
    enemy.backTexture.loadFromFile("card3.png", backTexture);
    desk.backTexture.loadFromFile("card3.png", backTexture);
    discarding.backTexture.loadFromFile("card3.png", backTexture);
    //инициализация завершена
    flagStartInit = 1;


}
void game(Player& player, Player& enemy, Desk& desk, Desk& discarding, Desk& field) {
    this_thread::sleep_for(chrono::milliseconds(2000));
    //раздаем по 6 карт
    player.player = 1;
    addCard(desk, player);
    addCard(desk, enemy);
    this_thread::sleep_for(chrono::milliseconds(300));
    //кто ходит первым
    TURN = scanToStart(desk, player, enemy);
    flagStart = 1;

    while (gameIsOpen) {

        //если ходит игрок
        if (TURN) {

            if (!botON) {
                playerTurn(player, field, desk, discarding);// КОД ИГРОКА
            }
            else

                enemyTurn(field, player, desk, discarding);// КОД БОТА        
        }

        //или же ходит противник
        else {

            enemyTurn(field, enemy, desk, discarding);// КОД БОТА

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
                //завершение игры
            }
            else if (enemy.counter == 0) {
                win = 2;
                flagSound = 3;
                countWinEnemy++;
                flagStartInit = 0;
                break;
                //завершение игры
            }
        }

        TURN = !TURN;
    }

}
void RestartGame(Player& player, Player& enemy, Desk& desk, Desk& discarding, Desk& field) {
    roundS++;
    while (gameIsOpen) {
        //очистка карт
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



        // инициализация игры
        startInit(player, enemy, desk, discarding, field);
        while (flagStartInit == 0) {
            this_thread::sleep_for(chrono::milliseconds(300));
            //ожидание окончания инициализации
        }
        //поток логики
        thread gameThread(game, ref(player), ref(enemy), ref(desk), ref(discarding), ref(field));

        gameThread.join();
        while (pushR == 0) {
            this_thread::sleep_for(chrono::milliseconds(300));
            //ожидает нажатие кнопки перезапуска и цикл повторяется

        }
        win = 0;
        pushR = 0;
        flagStartInit = 0;
        flagStart = 0;
    }
}