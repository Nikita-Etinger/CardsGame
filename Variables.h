#pragma once


extern bool enemyCardDraw;//1- �������� 0- �������� ����� ����������
extern bool botON;//0-��� �������� 1-������� (������ ������)
extern bool flagStartInit;//���� ��������� �������������
extern bool flagStart;
extern bool TURN;//���� ���� 
extern bool ROUND_END;//���� ��������� �����
extern int positionCardChouse;//������������ ����� ����� ������ �����
extern int positionCardChouseEnemy;//������������ ����� ����� ������ ���������
extern bool pushE;//��� ������������ ������� ������ � ������ ���������, ���� �� ���������������� ������
extern bool pushR;

extern int tranlocateCard;//����������� ����
extern bool gameIsOpen;//���� �������� ����
extern int flagSound;//�������� ����
extern int win;//���� ������
extern int animCard;//���� ��������
//������ ��������
/*0-��� ��������
1-��������� ����� �� ������ �������
2-��������� ����� �� ������ �����������
3-�� ���� � ������
4-�� ���� � ����������
5-�� ���� � �����
*/
extern int speedGame;//90- ���������� ��������


// �� ��������
extern int roundS;
extern int countWinEnemy;
extern int countWinPlayer;

