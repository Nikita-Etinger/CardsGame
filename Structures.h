#pragma once
struct Card
{
    Texture texture;
    int suit; // 0 - Spades, 1 - Hearts, 2 - Diamonds, 3 - Clubs
    int value; // 6 - Ace

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
    Card** cards = new Card * [0];
    int counter = 0;
    Texture backTexture;
    bool player = 0;

    Card* removeCard(int index) {
        if (index < 0 || index >= counter) {
            return nullptr;
        }
        if (player) {
            cout << "PLAYER: ";
        }
        else cout << "ENEMY: ";

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
        if (player) {
            cout << "PLAYER: ";
        }
        else cout << "ENEMY: ";

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