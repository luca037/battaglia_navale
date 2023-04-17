// AUTORE FILE: Chinello Alessandro

#ifndef BATTLESHIP_HPP
#define BATTLESHIP_HPP

#include "NavalUnit.h"

class BattleShip : public NavalUnit{
public:
	BattleShip();
	void action(Battlefield& to_defend, Battlefield& to_attack, const Coordinate& t);
};

#endif
