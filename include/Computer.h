// AUTORE FILE: Piai Luca

#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>
#include <fstream>

#include "Player.h"
#include "NavalUnit.h"
#include "Battlefield.h"
#include "Coordinate.h"

// rappresenta il player computer
class Computer : public Player {
public:
    Computer() { };

    Computer(const Computer&) = delete;
    Computer& operator=(const Computer&) = delete;

	void init_unit(Battlefield& own, NavalUnit* u, std::ofstream& log); 
	int turn(Battlefield& own, Battlefield& enemy, std::ofstream& log);

private:
    static constexpr char kRows[] = { '0', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'L', 'M', 'N', '\0' };

    // unità in vita
    std::vector<NavalUnit*> alive_units_;

    // restituisce una coordinata randomica
    Coordinate get_random_coordinate();
};

#endif
