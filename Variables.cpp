bool enemyCardDraw = 1;//1- �������� 0- �������� ����� ����������
bool botON = 0;//0-��� �������� 1-������� (������ ������)
bool flagStartInit = 0;//���� ��������� �������������
bool flagStart = 0;
bool TURN = 0;//���� ���� 
bool ROUND_END = 0;//���� ��������� �����
int positionCardChouse = 0;//������������ ����� ����� ������ �����
int positionCardChouseEnemy = 0;//������������ ����� ����� ������ ���������
bool pushE = 0;//��� ������������ ������� ������ � ������ ���������, ���� �� ���������������� ������
bool pushR = 0;

int tranlocateCard = 0;//����������� ����
bool gameIsOpen = 1;//���� �������� ����
int flagSound = 0;//�������� ����
int win = 0;//���� ������
int animCard = 0;//���� ��������
//������ ��������
/*0-��� ��������
1-��������� ����� �� ������ �������
2-��������� ����� �� ������ �����������
3-�� ���� � ������
4-�� ���� � ����������
5-�� ���� � �����
*/
int speedGame = 90;//90- ���������� ��������


// �� ��������
int roundS = 0;
int countWinEnemy = 0;
int countWinPlayer = 0;
