#include "main.h"
#include <iostream>
#include <cstdlib>
//==============================
#define id 2
#define key 8654532
#define MAX_X 60
#define MAX_Y 40
//==============================
using namespace std;


void main_R(void)
{
     int i,j;
     for (i=0;i<MAX_Y;i++)
     {
         for (j=0;j<MAX_X;j++)
         {
             if (Empire_Get_MyArmy(j,i,id,key)>100)
             {
                int mm,dd;
                dd=rand()%4+1;
                mm=Empire_Get_MyArmy(j,i,id,key)-10;
                Empire_Move(j,i,dd,mm,id,key);
             }
             else
             {
                 if (Empire_Get_Battling(j,i)&&Empire_Get_MyArmy(j,i,id,key))
                 {}
                 else if (Empire_Get_Battling(j,i-1)||Empire_Get_Battling(j,i+1)||Empire_Get_Battling(j+1,i)||Empire_Get_Battling(j-1,i))
                 {
                      if (Empire_Get_MyArmy(j,i,id,key)<20)
                      {
                         int gg;
                         gg=20-Empire_Get_MyArmy(j,i,id,key);
                         Empire_BuyArmy(j,i,gg,id,key);
                      }
                      else
                      {
                          int gg=Empire_Get_MyArmy(j,i,id,key);
                          if (Empire_Get_Battling(j,i-1))
                               Empire_Move(j,i,1,gg,id,key);
                          else if (Empire_Get_Battling(j,i+1))
                               Empire_Move(j,i,3,gg,id,key);
                          else if (Empire_Get_Battling(j+1,i))
                               Empire_Move(j,i,2,gg,id,key);
                          else if (Empire_Get_Battling(j-1,i))
                               Empire_Move(j,i,3,gg,id,key);
                      }
                 }
                 else
                 {
                     int mm=Empire_Get_MyArmy(j,i,id,key);
                     if (mm>20&&mm<50)
                     {
                        int gg=Empire_Get_Gold(id,key)/10;
                        Empire_BuyArmy(j,i,gg,id,key);
                     }
                     else if(mm>=50&&mm<=100)
                     {
                        int dd=rand()%4+1;
                        Empire_Move(j,i,dd,mm-1,id,key);
                     }

                 }
             }


         }
     }
}

