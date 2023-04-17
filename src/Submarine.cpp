// AUTORE FILE: Chinello Alessandro

#include "../include/Submarine.h"
#include "../include/Battlefield.h"

Submarine::Submarine() {
    hp_ = 1;
    size_ = 1;
    type_ = 'E';
    positions_ = { Coordinate{"00"} };
    cm_ = positions_[0];
}

void Submarine::action(Battlefield& to_defend, Battlefield& to_attack, const Coordinate& t) {
    if (!to_attack.is_inside(t)) return;

    // controllo se la destinzione è già occupata, se è lui stesso ad occuparla
    // eseguo comunque l'azione
    if (!to_defend.move(this, t) && cm_ != t) return;

    // trovo le coordinate della posizione (0,0) e della posizione (0,4)
    // della matrice 5x5 che ha il target come centro.
    // controllo sugli indici di riga delle due coordinate
    char start_x = t.x() - 2;
    if (start_x == 'J') start_x = 'H'; // solo se il target si trova alla riga 'L'
    if (start_x == 'K') start_x = 'I'; // solo se il target si trova alla riga 'M' 

    char end_x =  t.x() + 2;
    if (end_x == 'J') end_x = 'L'; // solo se il target si trova alla riga 'H'
    if (end_x == 'K') end_x = 'M'; // solo se il target si trova alla riga 'I' 

    Coordinate start(start_x, t.y()-2); // posizione (0,0) matrice
    Coordinate end(end_x, t.y()-2); // posizione (0,4) matrice

    // creo il vettore della colonna che va da (0,0) a (4,0)
    std::vector<Coordinate> matrix_rows = generate_inline_position(start, end);

    // creo il vettore contenente le posizioni da marchiare
    std::vector<Coordinate> sonar;

    // calcolo le restanti posizioni partendo dalla colonna creata
    for (int i=0; i<matrix_rows.size(); i++) 
        for (int j=0; j<matrix_rows.size(); j++) {
            // coordinata da controllare
            Coordinate tmp(matrix_rows[i].x(), matrix_rows[i].y()+j);
            if (to_attack.check_position(tmp))
                sonar.push_back(tmp);
        }

    // scrivo nella griglia di attacco
    for (const Coordinate& p : sonar) {
        // risalgo al proprietario dalla coordinata che devo segnare
        NavalUnit* owner = to_attack.get_coordinate_owner(p);

        // controllo se la coordintata è già stata colpita in precedeza
        for (const Coordinate& c : owner->get_positions())
            if (c==p && c.is_marked()) to_defend.mark_attack(p, 'X');
            else if (c == p) to_defend.mark_attack(p, 'Y');
    }
}


