#include <cstdlib>
#include <iostream>
using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <thread>
#include <ncurses.h>
#ifdef _WIN32
    #include <windows.h>

    void Sleep(unsigned milliseconds)
    {
        sleep(milliseconds);
    }
#else
    #include <unistd.h>

    void Sleep(unsigned milliseconds)
    {
        usleep(milliseconds * 1000); // takes microseconds
    }
#endif

#include "Objects.h"
#include "Empire_B.h"
#include "Empire_R.h"
#include "Empire_G.h"
#include "Empire_W.h"
#include "Empire_D.h"
#include "main.h"
#define MAX_X 60
#define MAX_Y 40

void Initialization(void);
void print_screen(void);
void print_status(int);
void game_process(void);
void SetColor(int=7);
bool identify(int,int);


int  time_counter;
int  Temp_Army[5][ MAX_Y ][ MAX_X ];

Empire Empire[5];

int main()
{
    Initialization();//初始化
    for(int i=3;i>0;i--)
    {
        cout <<  "Battle start in " << i <<  "..." << endl;
        Sleep(1000);
        printf("\033[H\033[J"); //clear
    }


    thread GameThread( game_process );

    while(1)
    {

        //game_process();

        print_screen();
        Sleep(100);
        printf("\033[H\033[J");  //clear
    }
    //system("PAUSE");
    return 0;
}
void Initialization(void)
{
     srand(time(NULL));
     time_counter=0;
     for (int i=0;i<5;i++)
     {
         Empire[i].Gold=0;
         for (int j=0;j<MAX_Y;j++)
         {
             for (int k=0;k<MAX_X;k++)
             {
                 Temp_Army[i][j][k]=0;
                 Empire[i].Army[j][k]=0;
             }
         }
     }
     for(int k=0;k<5;k++)
     {
        int _x,_y;
            _y=rand()%MAX_Y;
            _x=rand()%MAX_X;
            Empire[k].Army[_y][_x]=100;
     }


}


void print_screen(void)
{
     int j,k;
     for (j=0;j<MAX_Y;j++)
     {
         for (k=0;k<MAX_X;k++)
         {
             if (Empire[0].Army[j][k]==0&&Empire[1].Army[j][k]==0&&Empire[2].Army[j][k]==0&&Empire[3].Army[j][k]==0&&Empire[4].Army[j][k]==0)
             {
                printf("0 ");
             }
             else if(Empire_Get_Battling(k,j))
             {
                printf("\033[%dm", 41);
                printf("X");
                printf("\033[m");
                printf(" ");
             }
             else if(Empire[0].Army[j][k]>0)
             {
                printf("\033[%dm", 94);
               printf("B ");
                printf("\033[m");
             }
             else if(Empire[1].Army[j][k]>0)
             {
                printf("\033[%dm", 91);
               printf("R ");
               printf("\033[m");
             }
             else if(Empire[2].Army[j][k]>0)
             {
                printf("\033[%dm", 92);
               printf("G ");
                printf("\033[m");
             }
             else if(Empire[3].Army[j][k]>0)
             {
                printf("\033[%dm", 93);
                printf("W ");
                printf("\033[m");
             }
             else if(Empire[4].Army[j][k]>0)
             {
               printf("\033[%dm", 30);
               printf("D ");
               printf("\033[m");
             }
         }
         print_status(j);
         printf("\n");
     }
}
void print_status(int line)
{
     printf("|");
     if (line==0)
            printf("================");
     else if(line==1)
            printf("B帝國 軍力/財力:");
     else if(line==2)
          printf("%d/%d",Empire_Get_ArmyTotal(1),Empire[0].Gold);
     else if(line==3)
            printf("================");
     else if(line==4)
            printf("R帝國 軍力/財力:");
     else if(line==5)
            printf("%d/%d",Empire_Get_ArmyTotal(2),Empire[1].Gold);
     else if(line==6)
            printf("================");
     else if(line==7)
            printf("G帝國 軍力/財力:");
     else if(line==8)
            printf("%d/%d",Empire_Get_ArmyTotal(3),Empire[2].Gold);
     else if(line==9)
            printf("================");
     else if(line==10)
            printf("W帝國 軍力/財力:");
     else if(line==11)
            printf("%d/%d",Empire_Get_ArmyTotal(4),Empire[3].Gold);
     else if(line==12)
            printf("================");
     else if(line==13)
            printf("D帝國 軍力/財力:");
     else if(line==14)
            printf("%d/%d",Empire_Get_ArmyTotal(5),Empire[4].Gold);
     else if(line==15)
            printf("================");
     else if(line==16)
            printf("沙盒時鍾:");
     else if(line==17)
     {
          int hh,mm,ss;
          hh=time_counter/3600;
          mm=(time_counter/60)%60;
          ss=time_counter%60;
            printf("     %d:%d:%d",hh,mm,ss);
     }
}


void game_process(void)
{
    while(1)
    {
         //process AIs
         main_B();
         main_R();
         main_G();
         main_W();
         main_D();

         time_counter=time_counter+1;
         int j,k,i;
         for (j=0;j<MAX_Y;j++)
         {
             for (k=0;k<MAX_X;k++)
             {
                 for (i=0;i<5;i++)
                 {
                     Empire[i].Army[j][k]=Empire[i].Army[j][k]+Temp_Army[i][j][k];
                     Temp_Army[i][j][k]=0;
                 }
             }
         }
         for (j=0;j<MAX_Y;j++)
         {
             for (k=0;k<MAX_X;k++)
             {
                 if (Empire_Get_Battling(k,j))
                 {
                    int damage,tt;
                    tt=Empire_Get_AreaArmy(k,j);
                    for (i=0;i<5;i++)
                    {
                       damage=(tt-Empire[i].Army[j][k])/10;
                       if (damage==0)
                          damage=1;
                       Empire[i].Army[j][k]=Empire[i].Army[j][k]-damage;
                       if (Empire[i].Army[j][k]<0)
                          Empire[i].Army[j][k]=0;
                    }
                 }
                 else
                 {
                     for (i=0;i<5;i++)
                     {
                         if (Empire[i].Army[j][k]>0)
                            Empire[i].Gold=Empire[i].Gold+1;
                     }
                 }
             }
         }
         Sleep(150);
    }//while

}
bool Empire_Get_Battling(int x,int y)
{
     if (x>=0&&x<MAX_X&&y>=0&&y<MAX_Y)
     {
         int i,c=0;
         for (i=0;i<5;i++)
         {
             if (Empire[i].Army[y][x]>0)
                c=c+1;
         }
         if (c>=2)
            return 1;
         else
            return 0;
     }
     else
         return false;
     /*{
         system("CLR");
         printf("Empire_Get_Battling引數回傳錯誤!!(%d,%d)",x,y);
         Sleep(5000);
         system("PAUSE");
         exit(0);
         return 0;
     }*/
}
int  Empire_Get_ArmyTotal(int E)
{

     if(E>0&&E<=5)
     {
         int i,j,tt=0;
         for (i=0;i<MAX_Y;i++)
             for (j=0;j<MAX_X;j++)
                 tt=tt+Empire[E-1].Army[i][j];
         return tt;
     }
     else
         return 0;
}
int  Empire_Get_AreaArmy(int x,int y)
{
     if (x>=0&&x<MAX_X&&y>=0&&y<MAX_Y)
     {
         int i,tt=0;
         for (i=0;i<5;i++)
             tt=tt+Empire[i].Army[y][x];
         return tt;
     }
     else
     {
         return 0;
     }
}
void Empire_Move(int x,int y,int direct,int amount,int E,int password)
{
     if (identify(E,password)&&amount!=0)
     {
       if (amount>Empire[E-1].Army[y][x])
          amount=Empire[E-1].Army[y][x];
       if (direct==1&&y>0)//對系統而言使往下 但是對玩家而言是往上
       {
          Empire[E-1].Army[y][x]=Empire[E-1].Army[y][x]-amount;
          Temp_Army[E-1][y-1][x]=Temp_Army[E-1][y-1][x]+amount;
       }
       else if (direct==2&&x<MAX_X-1)//右
       {
          Empire[E-1].Army[y][x]=Empire[E-1].Army[y][x]-amount;
          Temp_Army[E-1][y][x+1]=Temp_Army[E-1][y][x+1]+amount;
       }
       else if (direct==3&&y<MAX_Y-1)//下
       {
          Empire[E-1].Army[y][x]=Empire[E-1].Army[y][x]-amount;
          Temp_Army[E-1][y+1][x]=Temp_Army[E-1][y+1][x]+amount;
       }
       else if (direct==4&&x>0)//左
       {
          Empire[E-1].Army[y][x]=Empire[E-1].Army[y][x]-amount;
          Temp_Army[E-1][y][x-1]=Temp_Army[E-1][y][x-1]+amount;
       }
     }
}
int  Empire_Get_MyArmy(int x,int y,int E,int password)
{
     if (identify(E,password))
     {
        return Empire[E-1].Army[y][x];
     }
     else
     {
         system("CLR");
         printf("Empire_Get_MyArmy引數回傳錯誤,錯誤的密碼!!E=%d",E);
         Sleep(5000);
         system("PAUSE");
         exit(0);
         return 0;
     }


}
void Empire_BuyArmy(int x,int y,int amount,int E,int password)
{
     if (identify(E,password)&&amount!=0&&Empire[E-1].Gold>=10)
     {
        if (x>=0&&x<=MAX_X&&y>=0&&y<=MAX_Y&&Empire[E-1].Army[y][x]>0&&Empire_Get_Battling(x,y)==false)
        {
           if (amount*10>Empire[E-1].Gold)
              amount=Empire[E-1].Gold/10;
           Empire[E-1].Gold=Empire[E-1].Gold-amount*10;
           Temp_Army[E-1][y][x]=Temp_Army[E-1][y][x]+amount;
        }
     }
}
int  Empire_Get_Gold(int id,int Password)
{
     if (identify(id,Password))
        return Empire[id-1].Gold;
     else
        return 0;
}
bool identify(int E,int _password)
{
     //bool control_right;
     if (E==1&&PASSWORD_B==_password)
        return true;
     else if (E==2&&PASSWORD_R==_password)
        return true;
     else if (E==3&&PASSWORD_G==_password)
        return true;
     else if (E==4&&PASSWORD_W==_password)
        return true;
     else if (E==5&&PASSWORD_D==_password)
        return true;
     else
        return false;
}
