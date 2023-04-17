// AUTORE FILE: Chinello Alessandro

#ifndef SUBMARINE_H
#define SUBMARINE_H

#include "../include/NavalUnit.h"

class Submarine : public NavalUnit {
public:
    Submarine();
    void action(Battlefield& to_defend, Battlefield& to_attack, const Coordinate& t);
};

#endif
