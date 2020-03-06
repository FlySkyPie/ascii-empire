#include "main.h"
#include <iostream>
#include <cstdlib>
//==============================
#define id 5
#define key 12432534
#define MAX_X 60
#define MAX_Y 40
//==============================
using namespace std;


void main_D(void)
{
     int i,j;
     //¦û»âµL¥D¦a
     bool nn=false;
     for (i=0;i<MAX_Y;i++)
     {
         for (j=0;j<MAX_X;j++)
         {
             if (Empire_Get_MyArmy(j,i,id,key)>0)
             {
                if (j<29)
                {
                    if (Empire_Get_AreaArmy(j+1,i)==0)
                    {
                       nn=true;
                       Empire_BuyArmy(j,i,1,id,key);
                    }
                }
                if (j>0)
                {
                    if (Empire_Get_AreaArmy(j-1,i)==0)
                    {
                       nn=true;
                       Empire_BuyArmy(j,i,1,id,key);
                    }
                }

                if (i<19)
                {
                    if (Empire_Get_AreaArmy(j,i+1)==0)
                    {
                       nn=true;
                       Empire_BuyArmy(j,i,1,id,key);
                    }
                }
                if (i>0)
                {
                    if (Empire_Get_AreaArmy(j,i-1)==0)
                    {
                       nn=true;
                       Empire_BuyArmy(j,i,1,id,key);
                    }
                }
             }
             if (Empire_Get_MyArmy(j,i,id,key)>=2)
             {
                if (Empire_Get_AreaArmy(j+1,i)==0)
                   Empire_Move(j,i,2,1,id,key);
                if (Empire_Get_AreaArmy(j-1,i)==0)
                   Empire_Move(j,i,4,1,id,key);
                if (Empire_Get_AreaArmy(j,i+1)==0)
                   Empire_Move(j,i,3,1,id,key);
                if (Empire_Get_AreaArmy(j,i-1)==0)
                   Empire_Move(j,i,1,1,id,key);
             }

         }
     }
     //
     if (nn==false)
     {
        for (i=0;i<20;i++)
         {
             for (j=0;j<30;j++)
             {
                if (Empire_Get_MyArmy(j,i,id,key)>100)
                 {
                    int mm,dd;
                    dd=rand()%4+1;
                    mm=Empire_Get_MyArmy(j,i,id,key)-10;
                    Empire_Move(j,i,dd,mm,id,key);
                 }
                 if (Empire_Get_Battling(j,i)&&Empire_Get_MyArmy(j,i,id,key)>0)
                 {
                    int mm =Empire_Get_Gold(id,key);
                    Empire_BuyArmy(j,i,mm,id,key);
                 }
                 if (Empire_Get_MyArmy(j,i,id,key)<5&&Empire_Get_Gold(id,key)>=10)
                 {
                    Empire_BuyArmy(j,i,1,id,key);
                 }
                 else if (Empire_Get_MyArmy(j,i,id,key)<10&&Empire_Get_Gold(id,key)>=10)
                 {
                    int bb;
                    bb=10-Empire_Get_MyArmy(j,i,id,key);
                    Empire_BuyArmy(j,i,bb,id,key);
                 }

             }
         }
     }

}
