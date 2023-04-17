// AUTORE FILE: Chinello Alessandro

#ifndef NAVALUNIT_H
#define NAVALUNIT_H

#include "Coordinate.h"

class Battlefield; // forward declaration

// rappresenta un'unità navale
class NavalUnit {
public:
    // azione specifica di ogni nave, riceve come parametri: il campo in cui si trova;
    // il campo del nemico; la coordinata di target
    virtual void action(Battlefield& to_defend, Battlefield& to_attack, const Coordinate& t) = 0;

    // ripristina la vita della nave
    void restore() {
        for (Coordinate& p : positions_)
            p.unmark();
        hp_ = size_;
    }

    // decrementa di uno la vita della nave e setta a hit la coordinata colpita
    void decrease_life(const Coordinate& p) {
        for (Coordinate& c : positions_) {
            if (c == p) {
                c.mark();
                --hp_;
                break;
            }
        }
    }

    // setta le nuove posizioni
    void set_positions(std::vector<Coordinate> v) {
        if(v.size() != size_) return;
        for (int i=0; i<size_; i++) {
            if (positions_.size() == 0)
                break;
            if (positions_[i].is_marked())
                v[i].mark();
        }
        positions_ = v;
        cm_ = v[v.size()/2]; // aggiorno il cm_
    }

    // ritorna il carattere associato alla nave
    char type() const { return type_; }

    // ritorna un vettore contenente le coordinate occupate dalla nave
    std::vector<Coordinate> get_positions() const { return positions_; }

    // ritorna la coordinata del centro di massa della nave
    Coordinate get_cm() const { return cm_; }

    // ritorna la coordinata della prua della nave
    Coordinate get_bow() const { return positions_.front(); }

    // ritorna la coordinata della poppa della nave
    Coordinate get_stern() const { return positions_.back(); }

    // torna true se la nave è ancora viva
    bool is_alive() const { return hp_ != 0; }

    // torna il numero di punti vita della nave
    int get_hp() const { return hp_; }

    // torna la dimensione della nave
    int size() const { return size_; }

    NavalUnit(const NavalUnit& n) = delete;
    NavalUnit& operator=(const NavalUnit&) = delete;

    virtual ~NavalUnit() { }

protected:
    NavalUnit() { }

    int hp_; // punti vita
    int size_; // dimensione
    char type_; // carattere identificativo 
    Coordinate cm_; // centro di massa
    std::vector<Coordinate> positions_; // posizioni occupate
};

#endif
