// AUTORE FILE: Chinello Alessandro

#ifndef HUMAN_H
#define HUMAN_H

#include <fstream>

#include "Player.h"
#include "NavalUnit.h"

class Human : public Player {
public:
	Human() : initialized_units_{1} { };

    Human(const Human&) = delete;
    Human& operator=(const Human&) = delete;

	void init_unit(Battlefield& own, NavalUnit* u, std::ofstream& log);
	int turn(Battlefield& own, Battlefield& enemy, std::ofstream& log);

private:
    // contatore che tiene conto del numero di barche che sono state inizializzate
    int initialized_units_;

    // restituisce il nome dell'unità in base all valore di initialized_units_
    std::string get_unit_name();

    // se la stringa passata corrisponde ad un comando speciale lo esegue e torna true
    bool special_commands(Battlefield& b, const std::string& in1, const std::string& in2);
};

#endif
