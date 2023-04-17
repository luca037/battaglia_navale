// AUTORE FILE: Chinello Alessandro

#include "../include/SupportVessel.h"
#include "../include/Battlefield.h"

SupportVessel::SupportVessel() {
    hp_ = 3;
    size_ = 3;
    type_ = 'S';
    for (int i=0; i<3; i++)
        positions_.push_back(Coordinate{"00"});
    cm_ = positions_[1];
}

void SupportVessel::action(Battlefield& to_defend, Battlefield& to_attack, const Coordinate& t) {
    if (!to_defend.is_inside(t)) return;

    // se il target è occupato (non da se stesso) non eseguo l'azione
    if (!to_defend.move(this, t) && cm_ != t) return;
 
    // trovo le coordinate della posizione (0,0) e della posizione (0,2)
    // della matrice 3x3 che ha il target come centro.
    // controllo sugli indici di riga delle due coordinate
    char start_x = t.x() - 1;
    if (start_x == 'K') start_x = 'I'; // solo se il target si trova alla riga 'L'

    char end_x = t.x() + 1;  
    if (end_x == 'J') end_x = 'L'; // solo se il target si trova alla riga 'I'

    Coordinate start(start_x, t.y()-1); // posizione (0,0) matrice
    Coordinate end(end_x, t.y()-1); // posizione (0,2) matrice

    // creo il vettore della colonna che va da (0,0) a (2,0)
    std::vector<Coordinate> matrix_rows = generate_inline_position(start, end);

    // calcolo le restanti posizioni partendo dalla colonna creata
    for (int i=0; i<matrix_rows.size(); i++)
        for (int j=0; j<matrix_rows.size(); j++) {
            // coordinata da controllare
            Coordinate tmp(matrix_rows[i].x(), matrix_rows[i].y()+j);

            // se la coordinata è vuota
            if (!to_defend.check_position(tmp)) continue;

            // controllo che non si auto curi
            bool flag = 0;
            for (const Coordinate& p : positions_)
                if (p == tmp) flag = 1;
            if (flag) continue;

            // curo la nave a cui appartiene il pezzo
            NavalUnit* owner = to_defend.get_coordinate_owner(tmp);
            owner->restore();
        }

    // refresh del campo in cui ho curato
    to_defend.refresh_defence();
}
