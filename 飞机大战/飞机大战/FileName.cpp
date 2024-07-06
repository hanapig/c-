#pragma once
#include<iostream>
#include<Windows.h>
using namespace std;
#include <conio.h>//��������
#include <ctime>//����ʱ��





typedef struct posenemy
{
    COORD position[2];//������

};//����һ�����飬����ÿ�л��±꼰������
class Game
{
public:
    int menu();//�˵�
    void SetPos(int a, int b);//��������
    void drawPlane();//�ɻ�����
    void setplanepos(COORD centren);//����ɻ��͵л����꣬����λ��
    void planeMove(char x);//�ɻ��ƶ�
    void play();//ִ��
    void clearplane();//�����ɻ�
    void HideCursor();//���ع��
    void drawenemy();//���ɵ���
    void posenemyplane(int num);//����λ��
    void enemyposmove();//�����ƶ�
    void clearenemies();//�������
    void movespeed();//�ƶ��ٶ�
    bool judge(posenemy enemytest, COORD posjudge);//��ײ���
    bool enemyjudge();//�����Ƿ�����


};
int enemtime;//�ƶ�ʱ��
clock_t lasttime = clock();  // ��¼��һ�θ���ʱ��
COORD pos[900];//λ������洢����
COORD enemypos[900];//��������洢��������
posenemy enemy[8];//��ÿ��������������
bool judge(posenemy enemytest, COORD posjudge);

//���������λ
void Game::SetPos(int a, int b)
{
    HANDLE hout;//�������win��Դ
    COORD coord;//�ַ�������Ļ�ϵ�����
    coord.X = a;
    coord.Y = b;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout, coord);//ָ������������
}


//���˵�
int Game:: menu()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);//������ɫ
	system("title �� �� �� ս");
	SetPos(55, 1);//������������
	cout << "�ɻ���ս";
	SetPos(30, 11);
	cout << "1.��ʼ��Ϸ";
	SetPos(30, 14);
	cout << "2. ESC";
    HideCursor();
    int choice = _getch();  
    return choice;//����ѡ��
}

//�ɻ�ͼ��
void Game::drawPlane()
{
    for (int i = 0; i < 9; i++)
    {
        SetPos(pos[i].X, pos[i].Y); 
        if (i != 5)
        {
            cout << "#";
        }
    }
}
//���˷ɻ�λ�ü�����
void Game::drawenemy()
{
    for (int i = 0; i < 8; i++)
    { // ÿ���л�
        for (int j = 0; j < 1; j++) 
        { // ÿ���л��������
            SetPos(enemy[i].position[j].X, enemy[i].position[j].Y);
            cout <<"**" ;

        }
    }
}


//�о�ͼ��
void Game::posenemyplane(int num)
{
    for (int i=0;i<num;i++)
    {
        COORD baseposition;
        baseposition.X = rand() % 99; // ȷ���л����ᳬ����Ļ��Ե
        baseposition.Y = 1;  // ��ʼY����

        // ���õл������ϽǺ����½�����
        enemy[i].position[0].X = baseposition.X;
        enemy[i].position[0].Y = baseposition.Y;

        enemy[i].position[1].X = baseposition.X+2 ;  // ���½�X����
        enemy[i].position[1].Y = baseposition.Y+2 ;  // ���½�Y����
        
    }
}

//�����ƶ�
void Game::enemyposmove()
{
    for (int i = 0; i < 8; i++) // ��8������
    {
        int maxmove = 5;
        for (int j = 0; j < 2; j++)//��������
            enemy[i].position[j].Y++;
        int move = rand() % (2 * maxmove + 1) - maxmove; // -maxmove �� maxmove ֮�����

        for (int j = 0; j < 2; j++) {
            enemy[i].position[j].X += move;
            if (enemy[i].position[j].X < 0)
            {
                enemy[i].position[j].X = 0;  
            }
            if (enemy[i].position[j].Y >46)
            {
                clearenemies();
                enemy[i].position[j].Y = 0;
            }
            else if (enemy[i].position[j].X > 99)
            {
                enemy[i].position[j].X = 99;  
            }
        }

    }
}

//�������
void Game::clearenemies() 
{
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {  
            SetPos(enemy[i].position[j].X, enemy[i].position[j].Y);
            cout << "  ";  // ���Ǿɵĵл��ַ�
        }
    }
}

//�ƶ��ٶ�
void Game::movespeed()
{
    int enemtime ;//�ƶ�ʱ��
    clock_t lasttime = clock();  // ��¼��һ�θ���ʱ��

}


//�ɻ�ͼ�ΰڷ�λ��
void Game::setplanepos(COORD centren)
{
        pos[0].X = pos[7].X = centren.X;
        pos[1].X = centren.X - 2;
        pos[2].X = pos[6].X = centren.X - 1;
        pos[3].X = pos[8].X = centren.X + 1;
        pos[4].X = centren.X + 2;
        for (int i = 0; i <= 4; i++)
        {
            pos[i].Y = centren.Y;
        }
        for (int i = 6; i <= 8; i++)
        {
            pos[i].Y = centren.Y + 1;
        }
}

//���ع��
void Game:: HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = { 1,0 };//�ڶ���ֵ0��ʾ���ع��
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void ResizeConsole(int width, int height) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD newSize = { short(width), short(height) };

    SMALL_RECT rect = { 0, 0, short(width - 1), short(height - 1) };

    // ������Ļ��������С
    SetConsoleScreenBufferSize(hOut, newSize);
    // ���ô��ڴ�С
    SetConsoleWindowInfo(hOut, TRUE, &rect);
}
//�ƶ��ɻ�

void Game::planeMove(char x)
{
    ResizeConsole(100, 50);
    if (x == 75)
    {
        if (pos[1].X >1)//��߽�
        {
            for (int i = 0; i <= 9; i++)
            {
                pos[i].X -= 2;
            }
        }
    }

    if (x == 80)
    {
        if (pos[7].Y <49)//�±߽�
        {
            for (int i = 0; i <= 9; i++)
            {
                pos[i].Y += 1;
            }
        }
    }

    if (x == 77 && (pos[4].X <99))//�ұ߽�
    {
        for (int i = 0; i <= 9; i++)
        {
            pos[i].X += 2;
        }
    }

    if (x == 72 && (pos[0].Y >0))//�ϱ߽�
    {
        for (int i = 0; i <= 9; i++)
        {
            pos[i].Y -= 1;
        }
    }
}

//�����ɻ�
 void Game:: clearplane() {
     for (int i = 0; i < 9; i++)
     {
         SetPos(pos[i].X, pos[i].Y);
         cout << " ";
     }

}

//��ײ
  bool Game:: judge(posenemy posenemes, COORD posjudge) 
 {
      if ((posjudge.X >= posenemes.position[0].X) && (posjudge.X <= posenemes.position[1].X) //����ĸ�����
          &&(posjudge.Y >= posenemes.position[0].Y) && (posjudge.Y <= posenemes.position[1].Y))
     {
         return true;
     }
     return false;
 }

 //�л����
bool Game:: enemyjudge()
 {
     for (int i = 0; i < 8; i++)
     {
         for (int j = 0; j < 9; j++)
         {
             if (judge(enemy[i], pos[j]))
             {
                 SetPos(45, 20);
                 cout << "  ����,5s���Զ����ز˵�      ";
                 return true;
             }
         }
     }
     return false;
 }

//��Ϸ����
 void Game::play()
 {
     game_start:
     int enemtime = 100;
     bool game = false;
     bool run = true;
     while (run)
     {
         if (_kbhit())
         {

             COORD centren;
             centren.X = 55;
             centren.Y = 40;
             char x = _getch();
             switch (x)
             {
             case '1':
                 system("cls");
                 game = true;
                 setplanepos(centren);//��������
                 posenemyplane(8);
                 HideCursor();
                 break;
             case '2':
                 exit;
                 break;
                 case 75:
                 case 77:
                 case 72:
                 case 80: //�ƶ������
                     HideCursor();
                     clearplane();//�����ɻ�
                     planeMove(x); // �ɻ��ƶ�
                     drawPlane(); // �ػ�ɻ�
                 }
             if (enemyjudge())
             {
                 Sleep(5000);
                 system("cls");
                 break;
             }
         }
         if (game && (clock() - lasttime ) >enemtime ) //����ʱ��
         {
             clearenemies();
             enemyposmove();
             drawenemy();
             lasttime = clock();
         }

     }
 }

int main()
{
    srand(time(NULL));//��ʼ��һ��
    Game game;//ʵ����'
    int re;
    do 
    {
        re = game.menu();
        if (re == '1')
        {
            game.play();
        }
    } while (re != '2');
    return 0;
}
