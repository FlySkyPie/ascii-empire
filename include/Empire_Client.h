#ifndef EMPIRE_CLIENT_H
#define EMPIRE_CLIENT_H

#include "Extra.h"

struct Empire;

struct Controllor
{
	Controllor(void);
	Controllor(Empire* target);
	void MoveArmy(VectorI2D position,uint32_t amount,char direct);
	
	uint32_t getMyAreaArmy(VectorI2D position);
	uint32_t getMyPopulation(void);
	bool getBattling(VectorI2D position);
	
	uint32_t getAreaArmy(VectorI2D position,uint8_t index);
	uint32_t getAreaArmyTotalArmy(VectorI2D position);
	uint32_t getAreaEnemyArmy(VectorI2D position);
	
	uint32_t getEmpirePopulation(uint8_t index);
	uint32_t getWorldPopulation(void);
	uint32_t getEnemyPopulation(void);
	VectorI2D getWorldSize(void);
	
	private:
	Empire* Target;
};
#endif
