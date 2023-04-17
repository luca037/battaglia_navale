// AUTORE FILE: Piai Luca

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "Coordinate.h"
#include "Battlefield.h"

class Player {
public:
    // inizializza l'unità navale passata come parametro
	virtual void init_unit(Battlefield& own, NavalUnit* u, std::ofstream& log) = 0;

    // viene eseguito un turno
	virtual int turn(Battlefield& own, Battlefield& enemy, std::ofstream& log) = 0;
};

#endif
