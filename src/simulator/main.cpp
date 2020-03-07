#include <cstring>
#include <fstream> 
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <dirent.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>			//usleep

#include "Extra.h"
#include "Empire_Client.h"
#include "Empire_Server.h"
using namespace std;

vector <Map> MapList;			//map list
vector <string> AIList;			//the vector of string which remanber AIs file name		
Map *ms=NULL;					//map select pointer
vector<string> AISelectList;	//those AI who been chosen

void ReadMap(void)
{
	string dir = string("maps/");				//where are the AIs
    vector<string> files = vector<string>();	
	GetFilesInDirectory(dir, files);			//get all of AI's file name
	for(uint8_t i =0;i<files.size();i++)		//read each file
	{
		Map m;
		m.Name = files[i];
		//read files
    	string filename,line;
    	filename = dir + files[i];
		ifstream myfile(filename);
		if (myfile.is_open())
		{
			while ( getline (myfile,line) )		//read file each line,and identify them
			{	
				vector<string> script;
				SplitString(line,' ',script);
				
				if(script[0]=="Size")
				{	m.Size.X = stoi(script[1]);m.Size.Y = stoi(script[2]);	}
				else if(script[0]=="Population")
				{	m.Population=stoi(script[1]);	}
				else if(script[0]=="SpawnPoint")
				{
					VectorI2D l(stoi(script[1]),stoi(script[2]));
					m.SpawnPoint.push_back(l);
				}	
			}
			MapList.push_back(m);
			myfile.close();
		}
	}
}

void DrawMapMenu(uint8_t ss)
{
	cout << "\033[H\033[J";		//clear
	//prepare mini map
	Map *m = &MapList.at(ss);							//chosen map
	uint8_t _y = m->Size.Y *30 / m->Size.X;
	char screen[30][_y];
	
	//initialize mini map screen array
	for(uint8_t i=0;i<_y;i++)
		for(uint8_t j=0;j<30;j++)
			screen[j][i] = '0';
	
	//setting mini-map
	for(uint8_t i=0;i< m->SpawnPoint.size();i++)
	{
		uint8_t x,y;
		x=m->SpawnPoint.at(i).X*30/m->Size.X;
		y=m->SpawnPoint.at(i).Y*_y/m->Size.Y;
		screen[x][y]='S';
	}
	
	//print
	for(uint8_t i=0;i<_y;i++)
	{
		string n="";
		if(i==ss)n+= ">";						//when map are selected,then point out
		if(i<MapList.size())n+=MapList[i].Name;
		cout << PrintSpace(n,16) << "|";
		for(uint8_t j=0;j<30;j++)
		{
			if(screen[j][i]=='S')cout << " \033[91m" << screen[j][_y-1-i] << "\033[m";
			else cout << ' ' << screen[j][i];
		}
		cout << endl;
	}
	for(uint8_t i=0;i<80;i++)cout<<"=";
	cout<<endl;
	cout << "Map name:" << m->Name << "\tsize:" << m->Size.X << "x" << m->Size.Y << "\tSize Player:" << m->SpawnPoint.size() << "\tPopulation:" << m->Population << endl; 
}

void SelectMap(void)
{
	uint8_t SelectIndex = 0;	//selection pointer 
	DrawMapMenu(SelectIndex);
	while(1)			//select map
	{
		string cmd;
		cin >> cmd;
		if(cmd=="exit")break;
		else if(cmd=="next")
		{
			if(SelectIndex==MapList.size()-1)continue;
			else SelectIndex+=1;
		}
		else if(cmd=="back")
		{
			if(SelectIndex==0)continue;
			else SelectIndex+=-1;
		}
		else if(cmd=="enter")
		{
			ms = &MapList.at(SelectIndex);
			break;
		}
		DrawMapMenu(SelectIndex);		//draw map menu
	}
	DrawMapMenu(SelectIndex);
}


void DrawAIMenu(uint8_t ss)
{
	cout << "\033[H\033[J";		//clear
	//prepare mini map
	uint8_t _y = ms->Size.Y *30 / ms->Size.X;
	char screen[30][_y];
	
	//initialize screen array
	for(uint8_t i=0;i<_y;i++)
		for(uint8_t j=0;j<30;j++)
			screen[j][i] = '0';
	
	//setting mini-map
	for(uint8_t i=0;i< ms->SpawnPoint.size();i++)
	{
		uint8_t x,y;
		x=ms->SpawnPoint.at(i).X*30/ms->Size.X;
		y=ms->SpawnPoint.at(i).Y*_y/ms->Size.Y;
		screen[x][y]='S';
	}
	
	//print
	for(uint8_t i=0;i<_y;i++)
	{
		string n="";
		if(i==ss)n+= ">";						//when map are selected,then point out
		if(i<AIList.size())n+=AIList.at(i);
		cout << PrintSpace(n,16) << "|";
		
		for(uint8_t j=0;j<30;j++)
		{
			if(screen[j][i]=='S')cout << " \033[91m" << screen[j][_y-1-i] << "\033[m";
			else cout << ' ' << screen[j][i];
		}
		cout << endl;
	}
	for(uint8_t i=0;i<80;i++)cout<<"=";
		cout<<endl;
	cout << "Map name:" << ms->Name << "\tSize:" << ms->Size.X << "x" << ms->Size.Y << "\tSize Player:" << ms->SpawnPoint.size() << "\tPopulation:"<<ms->Population <<endl;
	cout << "AI Selected:" << AISelectList.size() << '/' << ms->SpawnPoint.size()<<endl; 
	for(uint8_t i=0;i<AISelectList.size();i++)
	{
		cout << AISelectList.at(i) << endl;
	}
}

void SelectAI(void)
{
	uint8_t SelectIndex=0;	//selection pointer 
	DrawAIMenu(SelectIndex);
	
	while(1)			//select AI
	{
		string cmd;
		cin >> cmd;
		if(cmd=="exit")break;
		else if(cmd=="next")
		{
			if(SelectIndex==AIList.size()-1)continue;
			else SelectIndex+=1;
		}
		else if(cmd=="back")
		{
			if(SelectIndex==0)continue;
			else SelectIndex+=-1;
		}
		else if(cmd=="enter")
		{
			AISelectList.push_back(AIList.at(SelectIndex));
			AIList.erase(AIList.begin()+SelectIndex);
			if(AISelectList.size()==ms->SpawnPoint.size())break;
			
		}
		if(SelectIndex>AIList.size()-1)SelectIndex-=1;
		DrawAIMenu(SelectIndex);		//draw AI menu
	}
	DrawAIMenu(SelectIndex);
}

void DrawMap(World *w)
{
	cout << "\033[H\033[J";		//clear
	VectorI2D s = w->getSize();
	for(uint16_t i=0;i<s.Y;i++)
	{
		for(uint16_t j=0;j<s.X;j++)
		{
			cout << w->getPicture(j,s.Y-1-i) << ' ';
		}
		cout << "|";
		if(i<w->Country.size())
		{
			cout <<"\e[38;5;" << to_string(i+1) << "m" << w->Country.at(i)->Name <<"\e[0m\t" << w->Country.at(i)->getMyPopulation();
		}
		cout << "\n";
	}
}

int main(int argc, char **argv) 
{
	
	ReadMap();			//read maps

	//get AIs List
	string dir = string("intelligences/");				//where are the AI files
	GetFilesInDirectory(dir, AIList);			//get AIs name
	
	SelectMap();
	SelectAI();
	
	World *World_1 = new World(*ms,AISelectList);;
	//give controllor to AIs 
	for(uint8_t i=0;i<World_1->Country.size();i++)
	{
		Controllor c(World_1->Country.at(i));
		World_1->Country.at(i)->Initialize(c);
	}
	World_1->Action();	//first action
	
	//game start
	World_1->InitializeEmpire();		//round 1
	
	uint16_t tmp=0;
	while(!World_1->TheEnd())
	{
		World_1->Ask();
		World_1->Action();
		if(tmp%5==0)
		{
			World_1->Draw();
			DrawMap(World_1);
			usleep(400*1000);
		}
		else usleep(10*1000);
		if(tmp>=600)break;
		else tmp++;
	}
	World_1->Draw();
	DrawMap(World_1);
	
	delete World_1;
	return 0;
}
