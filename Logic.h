#pragma once
void loadCards(Desk& desk);
void addCard(Desk& desk, Player& player);
bool scanToStart(Desk& desk, Player& player, Player& enemy);
bool scanToFight(Desk& field, Card& card, Desk& desk);
bool scanDopCard(Desk& field, Card& card, Desk& desk);
bool enemyTurn(Desk& field, Player& enemy, Desk& desk, Desk& discarding);
bool playerTurn(Player& player, Desk& field, Desk& desk, Desk& discarding);
void startInit(Player& player, Player& enemy, Desk& desk, Desk& discarding, Desk& field);
void game(Player& player, Player& enemy, Desk& desk, Desk& discarding, Desk& field);
void RestartGame(Player& player, Player& enemy, Desk& desk, Desk& discarding, Desk& field);