#include <cstdint>	//uint_t
#include "Extra.h"
#include "Empire_Client.h"

bool WarMod=false;		//War and Expansion state
Controllor Terminal;
VectorI2D size;

VectorI2D SearchTarget(void)
{
	VectorI2D t(0,0);
	uint16_t a=0;		//amount
	for(uint8_t i=0;i<size.X;i++)
		for(uint8_t j=0;j<size.Y;j++)
		{
			if(Terminal.getAreaEnemyArmy(VectorI2D(i,j))>a)
			{
				a=Terminal.getAreaEnemyArmy(VectorI2D(i,j));
				t = VectorI2D(i,j);
			}	
		}
	return t;
}

bool SearchNonCap(void)
{
	for(uint8_t i=0;i<size.X;i++)
		for(uint8_t j=0;j<size.Y;j++)
		{
			VectorI2D	v(i,j);
			if(Terminal.getAreaArmyTotalArmy(v)==0)return true;
		}
	return false;		
}

void Expansion(uint8_t x,uint8_t y)
{
	bool u=true,d=true,r=true,l=true;
	if(x==0)l=false;
	else if(x==size.X-1)r=false;
	else if(y==0)d=false;
	else if(y==size.Y-1) u=false;
	
	VectorI2D v(x,y);
	if(u)if(Terminal.getAreaEnemyArmy(VectorI2D(x,y+1))==0)
		{	Terminal.MoveArmy(v,1,'U');}
	if(d)if(Terminal.getAreaEnemyArmy(VectorI2D(x,y-1))==0)
		{	Terminal.MoveArmy(v,1,'D');}
	if(r)if(Terminal.getAreaEnemyArmy(VectorI2D(x+1,y))==0)
		{	Terminal.MoveArmy(v,1,'R');}
	if(l)if(Terminal.getAreaEnemyArmy(VectorI2D(x-1,y))==0)
		{	Terminal.MoveArmy(v,1,'L');}
}

void Attack(VectorI2D target,VectorI2D block)
{
	uint16_t army = Terminal.getMyAreaArmy(block);
	int Dx=target.X-block.X,Dy=target.Y-block.Y;
	VectorI2D D;
	if(Dx<0)D.X=-1*Dx; else D.X=Dx;
	if(Dy<0)D.Y=-1*Dy; else D.Y=Dy;
	if(D.X>D.Y)			//right left first
	{
		if(Dx>=0)
			Terminal.MoveArmy(block,army-1,'R');
		else
			Terminal.MoveArmy(block,army-1,'L');
	}
	else				//up down first
	{
		if(Dy>=0)
			Terminal.MoveArmy(block,army-1,'U');
		else
			Terminal.MoveArmy(block,army-1,'D');
	}

}

extern "C" 
{
	
	void AI_Initialize(Controllor c)
	{
		Terminal = c;
		size = c.getWorldSize();
	}


	void AI_Action(void)
	{
		if(!WarMod)			//Expansion state
		{
			if(SearchNonCap())
				for(uint8_t i=0;i<size.X;i++)
					for(uint8_t j=0;j<size.Y;j++)
						Expansion(i,j);
			else WarMod=true;
		}
		else 				//War state
		{					
			VectorI2D Target = SearchTarget();
			for(uint8_t i=0;i<size.X;i++)
				for(uint8_t j=0;j<size.Y;j++)
					Attack(Target,VectorI2D(i,j));
						
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
