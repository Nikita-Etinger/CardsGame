#pragma once





void drawPlayerCards(RenderWindow& window, Player& player);
void drawEnemyCards(RenderWindow& window, Player& player);
void drawDesk(RenderWindow& window, Desk& desk);
void drawDiscarding(RenderWindow& window, Desk& discarding);
void drawField(RenderWindow& window, Desk& field);
void drawAnimCard(Player& player, Player& enemy, Desk& desk, Desk& discarding, Desk& field, RenderWindow& window);
void PrintAllCard(Player& player, Player& enemy, Desk& desk, Desk& discarding, Desk& field);
void chouser(RenderWindow& window, Player& player);
void sound();