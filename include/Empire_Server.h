#ifndef EMPIRE_SERVER_H
#define EMPIRE_SERVER_H
#include <string>			//string
#include <cstring>
#include <vector>
#include <cstdlib>

#include "Extra.h"

typedef void (*TYPE_AI_INIT_FUNC)(Controllor);
typedef void (*TYPE_AI_ACT_FUNC)(void);
typedef void (*TYPE_AI_OVER_FUNC)(char);

struct Empire;

struct Map
{
	string Name;
	VectorI2D Size;
	vector<VectorI2D> SpawnPoint;
	uint32_t Population;
};

struct World
{
	World(Map terrain,vector<string> AI);
	~World();
	
	vector<Empire*> Country;
	
	void InitializeEmpire(void);
	void Ask(void);
	void Action(void);
	bool TheEnd(void);
	
	void Draw(void);
	string getPicture(uint8_t x,uint8_t y);
	VectorI2D getSize(void);
	private:
	uint32_t Count;
	string **Picture;
	VectorI2D Size;
};

struct Empire
{
	Empire(World*w,string filename,VectorI2D *size,VectorI2D CapPoint,uint32_t pop);	//map size,capital position,capital population
	~Empire();
	
	World* Cosmos;
	string Name;
	VectorI2D *Size;
	//dynamic libaray stuff
	void *Handle;						//dynamic libaray handle
	void (*Initialize)(Controllor);
	void (*Action)(void);
	void (*GameOver)(char);
	
	//client command
	void MoveArmy(VectorI2D position,uint32_t amount,char direct);
	
	uint32_t getAreaArmy(VectorI2D position,uint8_t index);
	uint32_t getAreaArmyTotalArmy(VectorI2D position);
	uint32_t getAreaEnemyArmy(VectorI2D position);
	
	uint32_t getEmpirePopulation(uint8_t index);
	uint32_t getWorldPopulation(void);
	uint32_t getEnemyPopulation(void);
	
	uint32_t getMyAreaArmy(VectorI2D position);
	uint32_t getMyPopulation(void);
	
	bool getBattling(VectorI2D position);
	VectorI2D getSize(void);
	
	//server operate
	VectorI2D getMaximum(void);
	
	uint32_t **Army;
	uint32_t **ArmyBuffer;
};

extern string PrintSpace(string str,uint8_t len);
#endif
