// AUTORE FILE: Piai Luca

#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <list>
#include <vector>
#include "Coordinate.h"

class NavalUnit; // forward declaration

// Rappresenta il campo di battaglia di un giocatore,
// contiene le griglie di attacco e difesa e contiene le navi
class Battlefield {
public:
    Battlefield();

    Battlefield(const Battlefield& b) = delete;
    Battlefield& operator=(const Battlefield& b) = delete;

    // rimuove dalla griglia d'attacco il carattere specificato
    void clean_attack(char c);

    // permette di scrivere un carattere nella griglia d'attacco
    void mark_attack(const Coordinate& p, char c);

    // aggiorna i caratteri delle units nella griglia di difesa
    void refresh_defence();

    // sposta la nave all'interno della griglia di difesa
    // e aggiorna le posizioni della nave. Torna true se lo
    // spostamento è avvenuto
    bool move(NavalUnit* u, const Coordinate& p);

    // inserisce nella lista units_ la nave e la disegna nella matrice,
    // non controlla la validità delle coordinate della nave
    void insert(NavalUnit* u);

    // torna true se units_ è vuota
    bool is_empty() const { return units_.empty(); }

    // torna true se nella cella corrispondente alla coordinata
    // passata è presente un pezzo di una nave
    bool check_position(const Coordinate& p) const;

    // torna true appena trova una posizione occupata da un
    // pezzo di una nave
    bool check_position(const std::vector<Coordinate>& v) const;

    // torna true se la coordinata passata è interna alla griglia
    bool is_inside(const Coordinate& p) const;

    // torna true solo se tutte le coordinate sono interne alla griglia
    bool is_inside(const std::vector<Coordinate>& v) const;
    
    // ritorna l'unità navale che ha il cm alla coordinata passata
    NavalUnit* choose_unit(const Coordinate& p) const;

    // permette di risalire al'unità che occupa una data coordinata
    NavalUnit* get_coordinate_owner(const Coordinate& p) const;

    // converte il carattere passato nell'indice di riga associato
    int row(char c) const; 

    friend std::ostream& operator<<(std::ostream& os, const Battlefield& b);

private:
    char defence_[13][13]; // griglia di difesa
    char attack_[13][13]; // griglia di attacco
    std::list<NavalUnit*> units_; // unità navali presenti nel campo di battaglia
};

#endif
