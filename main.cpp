#include "Bib.h"
#include "Structures.h"


#include "Variables.h"


#include "Render.h"
#include "logic.h"




int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    Desk desk;
    Player player;
    Player enemy;
    Desk discarding;
    //����� 
    Desk field;
    //���� ��� 
    
    //����� ������
    thread gameThread(RestartGame, ref(player), ref(enemy), ref(desk), ref(discarding), ref(field));

    //����� ��� �����
    thread renderSound(sound);
    //����� ��������� � ���� 
    thread renderThread(PrintAllCard, ref(player), ref(enemy), ref(desk), ref(discarding), ref(field));

    renderThread.join();
    renderSound.join();
    gameThread.join();
    return 0;
}