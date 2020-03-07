#include <iostream>
#include <dlfcn.h>		//dynamic library
#include <dirent.h>		//DIR
#include <errno.h>		//

#include "Empire_Client.h"
#include "Empire_Server.h"

using namespace std;

//Controllor
Controllor::Controllor(void){}
Controllor::Controllor(Empire* target)
{	Target = target;	}
void Controllor::MoveArmy(VectorI2D position,uint32_t amount,char direct)
{	Target->MoveArmy(position,amount,direct);}

uint32_t Controllor::getMyAreaArmy(VectorI2D position)
{	return Target->getMyAreaArmy(position);}
uint32_t Controllor::getMyPopulation(void)
{	return Target->getMyPopulation();}
bool Controllor::getBattling(VectorI2D position)
{	return Target->getBattling(position);}

uint32_t Controllor::getAreaArmy(VectorI2D position,uint8_t index)
{	return Target->getAreaArmy(position,index);}
uint32_t Controllor::getAreaArmyTotalArmy(VectorI2D position)
{	return Target->getAreaArmyTotalArmy(position);}
uint32_t Controllor::getAreaEnemyArmy(VectorI2D position)
{	return Target->getAreaEnemyArmy(position);}

uint32_t Controllor::getEmpirePopulation(uint8_t index)
{	return Target->getEmpirePopulation(index);}
uint32_t Controllor::getWorldPopulation(void)
{	return Target->getWorldPopulation();}
uint32_t Controllor::getEnemyPopulation(void)
{	return Target->getEnemyPopulation();}
VectorI2D Controllor::getWorldSize(void)
{
	return Target->getSize();
}

//Empire.All of data and operate are here.
Empire::Empire(World*w,string filename,VectorI2D *size,VectorI2D CapPoint,uint32_t pop)
{
	vector <string> _name;
	SplitString(filename,'.',_name);
	Name = _name[0];
	cout << "Empire\"" << Name << '('<< filename << ')' <<"\" structing...\n";
	
	Cosmos = w;
	Size = size;

	//create army array
	Army = new uint32_t*[Size->X];
	for(uint8_t i = 0 ; i < Size->X; i ++) { Army[i] = new uint32_t[Size->Y]; } 
	
	//create army buffer array
	ArmyBuffer = new uint32_t*[Size->X];
	for(uint8_t i = 0 ; i < Size->X; i ++) { ArmyBuffer[i] = new uint32_t[Size->Y]; } 
	
	//initialize empire's arrmy
	for(uint8_t i=0;i<Size->X;i++)
		for(uint8_t j=0;j<Size->Y;j++)
			Army[i][j]=0;
			
	//set capital population
	Army[CapPoint.X][CapPoint.Y] = pop;
}
Empire::~Empire()
{
	cout << "Empire\"" <<Name <<"\" destructing...\n";
	for (uint i=0; i<Size->X; i++)
	{   delete [] Army[i];	}
	delete [] Army; 
	
	for (uint i=0; i<Size->X; i++)
	{   delete [] ArmyBuffer[i];	}
	delete []ArmyBuffer;
}
void Empire::MoveArmy(VectorI2D position,uint32_t amount,char direct)
{
	if(position.X>=Size->X||position.Y>=Size->Y)return;
	if(Army[position.X][position.Y]<amount)amount = Army[position.X][position.Y];	//don't have enough army
	if(direct=='U')
	{
		if(position.Y==Size->Y-1)return;			//already been edge,can't move up
		Army[position.X][position.Y]-=amount;
		ArmyBuffer[position.X][position.Y+1]+=amount;
	}
	else if(direct=='D')
	{
		if(position.Y==0)return;					//already been edge,can't move down
		Army[position.X][position.Y]-=amount;
		ArmyBuffer[position.X][position.Y-1]+=amount;
	}
	else if(direct=='R')
	{
		if(position.X==Size->X-1)return;			//already been edge,can't move right
		Army[position.X][position.Y]-=amount;
		ArmyBuffer[position.X+1][position.Y]+=amount;
	}
	else if(direct=='L')
	{
		if(position.X==0)return;					//already been edge,can't move left
		Army[position.X][position.Y]-=amount;
		ArmyBuffer[position.X-1][position.Y]+=amount;
	}
}

uint32_t Empire::getAreaArmy(VectorI2D position,uint8_t index)
{
	if(position.X>=Size->X||position.Y>=Size->Y)return 0;		//position over range
	if(index >= Cosmos->Country.size())return 0;						//index over range
	uint32_t sum = Cosmos->Country.at(index)->Army[position.X][position.Y] + Cosmos->Country.at(index)->ArmyBuffer[position.X][position.Y];
	return sum;
}
uint32_t Empire::getAreaArmyTotalArmy(VectorI2D position)
{
	if(position.X>=Size->X||position.Y>=Size->Y)return 0;		//position over range
	
	uint32_t sum=0;
	for(uint8_t i=0;i<Cosmos->Country.size();i++)
	{
		sum+=Cosmos->Country.at(i)->Army[position.X][position.Y];
		sum+=Cosmos->Country.at(i)->ArmyBuffer[position.X][position.Y];
	}
	return sum;
	
}
uint32_t Empire::getAreaEnemyArmy(VectorI2D position)
{
	if(position.X>=Size->X||position.Y>=Size->Y)return 0;		//position over range
	
	uint32_t sum=0;
	for(uint8_t i=0;i<Cosmos->Country.size();i++)
	{
		if(Cosmos->Country.at(i)==this)continue;
		sum+=Cosmos->Country.at(i)->Army[position.X][position.Y];
		sum+=Cosmos->Country.at(i)->ArmyBuffer[position.X][position.Y];
	}
	return sum;
}

uint32_t Empire::getEmpirePopulation(uint8_t index)
{
	if(index >= Cosmos->Country.size())return 0;						//index over range
	return Cosmos->Country.at(index)->getMyPopulation();
	
}
uint32_t Empire::getWorldPopulation(void)
{
	uint32_t sum=0;
	for(uint8_t i=0;i<Cosmos->Country.size();i++)
	{
		sum+=Cosmos->Country.at(i)->getMyPopulation();
	}
	return sum;
}
uint32_t Empire::getEnemyPopulation(void)
{
	uint32_t sum=0;
	for(uint8_t i=0;i<Cosmos->Country.size();i++)
	{
		if(Cosmos->Country.at(i)==this)continue;
		sum+=Cosmos->Country.at(i)->getMyPopulation();
	}
	return sum;
}

uint32_t Empire::getMyAreaArmy(VectorI2D position)
{
	if(position.X>=Size->X||position.Y>=Size->Y)return 0;		//position over range
	uint32_t sum = Army[position.X][position.Y] + ArmyBuffer[position.X][position.Y];
	return sum;
}
uint32_t Empire::getMyPopulation(void)
{
	uint32_t sum=0;
	for(uint8_t i=0;i<Size->X;i++)
		for(uint8_t j=0;j<Size->Y;j++)
		{
			sum+=Army[i][j];
			sum+=ArmyBuffer[i][j];
		}
	return sum;
}

bool Empire::getBattling(VectorI2D position)
{
	if(position.X>=Size->X||position.Y>=Size->Y)return false;
	uint8_t n=0;
	for(uint8_t i=0;i<Cosmos->Country.size();i++)
	{
		if(Cosmos->Country.at(i)->Army[position.X][position.Y] + Cosmos->Country.at(i)->ArmyBuffer[position.X][position.Y] >0)n++;
	}
	if(n>1)return true;
	else return false;
}

VectorI2D Empire::getSize(void)
{
	return *Size;
}


//World===============================================
World::World(Map terrain,vector<string> AI)
{
	Count = 0;
	Size = terrain.Size;			//set size of world
	
	//create picture array
	Picture = new string*[Size.X];
	for(uint8_t i = 0 ; i < Size.X; i ++) { Picture[i] = new string[Size.Y]; } 
	
	//initialize picture array
	for(uint8_t i=0;i<Size.X;i++)
		for(uint8_t j=0;j<Size.Y;j++)
			Picture[i][j]="";
	
	for(uint8_t i=0;i<AI.size();i++)
	{
		Empire *e=new Empire(this,AI.at(i),&Size,terrain.SpawnPoint.at(i),terrain.Population);
	
		//load dynamic library
		string dir = "./intelligences/"+AI.at(i);
		e->Handle = dlopen(dir.c_str(), RTLD_LAZY);			//open AI's shared library

		if (!e->Handle)	//dlopen failed
		{	fprintf (stderr, "%s\n", dlerror());	delete e;	continue;	}
			
		e->Initialize	= (TYPE_AI_INIT_FUNC)dlsym(e->Handle, "AI_Initialize");	//find address of AI_Initialize() function
		e->Action		= (TYPE_AI_ACT_FUNC)dlsym(e->Handle, "AI_Action");		//find address of AI_Action() function
		e->GameOver	= (TYPE_AI_OVER_FUNC)dlsym(e->Handle, "AI_GameOver");	//find address of AI_GameOver() function

		char *error;
		if(( error=dlerror())!=NULL)	//dlsym failed
		{	fputs(error, stderr);	delete e;	continue;	}
			
			
			
		Country.push_back(e);//everything was fine,load AI to the vector
	}
}

World::~World(void)
{
	while(Country.size()!=0)
	{
		Empire *e = Country.back();
		Country.pop_back();
		delete e;
	}
	for (uint i=0; i<Size.X; i++)
	{   delete [] Picture[i];	}
	delete []Picture;
}
void World::Action(void)
{
	if(TheEnd())
	{
		for(uint8_t i=0;i<Country.size();i++)
		{
			Empire *e = Country.at(i);
			if( e->getMyPopulation()>0 )e->GameOver('W');
			else e->GameOver('L');
		}
		return;
	}
	//army move process
	for(uint k=0;k<Country.size();k++)
	{
		Empire *e = Country.at(k);
		for(uint8_t i=0;i<Size.X;i++)
		{
			for(uint8_t j=0;j<Size.Y;j++)
			{
				e->Army[i][j] += e->ArmyBuffer[i][j];
				e->ArmyBuffer[i][j] = 0;
			}
		}
	}
	
	//damage and product process
	
	for(uint8_t i=0;i<Size.X;i++)
	{
		for(uint8_t j=0;j<Size.Y;j++)
		{
			uint32_t dam=0;		//damage
			uint8_t n=0;		//identify battling
			Empire *capter=NULL;//capture empire
			for(uint k=0;k<Country.size();k++)
			{
				dam += Country.at(k)->Army[i][j];		//sum damage
				if(Country.at(k)->Army[i][j]>0)
				{	capter = Country.at(k);	n++;	}
			}
			if(n==1)				//some one capture
			{	capter->Army[i][j] +=1;	}
			else if(n>1)		//battling
			{
				for(uint8_t b=0;b<Country.size();b++)
				{
					Empire *bb = Country.at(b);		//the empire who been attack
					uint32_t dam2 = dam - bb->Army[i][j];
					if(bb->Army[i][j]<=dam2/2)bb->Army[i][j]=0;
					else bb->Army[i][j]-=dam2/2;	
				}
			}
		}
	}
	
		
	Count +=1;	
}

bool World::TheEnd(void)
{
	uint8_t life=0;
	for(uint k=0;k<Country.size();k++)
	{
		if(Country.at(k)->getMyPopulation()>0)life+=1;
	}
	if(life>1)return false;
	else return true;
	
}

void World::InitializeEmpire(void)
{
	for(uint k=0;k<Country.size();k++)
	{
		Controllor c(Country.at(k));
		Country.at(k)->Initialize(c);
	}
		
}

void World::Ask(void)
{
	for(uint k=0;k<Country.size();k++)
	{
		Country.at(k)->Action();
	}
}

void World::Draw(void)
{
	for(uint8_t i=0;i<Size.Y;i++)
	{
		for(uint8_t j=0;j<Size.X;j++)
		{
			
			bool c=false;//identify area are non-man caption
			bool b=false;//identify area are battling?
			uint8_t n=0;
			for(uint8_t s=0;s<Country.size();s++)
			{
				if(Country.at(s)->Army[j][i]>0)
				{	n++;	c=true;}
			}
			if(n>1)b=true;
			
			if(!c)Picture[j][i] = "0";
			else if(b)Picture[j][i] = "\e[48;5;1m\e[1mX\e[0m";
			else
			{
				for(uint8_t s=0;s<Country.size();s++)
					if(Country.at(s)->Army[j][i]>0)
					{	Picture[j][i] = "\e[38;5;" + to_string(s+1) + "m" + Country.at(s)->Name.at(0) + "\e[0m";break;}
			}
		}
	}
}

string World::getPicture(uint8_t x,uint8_t y)
{
	if(x>=Size.X||y>=Size.Y)return "";
	return Picture[x][y];
}

VectorI2D World::getSize(void)
{	return Size;}


string PrintSpace(string str,uint8_t len)
{
	string tmp;
	if(str.length()>=len) return tmp.assign(str,0,len);
	else
	{
		tmp = str;
		for(uint8_t i=0;i<len-str.size();i++)
			tmp += " ";
		return tmp;
	}
}
