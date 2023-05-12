#pragma once
extern bool enemyCardDraw = 1;//1- показать 0- спрятать карты противника
extern bool botON = 0;//0-бот отключен 1-включен (вместо игрока)
extern bool flagStartInit = 0;//флаг окончания инициализации
extern bool flagStart = 0;
extern bool TURN = 0;//флаг хода 
extern bool ROUND_END = 0;//флаг окончания рауда
extern int positionCardChouse = 0;//отслеживание какую карты выбрал игрок
extern int positionCardChouseEnemy = 0;//отслеживание какую карты выбрал противник
extern bool pushE = 0;//для отслеживания нажатия игрока в потоке отрисовки, дабы не синхронизировать потоки
extern bool pushR = 0;
extern const string CARDSUIT[4]{ "Spades","Hearts","Diamonds","Clubs" };//для вывода отладки 
extern int tranlocateCard = 0;//перемещение карт
extern bool gameIsOpen = 1;//флаг открытой игры
extern int flagSound = 0;//звуковой флаг
extern int win = 0;//флаг победы
extern int animCard = 0;//флаг анимаций
//запуск анимаций
/*0-нет анимации
1-получение карты из колоды игроком
2-получение карты из колоды противником
3-из поля к игроку
4-из поля к противнику
5-из поля в сброс
*/
extern int speedGame = 90;//90- нормальная скорость


// из интереса
extern int roundS = 0;
extern int countWinEnemy = 0;
extern int countWinPlayer = 0;

