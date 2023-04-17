// AUTORE FILE: Chinello Alessandro

#include "../include/BattleShip.h"
#include "../include/Battlefield.h"

BattleShip::BattleShip() { 
    hp_ = 5;
    size_ = 5;
    type_ = 'C';
    for (int i=0; i<5; i++)
        positions_.push_back(Coordinate{"00"});
    cm_ = positions_[2];
}

void BattleShip::action(Battlefield& to_defend, Battlefield& to_attack, const Coordinate& t) { 
	if (!to_attack.is_inside(t)) return; 

	char hit  = 'O';
    // controllo se la posizione target è occupata da un pezzo di una nave
	if (to_attack.check_position(t)) {
        hit = 'X';

        // risalgo al proprietario della coordinata colpita
        NavalUnit* owner = to_attack.get_coordinate_owner(t);

        // controllo che la posizione non sia già stata colpita
        for (Coordinate& p : owner->get_positions())
            if (p == t && p.is_marked()) return;

        // decremento la vita della nave colpia e aggiorno la griglia di difesa nemica
        owner->decrease_life(t);
        to_attack.refresh_defence();
    }
	
	// aggiorno la mia griglia di attacco
	to_defend.mark_attack(t, hit);
}
