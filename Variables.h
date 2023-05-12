#pragma once


extern bool enemyCardDraw;//1- показать 0- спрятать карты противника
extern bool botON;//0-бот отключен 1-включен (вместо игрока)
extern bool flagStartInit;//флаг окончания инициализации
extern bool flagStart;
extern bool TURN;//флаг хода 
extern bool ROUND_END;//флаг окончания рауда
extern int positionCardChouse;//отслеживание какую карты выбрал игрок
extern int positionCardChouseEnemy;//отслеживание какую карты выбрал противник
extern bool pushE;//для отслеживания нажатия игрока в потоке отрисовки, дабы не синхронизировать потоки
extern bool pushR;

extern int tranlocateCard;//перемещение карт
extern bool gameIsOpen;//флаг открытой игры
extern int flagSound;//звуковой флаг
extern int win;//флаг победы
extern int animCard;//флаг анимаций
//запуск анимаций
/*0-нет анимации
1-получение карты из колоды игроком
2-получение карты из колоды противником
3-из поля к игроку
4-из поля к противнику
5-из поля в сброс
*/
extern int speedGame;//90- нормальная скорость


// из интереса
extern int roundS;
extern int countWinEnemy;
extern int countWinPlayer;

