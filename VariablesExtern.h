#pragma once
extern bool enemyCardDraw = 1;//1- �������� 0- �������� ����� ����������
extern bool botON = 0;//0-��� �������� 1-������� (������ ������)
extern bool flagStartInit = 0;//���� ��������� �������������
extern bool flagStart = 0;
extern bool TURN = 0;//���� ���� 
extern bool ROUND_END = 0;//���� ��������� �����
extern int positionCardChouse = 0;//������������ ����� ����� ������ �����
extern int positionCardChouseEnemy = 0;//������������ ����� ����� ������ ���������
extern bool pushE = 0;//��� ������������ ������� ������ � ������ ���������, ���� �� ���������������� ������
extern bool pushR = 0;
extern const string CARDSUIT[4]{ "Spades","Hearts","Diamonds","Clubs" };//��� ������ ������� 
extern int tranlocateCard = 0;//����������� ����
extern bool gameIsOpen = 1;//���� �������� ����
extern int flagSound = 0;//�������� ����
extern int win = 0;//���� ������
extern int animCard = 0;//���� ��������
//������ ��������
/*0-��� ��������
1-��������� ����� �� ������ �������
2-��������� ����� �� ������ �����������
3-�� ���� � ������
4-�� ���� � ����������
5-�� ���� � �����
*/
extern int speedGame = 90;//90- ���������� ��������


// �� ��������
extern int roundS = 0;
extern int countWinEnemy = 0;
extern int countWinPlayer = 0;

