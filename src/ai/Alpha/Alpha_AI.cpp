#include <cstdint>	//uint_t
#include "Extra.h"
#include "Empire_Client.h"

extern "C" 
{
	Controllor Terminal;
	VectorI2D size;
	void AI_Initialize(Controllor c)
	{
		Terminal = c;
		size = c.getWorldSize();
	}


	void AI_Action(void)
	{
		for(uint8_t i=0;i<size.X;i++)
		{
			for(uint8_t j=0;j<size.Y;j++)
			{
				bool u=true,d=true,r=true,l=true;
				if(i==0)l=false;
				else if(i==size.X-1)r=false;
				else if(j==0)d=false;
				else if(j==size.Y-1) u=false;
				
				VectorI2D v(i,j);
				if(u)
				{
					if(Terminal.getAreaEnemyArmy(VectorI2D(i,j+1))==0)
					{	Terminal.MoveArmy(v,1,'U');}
				}
				
				if(d)
				{
					if(Terminal.getAreaEnemyArmy(VectorI2D(i,j-1))==0)
					{	Terminal.MoveArmy(v,1,'D');}
				}
				
				if(r)
				{
					if(Terminal.getAreaEnemyArmy(VectorI2D(i+1,j))==0)
					{	Terminal.MoveArmy(v,1,'R');}
				}
				if(l)
				{
					if(Terminal.getAreaEnemyArmy(VectorI2D(i-1,j))==0)
					{	Terminal.MoveArmy(v,1,'L');}
				}

			}
		}
	}


	void AI_GameOver(char c)
	{
		if(c=='W')			//win
		{}
		else if(c=='L')		//lose
		{}
		else if(c=='I')		//interrupt
		{}
	}

}
