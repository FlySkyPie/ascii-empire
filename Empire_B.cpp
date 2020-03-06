#include "main.h"
#include <iostream>
#include <cstdlib>
//==============================
#define id 1
#define key 865564
#define MAX_X 60
#define MAX_Y 40
//==============================
using namespace std;

void main_B(void)
{
     int i,j;
     for (i=0;i<MAX_Y;i++)
     {
         for (j=0;j<MAX_X;j++)
         {
             if (Empire_Get_MyArmy(j,i,id,key)>10)
             {
                int go,dd;
                go=Empire_Get_MyArmy(j,i,id,key)/2;
                dd=rand()%4+1;
                Empire_Move(j,i,dd,go,id,key);
             }
             if (Empire_Get_MyArmy(j,i,id,key)<20&&Empire_Get_Gold(id,key)>=10)
             {
                int bb;
                bb=Empire_Get_Gold(id,key)/10;
                Empire_BuyArmy(j,i,bb,id,key);
             }
             else if (Empire_Get_MyArmy(j,i,id,key)<1000&&Empire_Get_Gold(id,key)>=10)
             {
                int bb;
                bb=Empire_Get_Gold(id,key)/40;
                Empire_BuyArmy(j,i,bb,id,key);
             }

         }
     }
}
